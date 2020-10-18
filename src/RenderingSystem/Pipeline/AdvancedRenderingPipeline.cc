#include "AdvancedRenderingPipeline.hh"

#include <GlobalSettings.hh>
#include <RenderingSystem/PushConstants.hh>
#include <Utils/Base.hh>
#include <Utils/Debug/Profiling.hh>
#include <array>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <lava-extras/camera/FixedCamera.hh>
#include <lava-extras/camera/GenericCamera.hh>
#include <lava-extras/pack/pack.hh>
#include <lava/createinfos/Buffers.hh>
#include <lava/createinfos/DescriptorSetLayoutCreateInfo.hh>
#include <lava/createinfos/Images.hh>
#include <lava/createinfos/PipelineShaderStageCreateInfo.hh>
#include <lava/createinfos/RenderPassCreateInfo.hh>
#include <lava/createinfos/Sampler.hh>
#include <lava/objects/Buffer.hh>
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

    // pre pass (input: no images, output: 1 depth texture)
    {
        auto info = lava::RenderPassCreateInfo{};
        // output attachment for depth texture
        info.addAttachment(AttachmentDescription::depth32float()
                               .clear()
                               .finalLayout_ShaderRead());

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

    // forward pass (input: 2 textures; one textureatlas, one shadow map,
    // output: 4 textures; 1 depth texture, 3 g-buffer images)
    {
        auto info = lava::RenderPassCreateInfo{};

        // depth texture output
        info.addAttachment(AttachmentDescription::depth32float()
                               .clear()
                               .finalLayout_ShaderRead());

        // g-buffer color texture output
        info.addAttachment(AttachmentDescription::color(Format::RGBA32F)
                               .clear()
                               .finalLayout_ShaderRead());

        // g-buffer normal texture output
        info.addAttachment(AttachmentDescription::color(Format::RGBA32F)
                               .clear()
                               .finalLayout_ShaderRead());

        // g-buffer position texture output
        info.addAttachment(AttachmentDescription::color(Format::RGBA32F)
                               .clear()
                               .finalLayout_ShaderRead());

        info.addDependency(SubpassDependency::first().sampleDepthStencil());
        info.addDependency(SubpassDependency(0, 1).reuseDepthStencil());

        info.addSubpass(SubpassDescription{}.depth(0));
        info.addSubpass(SubpassDescription{}.depth(0).colors({1, 2, 3}));

        mPassForward = mDevice->createRenderPass(info);
        mPassForward->setClearDepthStencil(vk::ClearDepthStencilValue(1.0));

        auto dsinfoForward = DescriptorSetLayoutCreateInfo{};
        // texture input texture atlas
        dsinfoForward.addBinding(vk::DescriptorType::eCombinedImageSampler,
                                 vk::ShaderStageFlagBits::eFragment, 1);
        // texture input shadow map
        dsinfoForward.addBinding(vk::DescriptorType::eCombinedImageSampler,
                                 vk::ShaderStageFlagBits::eFragment, 1);
        mForwardDescriptorLayout =
            mDevice->createDescriptorSetLayout(dsinfoForward);
    }

    // DeferredLighting Output pass (5 input textures (g-buffers (color, normal,
    // position, depth, shadowmap), 1 output texture color)
    {
        // setup dependencies and attachments
        auto info = lava::RenderPassCreateInfo{};
        info.addAttachment(AttachmentDescription::color(Format::RGBA32F)
                               .clear()
                               .finalLayout_ShaderRead());

        info.addSubpass(SubpassDescription{}.colors({0}));
        info.autoAddDependencies();

        mPassDeferredLightingOutput = mDevice->createRenderPass(info);

        auto dsinfoDeferredLightingOutput = DescriptorSetLayoutCreateInfo{};
        dsinfoDeferredLightingOutput.addBinding(
            vk::DescriptorType::eCombinedImageSampler,
            vk::ShaderStageFlagBits::eFragment, 1);
        dsinfoDeferredLightingOutput.addBinding(
            vk::DescriptorType::eCombinedImageSampler,
            vk::ShaderStageFlagBits::eFragment, 1);
        dsinfoDeferredLightingOutput.addBinding(
            vk::DescriptorType::eCombinedImageSampler,
            vk::ShaderStageFlagBits::eFragment, 1);
        dsinfoDeferredLightingOutput.addBinding(
            vk::DescriptorType::eCombinedImageSampler,
            vk::ShaderStageFlagBits::eFragment, 1);
        dsinfoDeferredLightingOutput.addBinding(
            vk::DescriptorType::eCombinedImageSampler,
            vk::ShaderStageFlagBits::eFragment, 1);

        mDeferredLightingOutputDescriptorLayout =
            mDevice->createDescriptorSetLayout(dsinfoDeferredLightingOutput);

        // setup shader since predetermined
        VkPushConstantRange pushConstantRange{
            VK_SHADER_STAGE_ALL, 0, sizeof(CameraDataDirectionalLight)};

        auto layout = mDevice->createPipelineLayout(
            {pushConstantRange}, {mDeferredLightingOutputDescriptorLayout});

        auto infoDeferredLightingOutput =
            lava::GraphicsPipelineCreateInfo::defaults();
        infoDeferredLightingOutput.setLayout(layout);
        infoDeferredLightingOutput.addStage(
            lava::pack::shader(device, "shaders/output_vert.spv"));
        infoDeferredLightingOutput.addStage(
            lava::pack::shader(device, "shaders/output_frag.spv"));

        for (int i = 0; i < numberOfDebugSpecializations + 1; i++) {
            infoDeferredLightingOutput.stage(1).specialize(0, i);
            mPipelineSpecializations.push_back(
                mPassDeferredLightingOutput->createPipeline(
                    0, infoDeferredLightingOutput));
        }
    }

    // Output pass (used for FXAA) (inputs: 1 color texture, outputs: 1 color
    // texture)
    {
        auto info = lava::RenderPassCreateInfo{};
        info.addAttachment(AttachmentDescription::color(mOutputFormat)
                               .clear()
                               .finalLayout_PresentSrc());
        info.addSubpass(SubpassDescription{}.colors({0}));
        info.autoAddDependencies();

        mPassOutput = mDevice->createRenderPass(info);

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

        infoFXAA.stage(1).specialize(0, true);  // Enable FXAA
        mPipelineOutputPass = mPassOutput->createPipeline(0, infoFXAA);
    }
}

