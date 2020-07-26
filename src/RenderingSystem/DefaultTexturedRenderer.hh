#pragma once
#include "GraphicsPipelineRenderer.hh"
#include "PushConstants.hh"
#include <Components/RenderComponent.hh>
#include <ComponentBased/GameObject.hh>
namespace DCore {
	namespace Rendering {
		class DefaultTexturedRenderer : public GraphicsPipelineRenderer
		{
			using GraphicsPipelineRenderer::GraphicsPipelineRenderer;

		private:
			void renderSingleGameObject(const std::shared_ptr<GameObject>& go) override;
		};
	}
}