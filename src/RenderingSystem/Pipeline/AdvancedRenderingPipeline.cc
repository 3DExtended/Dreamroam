#include "AdvancedRenderingPipeline.hh"

#include <Utils/Base.hh>
#include <array>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <lava-extras/camera/FixedCamera.hh>
#include <lava-extras/camera/GenericCamera.hh>
#include <lava-extras/pack/pack.hh>
#include <lava/createinfos/DescriptorSetLayoutCreateInfo.hh>
#include <lava/createinfos/Images.hh>
#include <lava/createinfos/PipelineShaderStageCreateInfo.hh>
#include <lava/createinfos/RenderPassCreateInfo.hh>
#include <lava/createinfos/Sampler.hh>
#include <lava/objects/DescriptorSet.hh>
#include <lava/objects/DescriptorSetLayout.hh>
#include <lava/objects/Device.hh>
#include <lava/objects/Framebuffer.hh>
#include <lava/objects/GraphicsPipeline.hh>
#include <lava/objects/Image.hh>
#include <lava/objects/ImageView.hh>
#include <lava/objects/RenderPass.hh>
#include <lava/raii/ActiveRenderPass.hh>

using namespace lava;
using namespace lava::pipeline;

int AdvancedRenderingPipeline::getOutputWidth() const {
    return mCamera ? mCamera->getViewportWidth() : mWidth;
}

int AdvancedRenderingPipeline::getOutputHeight() const {
    return mCamera ? mCamera->getViewportHeight() : mHeight;
}

AdvancedRenderingPipeline::AdvancedRenderingPipeline(const SharedDevice& device,
                                                     GenericFormat outputFormat)
    : mDevice(device), mOutputFormat(outputFormat.vkhpp()) {
    mCamera = std::make_shared<camera::GenericCamera>();
    mCamera->setPosition({0.f, 0.f, 0.f});
    mCamera->setTarget({0.f, 0.f, -1.f});

    {
        auto info = lava::RenderPassCreateInfo{};
        info.addAttachment(
            AttachmentDescription::depth16().clear().finalLayout_ShaderRead());

        auto firstDep =
            SubpassDependency::first()
                .setSrcSubpass(VK_SUBPASS_EXTERNAL)
                .setDstSubpass(0)
                .setSrcStageMask(vk::PipelineStageFlagBits::eBottomOfPipe)
                .setDstStageMask(vk::PipelineStageFlagBits::eLateFragmentTests)
                .setDstAccessMask(
                    vk::AccessFlagBits::eDepthStencilAttachmentRead |
                    vk::AccessFlagBits::eDepthStencilAttachmentWrite)
                .setDependencyFlags(vk::DependencyFlagBits::eByRegion);
        info.addDependency(firstDep);

        auto secondDep =
            SubpassDependency::first()
                .setSrcSubpass(0)
                .setDstSubpass(VK_SUBPASS_EXTERNAL)
                .setSrcStageMask(vk::PipelineStageFlagBits::eLateFragmentTests)
                .setDstStageMask(vk::PipelineStageFlagBits::eFragmentShader)
                .setSrcAccessMask(
                    vk::AccessFlagBits::eDepthStencilAttachmentRead |
                    vk::AccessFlagBits::eDepthStencilAttachmentWrite)
                .setDstAccessMask(vk::AccessFlagBits::eShaderRead)
                .setDependencyFlags(vk::DependencyFlagBits::eByRegion);
        info.addDependency(secondDep);

        info.addSubpass(SubpassDescription{}.depth(0));
        mPassPre = mDevice->createRenderPass(info);
        std::array<float, 4> clearColor = {1.0f, 1.0f, 1.0f, 1.0f};
        mPassPre->setClearColor(vk::ClearColorValue(clearColor));
    }

    {
        auto info = lava::RenderPassCreateInfo{};
        info.addAttachment(AttachmentDescription::depth32float()
                               .clear()
                               .finalLayout_DepthStencilRead());
        info.addAttachment(AttachmentDescription::color(Format::RGBA16F)
                               .clear()
                               .finalLayout_ShaderRead());
        info.addDependency(SubpassDependency::first().sampleDepthStencil());
        info.addDependency(SubpassDependency(0, 1).reuseDepthStencil());
        info.addSubpass(SubpassDescription{}.depth(0));
        info.addSubpass(SubpassDescription{}.depth(0).colors({1}));

        mPassForward = mDevice->createRenderPass(info);
        mPassForward->setClearDepthStencil(vk::ClearDepthStencilValue(1.0));
    }

    // Output pass (used for FXAA)
    {
        auto info = lava::RenderPassCreateInfo{};
        info.addAttachment(AttachmentDescription::color(mOutputFormat)
                               .clear()
                               .finalLayout_PresentSrc());
        info.addDependency(SubpassDependency::first().sampleColor());
        info.addSubpass(SubpassDescription{}.colors({0}));

        mPassOutput = mDevice->createRenderPass(info);

        auto dsinfoForward = DescriptorSetLayoutCreateInfo{};
        dsinfoForward.addBinding(vk::DescriptorType::eCombinedImageSampler,
                                 vk::ShaderStageFlagBits::eFragment, 1);
        dsinfoForward.addBinding(vk::DescriptorType::eCombinedImageSampler,
                                 vk::ShaderStageFlagBits::eFragment, 1);
        mForwardDescriptorLayout =
            mDevice->createDescriptorSetLayout(dsinfoForward);

        auto dsinfoOutput = DescriptorSetLayoutCreateInfo{};
        dsinfoOutput.addBinding(vk::DescriptorType::eCombinedImageSampler,
                                vk::ShaderStageFlagBits::eFragment, 1);
        mOutputDescriptorLayout =
            mDevice->createDescriptorSetLayout(dsinfoOutput);

        auto layout =
            mDevice->createPipelineLayout({}, {mOutputDescriptorLayout});

        auto infoFXAA = lava::GraphicsPipelineCreateInfo::defaults();
        infoFXAA.setLayout(layout);
        infoFXAA.addStage(
            lava::pack::shader(device, "lava-extras/pipeline/output.vert"));
        infoFXAA.addStage(
            lava::pack::shader(device, "lava-extras/pipeline/output.frag"));

        infoFXAA.stage(1).specialize(0, false);  // Disable FXAA
        mPipelineOutputNoFXAA = mPassOutput->createPipeline(0, infoFXAA);

        infoFXAA.stage(1).specialize(0, true);  // Enable FXAA
        mPipelineOutputFXAA = mPassOutput->createPipeline(0, infoFXAA);
    }
}

