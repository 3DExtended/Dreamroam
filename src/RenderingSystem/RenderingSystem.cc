#include "RenderingSystem.hh"

#include <GLFW/glfw3.h>

#include <ComponentBased/SceneHandler.hh>
#include <GlobalSettings.hh>
#include <RenderingSystem/Pipeline/GraphicsPipelineFactory.cc>
#include <Utils/Debug/Profiling.hh>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <lava-extras/camera/GenericCamera.hh>
#include <lava-extras/imgui/ImGui.hh>
#include <lava/common/log.hh>
#include <lava/createinfos/Buffers.hh>
#include <lava/createinfos/DescriptorSetLayoutCreateInfo.hh>
#include <lava/createinfos/Images.hh>
#include <lava/createinfos/Sampler.hh>
#include <lava/features/GlfwOutput.hh>
#include <lava/features/MultiView.hh>
#include <lava/gpuselection/NthOfTypeStrategy.hh>
#include <lava/objects/Buffer.hh>
#include <lava/objects/DescriptorSetLayout.hh>
#include <lava/objects/Framebuffer.hh>
#include <lava/objects/Image.hh>
#include <lava/objects/ImageView.hh>
#include <lava/objects/Instance.hh>
#include <limits>
#include <thread>

RenderingSystem::RenderingSystem(
    lava::SharedDevice device, lava::SharedDescriptorSetLayout textureLayout,
    std::shared_ptr<lava::features::GlfwOutput> glfwOutput,
    std::shared_ptr<lava::features::GlfwWindow> glfwWindow)
    : mDevice(device),
      mGlfwOutput(glfwOutput),
      mWindow(glfwWindow),
      mGui(lava::imgui::ImGui(mDevice, vk::ImageLayout::ePresentSrcKHR)) {
    DR_PROFILE_FUNCTION();

    setupPipeline(textureLayout);

    mOpaqueUntextured =
        GraphicsPipelineFactory::createRenderer_opaqueUntextured(
            mDevice, mPlLayout, mPipeline);
    mOpaqueTextured = GraphicsPipelineFactory::createRenderer_opaqueTextured(
        mDevice, mPlLayout, mPipeline);
    mTransparendUntextured =
        GraphicsPipelineFactory::createRenderer_transparentUntextured(
            mDevice, mPlLayout, mPipeline);
    mTransparendTextured =
        GraphicsPipelineFactory::createRenderer_transparentTextured(
            mDevice, mPlLayout, mPipeline);
    mShadowMap = GraphicsPipelineFactory::createRenderer_shadowMap(
        mDevice, mPlLayout, mPipeline);
}

