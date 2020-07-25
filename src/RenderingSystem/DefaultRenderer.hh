#pragma once
#include "GraphicsPipelineRenderer.hh"

/// <summary>
///
/// </summary>
class DefaultRenderer : public GraphicsPipelineRenderer
{
	using GraphicsPipelineRenderer::GraphicsPipelineRenderer;

private:
	void renderSingleGameObject(std::shared_ptr<GameObject> go) override;
};