void AdvancedRenderingPipeline::resize(int w, int h) {
    DR_PROFILE_FUNCTION();

    if (w == mWidth && h == mHeight) return;  // no change

    mWidth = w;
    mHeight = h;

    // pre pass (shadow map rendering)
    {
        // attachment (image) for later use of depth buffer
        mImageDepthPre =
            lava::attachment2D(GlobalSettings::shadowMapSize,
                               GlobalSettings::shadowMapSize,
                               Format::DEPTH_COMPONENT32F)
                .setUsage(vk::ImageUsageFlagBits::eDepthStencilAttachment |
                          vk::ImageUsageFlagBits::eSampled)
                .create(mDevice);
        mImageDepthPre->realizeAttachment();
        mViewDepthShadowMap = mImageDepthPre->createView(
            vk::ImageSubresourceRange{}
                .setAspectMask(vk::ImageAspectFlagBits::eDepth)
                .setBaseArrayLayer(0)
                .setBaseMipLevel(0)
                .setLevelCount(1)
                .setLayerCount(1));
        mFboPre = mPassPre->createFramebuffer({mViewDepthShadowMap});
    }

    // rendering to g-buffers: Depth, Color, Normal, Frag. Position
    {
        // G-Buffer depth
        {
            mImageDepth =
                lava::attachment2D(mWidth, mHeight, Format::DEPTH_COMPONENT32F)
                    .create(mDevice);
            mImageDepth->realizeAttachment();
            mViewDepth = mImageDepth->createView();
        }

        // G-Buffer color
        {
            mImageColor = lava::attachment2D(mWidth, mHeight, Format::RGBA32F)
                              .create(mDevice);
            mImageColor->realizeAttachment();
            mViewColor = mImageColor->createView();
        }

        // G-Buffer normal
        {
            mImageNormal = lava::attachment2D(mWidth, mHeight, Format::RGBA32F)
                               .create(mDevice);
            mImageNormal->realizeAttachment();
            mViewNormal = mImageNormal->createView();
        }

        // G-Buffer position
        {
            mImagePosition =
                lava::attachment2D(mWidth, mHeight, Format::RGBA32F)
                    .create(mDevice);
            mImagePosition->realizeAttachment();
            mViewPosition = mImagePosition->createView();
        }

        mFboForward = mPassForward->createFramebuffer(
            {mViewDepth, mViewColor, mViewNormal, mViewPosition});

        auto forwardSampler = mDevice->createSampler(
            SamplerCreateInfo{}
                .setUnnormalizedCoordinates(false)
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
            {forwardSampler, mViewDepthShadowMap}, 1);
    }

    // deferred lighting pass. Combine G-Buffers to one image and output to
    // framebuffer image
    {
        auto deferredOutputSamplerShadowMap = mDevice->createSampler(
            SamplerCreateInfo{}
                .setUnnormalizedCoordinates(false)
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
        auto deferredOutputSampler = mDevice->createSampler(
            SamplerCreateInfo{}.setUnnormalizedCoordinates(true));

        mDeferredLightingOutputDescriptor =
            mDeferredLightingOutputDescriptorLayout->createDescriptorSet();
        mDeferredLightingOutputDescriptor->writeCombinedImageSampler(
            {deferredOutputSampler, mViewColor}, 0);
        mDeferredLightingOutputDescriptor->writeCombinedImageSampler(
            {deferredOutputSampler, mViewNormal}, 1);
        mDeferredLightingOutputDescriptor->writeCombinedImageSampler(
            {deferredOutputSampler, mViewPosition}, 2);
        mDeferredLightingOutputDescriptor->writeCombinedImageSampler(
            {deferredOutputSampler, mViewDepth}, 3);
        mDeferredLightingOutputDescriptor->writeCombinedImageSampler(
            {deferredOutputSamplerShadowMap, mViewDepthShadowMap}, 4);

        // G-Buffer deferred lighting result
        {
            mImageDeferredLightingResult =
                lava::attachment2D(mWidth, mHeight, Format::RGBA32F)
                    .create(mDevice);
            mImageDeferredLightingResult->realizeAttachment();
            mViewDeferredLightingResult =
                mImageDeferredLightingResult->createView();
        }

        mFboDeferredLighting = mPassDeferredLightingOutput->createFramebuffer(
            {mViewDeferredLightingResult});
    }

    // post processing step: fxaa and such
    {
        auto outputSampler = mDevice->createSampler(
            SamplerCreateInfo{}.setUnnormalizedCoordinates(true));
        mOutputDescriptor = mOutputDescriptorLayout->createDescriptorSet();
        mOutputDescriptor->writeCombinedImageSampler(
            {outputSampler, mViewDeferredLightingResult}, 0);
    }
}

void AdvancedRenderingPipeline::render(
    lava::RecordingCommandBuffer& cmd, lava::SharedFramebuffer const& fbo,
    glm::mat4 directionalLightViewProjMat,
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
        auto pass = cmd.beginRenderpass(mFboDeferredLighting);
        auto sub = pass.startInlineSubpass();

        CameraDataDirectionalLight directionalLightMatrix;
        directionalLightMatrix.viewProjMat = directionalLightViewProjMat;
        sub.pushConstantBlock(directionalLightMatrix);

        sub.bindPipeline(mPipelineSpecializations[mDebugSpecialization]);
        sub.bindDescriptorSets({mDeferredLightingOutputDescriptor});

        sub.draw(3);
    }

    {
        auto pass = cmd.beginRenderpass(fbo);
        auto sub = pass.startInlineSubpass();

        sub.bindPipeline(mPipelineOutputPass);
        sub.bindDescriptorSets({mOutputDescriptor});

        sub.draw(3);
    }
}