void RenderingSystem::Render(
    entt::basic_view<entt::entity, entt::exclude_t<>, RenderComponent,
                     TransformComponent>
        entities) {
    DR_PROFILE_FUNCTION();

    if (GetCurrentScene() == 0) {
        return;
    }

    std::vector<std::tuple<RenderComponent&, TransformComponent&>>
        opaqueUntexturedObjects, opaqueTexturedObjects,
        transparendUntexturedObjects, transparendTexturedObjects,
        shadowThrowingObjects =
            std::vector<std::tuple<RenderComponent&, TransformComponent&>>();

    for (auto entity : entities) {
        auto [renderer, transform] =
            entities.get<RenderComponent, TransformComponent>(entity);

        // TODO this is actually bad code... it results in a lot of copying
        // components around. This needs to be fixed.
        auto tuple = entities.get<RenderComponent, TransformComponent>(entity);
        if (renderer.active) {
            if (renderer.isThrowingShadow) {
                shadowThrowingObjects.push_back(tuple);
            }
            if (renderer.hasTexture) {
                renderer.isTransparent
                    ? transparendTexturedObjects.push_back(tuple)
                    : opaqueTexturedObjects.push_back(tuple);
            } else {
                renderer.isTransparent
                    ? transparendUntexturedObjects.push_back(tuple)
                    : opaqueUntexturedObjects.push_back(tuple);
            }
        }
    }

    mDevice->graphicsQueue().handle().waitIdle();

    /*find camera using the system mechanic and calculate view and proj matrix
     * here.*/
    Entity cameraEntity;

    auto cameraComponentView =
        this->GetEntitiesWithComponents<CameraComponent>();

    for (auto tempCameraEntity : cameraComponentView) {
        auto& cameraComp =
            cameraComponentView.get<CameraComponent>(tempCameraEntity);
        if (cameraComp.IsMainCamera) {
            cameraEntity = this->GetEntityFromId(tempCameraEntity);
            break;
        }
    }
    if (!cameraEntity) {
        lava::log(lava::LogLevel::Error) << "Could not find camera entity to "
                                            "render from. Skipping this frame.";
        return;
    }

    auto cameraTransformComp =
        cameraEntity.GetComponent<DCore::ComponentSystem::TransformComponent>();

    auto cameraComp =
        cameraEntity.GetComponent<DCore::ComponentSystem::CameraComponent>();

    // calculate view matrix from camera transform
    /*glm::mat4 trans = glm::mat4(1.0f);
    trans[3][0] = -cameraTransformComp.position.x;
    trans[3][1] = -cameraTransformComp.position.y;
    trans[3][2] = -cameraTransformComp.position.z;//*/
    glm::mat4 trans = glm::translate(glm::vec3(0));

    glm::mat4 rotX =
        glm::rotate(cameraTransformComp.rotation.x, glm::vec3(1, 0, 0));
    glm::mat4 rotY =
        glm::rotate(cameraTransformComp.rotation.y, glm::vec3(0, 1, 0));
    glm::mat4 rotZ =
        glm::rotate(cameraTransformComp.rotation.z, glm::vec3(0, 0, 1));

    glm::mat4 rotMat = rotX * rotY * rotZ;
    auto viewMatrixCam = rotMat * trans;

    {
        DR_PROFILE_SCOPE("After graphics queue idle");

        {
            auto guiframe = mGui.frame();
            SceneHandler::getCurrentScene()->imGuiRender();
            guiframe.~ImGuiFrame();
        }

        auto frame = mWindow->startFrame();
        auto cmd = mDevice->graphicsQueue().beginCommandBuffer();

        cmd.wait(frame.imageReady());

        // Create light view and projection matrix
        glm::mat4 lightProjMatrix;
        glm::mat4 lightViewMatrix;

        std::tie(lightProjMatrix, lightViewMatrix) =
            this->rotateCameraFrustrumCornersToLightSpace(
                glm::vec3(0.5f, 1.0f, -0.5f),
                glm::vec3(0),  // cameraTransformComp.position,
                cameraComp.getProjectionMatrix() * viewMatrixCam,
                glm::vec3(0, 1, 0));
        {
            CameraDataPrePass matrixData{lightViewMatrix, lightProjMatrix};
            mViewProjBufferPrePass->setDataVRAM(&matrixData, sizeof(matrixData),
                                                cmd);
        }

        // load scene camera
        {
            CameraDataForwardPass matrixData{viewMatrixCam,
                                             cameraComp.getProjectionMatrix(),
                                             lightProjMatrix * lightViewMatrix};
            mViewProjBufferForwardPass->setDataVRAM(&matrixData,
                                                    sizeof(matrixData), cmd);
        }

        // render all objects.
        // Note that this includes two render passes.
        // The first one beeing for rendering objects to the shadow map and the
        // second one rendering all objects.
        mPipeline->render(
            cmd, companionWindowFBO[frame.imageIndex()],
            [&](lava::pipeline::AdvancedRenderPass const& pass) {
                DR_PROFILE_FUNCTION();
                auto sub = pass.pass.startInlineSubpass();

                if (pass.type == lava::pipeline::RenderPassType::Shadow) {
                    DR_PROFILE_SCOPE(
                        "Shadow map render pass cmd buffer builder");
                    sub.setViewports(
                        {{0, 0, float(GlobalSettings::shadowMapSize),
                          float(GlobalSettings::shadowMapSize)}});

                    mShadowMap->prepareRendering(&sub, mViewProjDescriptorPre);
                    mShadowMap->renderGameObjects(shadowThrowingObjects,
                                                  cameraTransformComp.position);
                } else if (pass.type ==
                           lava::pipeline::RenderPassType::Opaque) {
                    DR_PROFILE_SCOPE("Opaque render pass cmd buffer builder");

                    sub.setViewports({{0, 0, float(mWindow->width()),
                                       float(mWindow->height())}});

                    if (opaqueUntexturedObjects.size() > 0) {
                        mOpaqueUntextured->prepareRendering(
                            &sub, mViewProjDescriptorForward);
                        mOpaqueUntextured->renderGameObjects(
                            opaqueUntexturedObjects,
                            cameraTransformComp.position);
                    }

                    if (opaqueTexturedObjects.size() > 0) {
                        mOpaqueTextured->prepareRendering(
                            &sub, mViewProjDescriptorForward);
                        mOpaqueTextured->renderGameObjects(
                            opaqueTexturedObjects,
                            cameraTransformComp.position);
                    }

                    if (transparendUntexturedObjects.size() > 0) {
                        mTransparendUntextured->prepareRendering(
                            &sub, mViewProjDescriptorForward);
                        mTransparendUntextured->renderGameObjects(
                            transparendUntexturedObjects,
                            cameraTransformComp.position);
                    }

                    if (transparendTexturedObjects.size() > 0) {
                        mTransparendTextured->prepareRendering(
                            &sub, mViewProjDescriptorForward);
                        mTransparendTextured->renderGameObjects(
                            transparendTexturedObjects,
                            cameraTransformComp.position);
                    }
                }
            });

        frame.image()->changeLayout(vk::ImageLayout::ePresentSrcKHR,
                                    vk::ImageLayout::eColorAttachmentOptimal,
                                    cmd);
        mGui.render(frame.imageIndex(), cmd);

        cmd.signal(frame.renderingComplete());
    }
}

