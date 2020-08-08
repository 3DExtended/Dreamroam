#include "GraphicsPipelineRenderer.hh"

using namespace DCore::Rendering;

GraphicsPipelineRenderer::GraphicsPipelineRenderer(
	std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> advancedPipeline,
	lava::SharedGraphicsPipeline pipeline,
	lava::SharedPipelineLayout layout)
	: mPipeline(pipeline),
	mLayout(layout),
	mAdvancedPipeline(advancedPipeline)
{
}

void GraphicsPipelineRenderer::prepareRendering(
	lava::InlineSubpass* sub, lava::SharedDescriptorSet cameraDescriptor)
{
	mCurrentSubpass = sub;
	mCameraDescriptor = cameraDescriptor;
	mCurrentSubpass->bindPipeline(mPipeline);
}

void GraphicsPipelineRenderer::renderGameObjects(const std::vector<std::tuple<RenderComponent&, TransformComponent&>>& gos)
{
	for (auto go : gos)
	{
		renderSingleGameObject(go);
	}
}