void AdvancedRenderingPipeline::resize(int w, int h) {
    if (w == mWidth && h == mHeight) return;  // no change

    mWidth = w;
    mHeight = h;

    mImageDepthPre =
        lava::attachment2D(mWidth, mHeight, Format::DEPTH_COMPONENT16)
            .setUsage(vk::ImageUsageFlagBits::eDepthStencilAttachment |
                      vk::ImageUsageFlagBits::eSampled)
            .create(mDevice);
    mImageDepthPre->realizeAttachment();
    mViewDepthPre = mImageDepthPre->createView(
        vk::ImageSubresourceRange{}
            .setAspectMask(vk::ImageAspectFlagBits::eDepth)
            .setBaseArrayLayer(0)
            .setBaseMipLevel(0)
            .setLevelCount(1)
            .setLayerCount(1));

    mImageColor =
        lava::attachment2D(mWidth, mHeight, Format::RGBA16F).create(mDevice);
    mImageColor->realizeAttachment();
    mViewColor = mImageColor->createView();

    mImageDepth =
        lava::attachment2D(mWidth, mHeight, Format::DEPTH_COMPONENT32F)
            .create(mDevice);
    mImageDepth->realizeAttachment();
    mViewDepth = mImageDepth->createView();

    mFboPre = mPassPre->createFramebuffer({mViewDepthPre});

    mFboForward = mPassForward->createFramebuffer({mViewDepth, mViewColor});

    auto forwardSampler = mDevice->createSampler(
        SamplerCreateInfo{}
            .setMagFilter(vk::Filter::eLinear)
            .setMinFilter(vk::Filter::eLinear)
            .setMipmapMode(vk::SamplerMipmapMode::eNearest)
            .setAddressModeU(vk::SamplerAddressMode::eClampToEdge)
            .setAddressModeV(vk::SamplerAddressMode::eClampToEdge)
            .setAddressModeW(vk::SamplerAddressMode::eClampToEdge)
            .setMipLodBias(0.0f)
            .setMaxAnisotropy(1.0f)
            .setMinLod(0.0f)
            .setMaxLod(1.0f)
            .setBorderColor(vk::BorderColor::eFloatOpaqueWhite));
    mForwardDescriptor = mForwardDescriptorLayout->createDescriptorSet();
    mForwardDescriptor->writeCombinedImageSampler(
        {forwardSampler, mViewDepthPre}, 1);

    auto outputSampler = mDevice->createSampler(
        SamplerCreateInfo{}.setUnnormalizedCoordinates(true));
    mOutputDescriptor = mOutputDescriptorLayout->createDescriptorSet();
    mOutputDescriptor->writeCombinedImageSampler({outputSampler, mViewColor},
                                                 0);
}

void AdvancedRenderingPipeline::assignCamera(
    const camera::SharedGenericCamera& cam, bool useCamViewport) {
    mCamera = cam;

    if (cam && useCamViewport)
        resize(cam->getViewportWidth(), cam->getViewportHeight());
}

void AdvancedRenderingPipeline::render(
    lava::RecordingCommandBuffer& cmd, lava::SharedFramebuffer const& fbo,
    std::function<void(lava::pipeline::AdvancedRenderPass const& pass)> const&
        renderFunc) {
    DR_ASSERT(renderFunc != nullptr && "no render function provided");
    DR_ASSERT(mCamera != nullptr && "no camera provided");

    camera::FixedCamera cam(mCamera->getPosition(),          //
                            mCamera->getViewMatrix(),        //
                            mCamera->getProjectionMatrix(),  //
                            mCamera->getViewportSize());

    // mImageDepthPre->changeLayout(vk::ImageLayout::eGeneral, cmd);
    {
        auto pass = cmd.beginRenderpass(mFboPre);
        {
            AdvancedRenderPass rp{RenderPassType::Shadow, this, cam, mFboPre,
                                  pass};
            renderFunc(rp);
        }
    }
    // mImageDepthPre->changeLayout(vk::ImageLayout::eGeneral, cmd);
    {
        auto pass = cmd.beginRenderpass(mFboForward);
        // z-Pre
        {
            AdvancedRenderPass rp{RenderPassType::ZPre, this, cam, mFboForward,
                                  pass};
            renderFunc(rp);
        }

        {
            AdvancedRenderPass rp{RenderPassType::Opaque, this, cam,
                                  mFboForward, pass};
            renderFunc(rp);
        }
    }

    {
        auto pass = cmd.beginRenderpass(fbo);
        auto sub = pass.startInlineSubpass();

        sub.bindPipeline(mFXAA ? mPipelineOutputFXAA : mPipelineOutputNoFXAA);
        sub.bindDescriptorSets({mOutputDescriptor});

        sub.draw(3);
    }
}