void RenderingSystem::Resize(int width, int height) {
    auto cameraComponentView =
        this->GetEntitiesWithComponents<CameraComponent>();

    for (auto tempCameraEntity : cameraComponentView) {
        auto& cameraComp =
            cameraComponentView.get<CameraComponent>(tempCameraEntity);
        if (cameraComp.IsMainCamera) {
            cameraComp.resize(width, height);
        }
    }

    mPipeline->resize(width, height);
}

std::tuple<glm::mat4, glm::mat4>
RenderingSystem::rotateCameraFrustrumCornersToLightSpace(
    glm::vec3 lightDir, glm::vec3 camPosition, glm::mat4 cameraViewProj,
    glm::vec3 upDirection = glm::vec3(0, 1, 0)) {
    DR_PROFILE_FUNCTION();

    // this works as we center the camera to position (0,0,0).
    float minX = -50.0f;
    float maxX = 50.0f;
    float minY = -50.0f;
    float maxY = 50.0f;
    float minZ = -50.0f;
    float maxZ = 50.0f;

    glm::vec3 frustumCenter = glm::vec3(
        (maxX + minX) / 2.0f, (maxY + minY) / 2.0f, (maxZ + minZ) / 2.0f);

    float maxDistance = 100.0;

    glm::mat4 proj = glm::orthoRH_ZO(maxDistance, -maxDistance, maxDistance,
                                     -maxDistance, 0.0f, maxDistance * 2.0f);

    glm::vec3 newEyePosition =
        frustumCenter - glm::normalize(lightDir) * maxDistance;
    glm::mat4 view = glm::lookAt(newEyePosition, newEyePosition + lightDir,
                                 glm::vec3(0, 1, 0));

    return std::tuple<glm::mat4, glm::mat4>(proj, view);
}

void RenderingSystem::setupPipeline(
    const lava::SharedDescriptorSetLayout textureLayout) {
    DR_PROFILE_FUNCTION();

    // create CameraDataBuffer
    {// pre pass
     {mViewProjBufferPrePass =
          mDevice->createBuffer(lava::uniformBuffer(sizeof(CameraDataPrePass)));

    mViewProjBufferPrePass->keepStagingBuffer();
    mViewProjBufferPrePass->realizeVRAM();

    auto dslinfo = lava::DescriptorSetLayoutCreateInfo{};
    dslinfo.addUniformBuffer(vk::ShaderStageFlagBits::eAllGraphics);
    dslinfo.addUniformBuffer(vk::ShaderStageFlagBits::eAllGraphics);

    mViewProjDescriptorSetLayoutPrePass = dslinfo.create(mDevice);

    mViewProjDescriptorPre =
        mViewProjDescriptorSetLayoutPrePass->createDescriptorSet();
    mViewProjDescriptorPre->writeUniformBuffer(mViewProjBufferPrePass, 0);
}

// forward pass
{
    mViewProjBufferForwardPass = mDevice->createBuffer(
        lava::uniformBuffer(sizeof(CameraDataForwardPass)));

    mViewProjBufferForwardPass->keepStagingBuffer();
    mViewProjBufferForwardPass->realizeVRAM();

    auto dslinfo = lava::DescriptorSetLayoutCreateInfo{};
    dslinfo.addUniformBuffer(vk::ShaderStageFlagBits::eAllGraphics);
    dslinfo.addUniformBuffer(vk::ShaderStageFlagBits::eAllGraphics);

    mViewProjDescriptorSetLayoutForwarPass = dslinfo.create(mDevice);

    mViewProjDescriptorForward =
        mViewProjDescriptorSetLayoutForwarPass->createDescriptorSet();
    mViewProjDescriptorForward->writeUniformBuffer(mViewProjBufferForwardPass,
                                                   0);
}
}

// Object Rendering Pipeline
{
    VkPushConstantRange pushConstantRange{VK_SHADER_STAGE_ALL, 0,
                                          sizeof(PushConstants)};

    mPipeline = std::make_shared<lava::pipeline::AdvancedRenderingPipeline>(
        mDevice, mGlfwOutput->format());

    mPlLayout = mDevice->createPipelineLayout(
        {pushConstantRange},
        {mViewProjDescriptorForward->layout(), textureLayout,
         mPipeline->mForwardDescriptorLayout});
}

mGui.connectWindow(mWindow);

mWindow->buildSwapchainWith(
    [&](std::vector<lava::SharedImageView> const& views) {
        mPipeline->resize(mWindow->width(), mWindow->height());
        companionWindowFBO.clear();
        for (auto& view : views)
            companionWindowFBO.push_back(
                mPipeline->outputPass()->createFramebuffer({view}));
        mGui.prepare(views);
    });

// enable FXAA
mPipeline->setFXAA(true);
}