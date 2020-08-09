#include "RenderingSystem.hh"

#include <thread>
#include <limits>
#include <lava/createinfos/Sampler.hh>

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <lava/common/log.hh>
#include <lava/features/MultiView.hh>
#include <lava/features/GlfwOutput.hh>
#include <lava/gpuselection/NthOfTypeStrategy.hh>
#include <lava/objects/Instance.hh>
#include <lava-extras/camera/GenericCamera.hh>
#include <lava/createinfos/Images.hh>
#include <lava/objects/Image.hh>
#include <lava/objects/Framebuffer.hh>
#include <lava/objects/ImageView.hh>
#include <lava/objects/DescriptorSetLayout.hh>
#include <lava/objects/Buffer.hh>
#include <lava/createinfos/Buffers.hh>
#include <lava/createinfos/DescriptorSetLayoutCreateInfo.hh>
#include <RenderingSystem/Pipeline/GraphicsPipelineFactory.cc>

RenderingSystem::RenderingSystem(
	lava::SharedDevice device,
	lava::SharedDescriptorSetLayout textureLayout,
	std::shared_ptr<lava::features::GlfwOutput> glfwOutput,
	std::shared_ptr<lava::features::GlfwWindow> glfwWindow
) : mDevice(device), mGlfwOutput(glfwOutput), mWindow(glfwWindow)
{
	setupPipeline(textureLayout);

	mOpaqueUntextured = GraphicsPipelineFactory::createRenderer_opaqueUntextured(mDevice, mPlLayout, mPipeline);
	mOpaqueTextured = GraphicsPipelineFactory::createRenderer_opaqueTextured(mDevice, mPlLayout, mPipeline);
	mTransparendUntextured = GraphicsPipelineFactory::createRenderer_transparentUntextured(mDevice, mPlLayout, mPipeline);
	mTransparendTextured = GraphicsPipelineFactory::createRenderer_transparentTextured(mDevice, mPlLayout, mPipeline);
	mShadowMap = GraphicsPipelineFactory::createRenderer_shadowMap(mDevice, mPlLayout, mPipeline);
}

void RenderingSystem::Render(entt::basic_view<entt::entity, entt::exclude_t<>, RenderComponent, TransformComponent> entities)
{
	std::vector<std::tuple<RenderComponent&, TransformComponent&>>
		opaqueUntexturedObjects,
		opaqueTexturedObjects,
		transparendUntexturedObjects,
		transparendTexturedObjects,
		shadowThrowingObjects = std::vector<std::tuple<RenderComponent&, TransformComponent&>>();

	for each (auto entity in entities)
	{
		auto& [renderer, transform] = entities.get<RenderComponent, TransformComponent>(entity);

		// TODO this is actually bad code... it results in a lot of copying components around. This needs to be fixed.
		auto tuple = entities.get<RenderComponent, TransformComponent>(entity);
		if (renderer.active)
		{
			if (renderer.isThrowingShadow) {
				shadowThrowingObjects.push_back(tuple);
			}
			if (renderer.hasTexture)
			{
				renderer.isTransparent ? transparendTexturedObjects.push_back(tuple) : opaqueTexturedObjects.push_back(tuple);
			}
			else
			{
				renderer.isTransparent ? transparendUntexturedObjects.push_back(tuple) : opaqueUntexturedObjects.push_back(tuple);
			}
		}
	}

	mDevice->graphicsQueue().handle().waitIdle();

	{
		auto frame = mWindow->startFrame();
		auto cmd = mDevice->graphicsQueue().beginCommandBuffer();

		cmd.wait(frame.imageReady());

		// Create light view and projection matrix
		glm::mat4 lightProjMatrix;
		glm::mat4 lightViewMatrix;

		std::tie(lightProjMatrix, lightViewMatrix) = this->rotateCameraFrustrumCornersToLightSpace(
			glm::vec3(0.5f, 1.0f, -0.5f),
			mPipeline->getCamera()->getPosition(),
			mPipeline->getCamera()->getUpDirection());
		{
			CameraDataPrePass matrixData
			{
				lightViewMatrix,
				lightProjMatrix
			};
			mViewProjBufferPrePass->setDataVRAM(&matrixData, sizeof(matrixData), cmd);
		}

		// load scene camera
		{
			CameraDataForwardPass matrixData
			{
				mPipeline->getCamera()->getViewMatrix(),
				mPipeline->getCamera()->getProjectionMatrix(),
				lightProjMatrix * lightViewMatrix
			};
			mViewProjBufferForwardPass->setDataVRAM(&matrixData, sizeof(matrixData), cmd);
		}

		// render all objects.
		// Note that this includes two render passes.
		// The first one beeing for rendering objects to the shadow map and the second one rendering all objects.
		mPipeline->render(cmd, companionWindowFBO[frame.imageIndex()],
			[&](lava::pipeline::AdvancedRenderPass const& pass) {
				auto sub = pass.pass.startInlineSubpass();

				if (pass.type == lava::pipeline::RenderPassType::Shadow)
				{
					sub.setViewports(
						{ {0, 0, float(mWindow->width()), float(mWindow->height())} });

					mShadowMap->prepareRendering(&sub, mViewProjDescriptorPre);
					mShadowMap->renderGameObjects(shadowThrowingObjects);
				}
				else if (pass.type == lava::pipeline::RenderPassType::Opaque)
				{
					sub.setViewports(
						{ {0, 0, float(mWindow->width()), float(mWindow->height())} });

					if (opaqueUntexturedObjects.size() > 0) {
						mOpaqueUntextured->prepareRendering(&sub, mViewProjDescriptorForward);
						mOpaqueUntextured->renderGameObjects(opaqueUntexturedObjects);
					}

					if (opaqueTexturedObjects.size() > 0) {
						mOpaqueTextured->prepareRendering(&sub, mViewProjDescriptorForward);
						mOpaqueTextured->renderGameObjects(opaqueTexturedObjects);
					}

					if (transparendUntexturedObjects.size() > 0) {
						mTransparendUntextured->prepareRendering(&sub, mViewProjDescriptorForward);
						mTransparendUntextured->renderGameObjects(transparendUntexturedObjects);
					}

					if (transparendTexturedObjects.size() > 0) {
						mTransparendTextured->prepareRendering(&sub, mViewProjDescriptorForward);
						mTransparendTextured->renderGameObjects(transparendTexturedObjects);
					}
				}
			});
		cmd.signal(frame.renderingComplete());
	}
}

