#pragma once
#include "GraphicsPipelineRenderer.hh"
#include "PushConstants.hh"
#include <Components/RenderComponent.hh>
#include <ComponentBased/GameObject.hh>

class DefaultTexturedRenderer : public GraphicsPipelineRenderer
{
  using GraphicsPipelineRenderer::GraphicsPipelineRenderer;

private:
  void renderSingleGameObject(std::shared_ptr<GameObject> go) override;
};
