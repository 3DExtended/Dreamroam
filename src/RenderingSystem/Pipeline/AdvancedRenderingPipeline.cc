#include "AdvancedRenderingPipeline.hh"

#include <GlobalSettings.hh>
#include <Utils/Base.hh>
#include <Utils/Debug/Profiling.hh>
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

int AdvancedRenderingPipeline::getOutputWidth() const { return mWidth; }

int AdvancedRenderingPipeline::getOutputHeight() const { return mHeight; }

AdvancedRenderingPipeline::AdvancedRenderingPipeline(
    const SharedDevice& device, GenericFormat outputFormat,
    int numberOfDebugSpecializations)
    : mDevice(device), mOutputFormat(outputFormat.vkhpp()) {
    DR_PROFILE_FUNCTION();

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
                               .finalLayout_ShaderRead());
        info.addAttachment(AttachmentDescription::color(Format::RGBA16F)
                               .clear()
                               .finalLayout_ShaderRead());
        info.addAttachment(AttachmentDescription::color(Format::RGBA16F)
                               .clear()
                               .finalLayout_ShaderRead());
        info.addAttachment(AttachmentDescription::color(Format::RGBA16F)
                               .clear()
                               .finalLayout_ShaderRead());
        info.addDependency(SubpassDependency::first().sampleDepthStencil());
        info.addDependency(SubpassDependency(0, 1).reuseDepthStencil());

        info.addSubpass(SubpassDescription{}.depth(0));
        info.addSubpass(SubpassDescription{}.depth(0).colors({1, 2, 3}));

        mPassForward = mDevice->createRenderPass(info);
        mPassForward->setClearDepthStencil(vk::ClearDepthStencilValue(1.0));
    }

    // Output pass (used for FXAA)
    {
        auto info = lava::RenderPassCreateInfo{};
        info.addAttachment(AttachmentDescription::color(mOutputFormat)
                               .clear()
                               .finalLayout_PresentSrc());
        info.addDependency(SubpassDependency::first().readInFragmentShader());
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
        dsinfoOutput.addBinding(vk::DescriptorType::eCombinedImageSampler,
                                vk::ShaderStageFlagBits::eFragment, 1);
        dsinfoOutput.addBinding(vk::DescriptorType::eCombinedImageSampler,
                                vk::ShaderStageFlagBits::eFragment, 1);
        dsinfoOutput.addBinding(vk::DescriptorType::eCombinedImageSampler,
                                vk::ShaderStageFlagBits::eFragment, 1);
        dsinfoOutput.addBinding(vk::DescriptorType::eCombinedImageSampler,
                                vk::ShaderStageFlagBits::eFragment, 1);

        mOutputDescriptorLayout =
            mDevice->createDescriptorSetLayout(dsinfoOutput);

        auto layout =
            mDevice->createPipelineLayout({}, {mOutputDescriptorLayout});

        auto infoOutput = lava::GraphicsPipelineCreateInfo::defaults();
        infoOutput.setLayout(layout);
        infoOutput.addStage(
            lava::pack::shader(device, "shaders/output_vert.spv"));
        infoOutput.addStage(
            lava::pack::shader(device, "shaders/output_frag.spv"));

        for (int i = 0; i < numberOfDebugSpecializations + 1; i++) {
            infoOutput.stage(1).specialize(0, i);
            mPipelineSpecializations.push_back(
                mPassOutput->createPipeline(0, infoOutput));
        }
    }
}

void AdvancedRenderingPipeline::resize(int w, int h) {
    DR_PROFILE_FUNCTION();

    if (w == mWidth && h == mHeight) return;  // no change

    mWidth = w;
    mHeight = h;

    mImageDepthPre =
        lava::attachment2D(GlobalSettings::shadowMapSize,
                           GlobalSettings::shadowMapSize,
                           Format::DEPTH_COMPONENT16)
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

    mFboPre = mPassPre->createFramebuffer({mViewDepthPre});

    mImageColor =
        lava::attachment2D(mWidth, mHeight, Format::RGBA16F).create(mDevice);
    mImageColor->realizeAttachment();
    mViewColor = mImageColor->createView();

    auto mImageColor2 =
        lava::attachment2D(mWidth, mHeight, Format::RGBA16F).create(mDevice);
    mImageColor2->realizeAttachment();
    auto mViewColor2 = mImageColor2->createView();

    auto mImageColor3 =
        lava::attachment2D(mWidth, mHeight, Format::RGBA16F).create(mDevice);
    mImageColor3->realizeAttachment();
    auto mViewColor3 = mImageColor3->createView();

    mImageDepth =
        lava::attachment2D(mWidth, mHeight, Format::DEPTH_COMPONENT32F)
            .create(mDevice);
    mImageDepth->realizeAttachment();
    mViewDepth = mImageDepth->createView();

    mFboForward = mPassForward->createFramebuffer(
        {mViewDepth, mViewColor, mViewColor2, mViewColor3});

    auto forwardSampler = mDevice->createSampler(
        SamplerCreateInfo{}
            .setMagFilter(vk::Filter::eLinear)
            .setMinFilter(vk::Filter::eLinear)
            .setMipmapMode(vk::SamplerMipmapMode::eLinear)
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

    mOutputDescriptor->writeCombinedImageSampler({outputSampler, mViewColor2},
                                                 1);
    mOutputDescriptor->writeCombinedImageSampler({outputSampler, mViewColor3},
                                                 2);
    mOutputDescriptor->writeCombinedImageSampler({outputSampler, mViewDepth},
                                                 3);
}

void AdvancedRenderingPipeline::render(
    lava::RecordingCommandBuffer& cmd, lava::SharedFramebuffer const& fbo,
    std::function<void(lava::pipeline::AdvancedRenderPass const& pass)> const&
        renderFunc) {
    DR_PROFILE_FUNCTION();

    DR_ASSERT(renderFunc != nullptr && "no render function provided");

    // can not be used..
    camera::FixedCamera cam;

    {
        auto pass = cmd.beginRenderpass(mFboPre);
        {
            AdvancedRenderPass rp{RenderPassType::Shadow, this, cam, mFboPre,
                                  pass};
            renderFunc(rp);
        }
    }
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

        sub.bindPipeline(mPipelineSpecializations[mDebugSpecialization]);
        sub.bindDescriptorSets({mOutputDescriptor});

        sub.draw(3);
    }
}