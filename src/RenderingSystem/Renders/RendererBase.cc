#include "RendererBase.hh"

using namespace DCore::Rendering;

RendererBase::RendererBase(
    std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> advancedPipeline,
    lava::SharedGraphicsPipeline pipeline, lava::SharedPipelineLayout layout)
    : mPipeline(pipeline),
      mLayout(layout),
      mAdvancedPipeline(advancedPipeline) {}

void RendererBase::prepareRendering(
    lava::InlineSubpass* sub, lava::SharedDescriptorSet cameraDescriptor) {
    mCurrentSubpass = sub;
    mCameraDescriptor = cameraDescriptor;
    mCurrentSubpass->bindPipeline(mPipeline);
}

void RendererBase::renderGameObjects(
    const std::vector<std::tuple<RenderComponent&, TransformComponent&>>& gos) {
    for (auto go : gos) {
        renderSingleGameObject(go);
    }
}