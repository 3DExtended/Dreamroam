#pragma once
#include "../Pipeline/GraphicsPipelineRenderer.hh"
#include <RenderingSystem/RenderComponent.hh>
#include <ComponentBased/Entity.hh>

using namespace DCore::ComponentSystem;
namespace DCore {
	namespace Rendering {
		class DefaultTexturedRenderer : public GraphicsPipelineRenderer
		{
			using GraphicsPipelineRenderer::GraphicsPipelineRenderer;

		private:
			void renderSingleGameObject(const std::tuple<RenderComponent&, TransformComponent&> go) override;
		};
	}
}