void RenderingSystem::Resize(int width, int height) {
	getCamera()->resize(width, height);
	mPipeline->resize(width, height);
}

void RenderingSystem::getFrustumCorners(std::vector<glm::vec4>& corners, glm::mat4 inverseProjection)
{
	corners.clear();

	// homogeneous corner coords
	glm::vec4 hcorners[8];
	// near
	hcorners[0] = glm::vec4(-1, 1, 1, 1);
	hcorners[1] = glm::vec4(1, 1, 1, 1);
	hcorners[2] = glm::vec4(1, -1, 1, 1);
	hcorners[3] = glm::vec4(-1, -1, 1, 1);
	// far
	hcorners[4] = glm::vec4(-1, 1, -1, 1);
	hcorners[5] = glm::vec4(1, 1, -1, 1);
	hcorners[6] = glm::vec4(1, -1, -1, 1);
	hcorners[7] = glm::vec4(-1, -1, -1, 1);

	glm::mat4 inverseProj = inverseProjection;
	for (int i = 0; i < 8; i++) {
		hcorners[i] = inverseProj * hcorners[i];
		hcorners[i] /= hcorners[i].w;

		corners.push_back(hcorners[i]);
	}
}

std::tuple<glm::mat4, glm::mat4> RenderingSystem::rotateCameraFrustrumCornersToLightSpace(
	glm::vec3 lightDir,
	glm::vec3 camPosition,
	glm::vec3 upDirection = glm::vec3(0, 1, 0))
{
	std::vector<glm::vec4> corners;

	glm::vec3 cameraForward = mPipeline->getCamera()->getForwardDirection();
	glm::vec3 cameraUp = mPipeline->getCamera()->getUpDirection();

	glm::mat4 inverseCameraViewProj = glm::inverse(
		mPipeline->getCamera()->getProjectionMatrix()
		* glm::lookAt(glm::vec3(0), glm::vec3(0) + cameraForward, cameraUp)
		* mPipeline->getCamera()->getTranslationMatrix4()
	);

	this->getFrustumCorners(corners, inverseCameraViewProj);

	float minX = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float minY = std::numeric_limits<float>::max();
	float maxY = std::numeric_limits<float>::min();
	float minZ = std::numeric_limits<float>::max();
	float maxZ = std::numeric_limits<float>::min();

	for (auto c : corners) {
		if (c[0] < minX) minX = c[0];
		if (c[0] > maxX) maxX = c[0];
		if (c[1] < minY) minY = c[1];
		if (c[1] > maxY) maxY = c[1];
		if (c[2] < minZ) minZ = c[2];
		if (c[2] > maxZ) maxZ = c[2];
	}

	glm::vec3 frustumCenter = glm::vec3((maxX + minX) / 2.0f, (maxY + minY) / 2.0f, (maxZ + minZ) / 2.0f);

	float maxDistance = 0.0;
	for (auto c : corners) {
		auto tempDistance = glm::distance(glm::vec4(frustumCenter, 1.0f), c);
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
		}
	}

	glm::mat4 proj = glm::orthoRH_ZO(maxDistance, -maxDistance, maxDistance, -maxDistance, 0.0f, maxDistance * 2.0f);

	glm::vec3 newEyePosition = frustumCenter - glm::normalize(lightDir) * maxDistance;
	glm::mat4 view =
		glm::lookAt(newEyePosition, newEyePosition + lightDir, glm::vec3(0, 1, 0));

	return std::tuple<glm::mat4, glm::mat4 >(proj, view);
}

void RenderingSystem::setupPipeline(const lava::SharedDescriptorSetLayout textureLayout)
{
	// create CameraDataBuffer
	{
		// pre pass
		{
			mViewProjBufferPrePass = mDevice->createBuffer(
				lava::uniformBuffer(sizeof(CameraDataPrePass)));

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
			mViewProjDescriptorForward->writeUniformBuffer(mViewProjBufferForwardPass, 0);
		}
	}

	// Object Rendering Pipeline
	{
		VkPushConstantRange pushConstantRange{
			VK_SHADER_STAGE_ALL,
			0,
			sizeof(PushConstants) };

		mPipeline = std::make_shared<lava::pipeline::AdvancedRenderingPipeline>(
			mDevice, mGlfwOutput->format());

		mPlLayout = mDevice->createPipelineLayout(
			{ pushConstantRange },
			{ mViewProjDescriptorForward->layout(), textureLayout, mPipeline->mForwardDescriptorLayout });

		mPipeline->getCamera()->setVerticalFieldOfView(60);
		mPipeline->getCamera()->setFarClippingPlane(25);
		mPipeline->getCamera()->setPosition({ 5, 2, 5 });
	}

	mWindow->buildSwapchainWith(
		[&](std::vector<lava::SharedImageView> const& views) {
			mPipeline->resize(mWindow->width(), mWindow->height());
			companionWindowFBO.clear();
			for (auto& view : views)
				companionWindowFBO.push_back(mPipeline->outputPass()->createFramebuffer({ view }));
		});

	// enable FXAA
	mPipeline->setFXAA(true);
}