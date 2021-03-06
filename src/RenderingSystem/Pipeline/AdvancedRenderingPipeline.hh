#pragma once

#include <ComponentBased/BaseComponents.hh>
#include <functional>
#include <glm/vec3.hpp>
#include <lava-extras/camera/fwd.hh>
#include <lava-extras/pipeline/RenderPass.hh>
#include <lava-extras/pipeline/fwd.hh>
#include <lava/common/GlLikeFormats.hh>
#include <lava/common/property.hh>
#include <lava/fwd.hh>
#include <lava/objects/RenderPass.hh>
#include <vector>

namespace lava {
namespace pipeline {
/// <summary>
/// A Forward+ Rendering Pipeline with post-processing support
/// It provides features such as shadow mapping
/// </summary>
class AdvancedRenderingPipeline {
private:
    /// Render width in px
    int mWidth = 2;
    /// Render height in px
    int mHeight = 2;

    // === RENDER TARGETS ===
    SharedImage mImageDepthPre;  // used for shadowMapping
    SharedImageView mViewDepthShadowMap;

    SharedImage mImageColor;  // actual rendering target
    SharedImageView mViewColor;

    SharedImage mImageDepth;
    SharedImageView mViewDepth;

    SharedImage mImageNormal;
    SharedImageView mViewNormal;

    SharedImage mImagePosition;
    SharedImageView mViewPosition;

    SharedImage mImageDeferredLightingResult;
    SharedImageView mViewDeferredLightingResult;

    // === Framebuffers ===
    SharedFramebuffer mFboPre;
    SharedFramebuffer mFboForward;
    SharedFramebuffer mFboDeferredLighting;

    // === (Vulkan) RenderPasses ===
    SharedRenderPass mPassPre;      // 1 subpass
    SharedRenderPass mPassForward;  // 2 subpasses
    SharedRenderPass mPassDeferredLightingOutput;
    SharedRenderPass mPassOutput;

    // === Pipelines ===
    std::vector<SharedGraphicsPipeline> mPipelineSpecializations;

    /// <summary>
    /// Used for applying post processing effects like fxaa
    /// </summary>
    SharedGraphicsPipeline mPipelineOutputPass;

public:
    // === Descriptor Sets
    SharedDescriptorSetLayout mForwardDescriptorLayout;
    SharedDescriptorSet mForwardDescriptor;
    SharedDescriptorSetLayout mDeferredLightingOutputDescriptorLayout;
    SharedDescriptorSet mDeferredLightingOutputDescriptor;
    SharedDescriptorSetLayout mOutputDescriptorLayout;
    SharedDescriptorSet mOutputDescriptor;

    // === SETTINGS ===
    int mDebugSpecialization = 0;
    bool mTransparentPass = true;
    float mDitheringStrength = 1 / 256.f;

    SharedDevice mDevice;
    vk::Format mOutputFormat;

public:  // getter, setter
    LAVA_GETTER(Width);
    LAVA_GETTER(Height);

    LAVA_PROPERTY(DebugSpecialization);
    LAVA_PROPERTY(DitheringStrength);
    LAVA_PROPERTY(TransparentPass);

    int getOutputWidth() const;
    int getOutputHeight() const;

public:
    AdvancedRenderingPipeline(SharedDevice const& device,
                              GenericFormat outputFormat,
                              int numberOfDebugSpecializations = 0);

    /// Resizes the internal pipeline size
    void resize(int w, int h);

    /**
     * @brief executes the whole rendering pipeline
     * @param renderFunc function to call for every renderpass. Use the provided
     * pass information
     */
    void render(
        lava::RecordingCommandBuffer& cmd, lava::SharedFramebuffer const& fbo,
        glm::mat4 directionalLightViewProjMat,
        const std::function<
            void(lava::pipeline::AdvancedRenderPass const& pass)>& renderFunc);

    /// Use this to create the FBOs for the Pipeline to output to
    SharedRenderPass const& outputPass() const { return mPassOutput; }

    /// Use this to create the FBOs for the Pipeline
    SharedRenderPass const& deferredLightingOutputPass() const {
        return mPassDeferredLightingOutput;
    }

    /// Use this to create the Pipelines to render the shadow pass
    SharedRenderPass const& prePass() const { return mPassPre; }

    /// Use this to create the Pipelines to render the forward pass
    SharedRenderPass const& forwardPass() const { return mPassForward; }

private:
    struct CameraDataDirectionalLight {
        glm::mat4 viewProjMat;
        glm::mat4 futureUseMat4;
        float futureUseFloat;
    };
};
}  // namespace pipeline
}  // namespace lava