#pragma once
#include "GraphicsPipelineRenderer.hh"

class DefaultRenderer : public GraphicsPipelineRenderer
{
  using GraphicsPipelineRenderer::GraphicsPipelineRenderer;

private:
  void renderSingleGameObject(std::shared_ptr<GameObject> go) override;
};
