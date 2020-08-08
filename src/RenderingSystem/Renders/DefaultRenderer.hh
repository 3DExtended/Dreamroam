#pragma once
#include "GraphicsPipelineRenderer.hh"

namespace DCore {
	namespace Rendering {
		class DefaultRenderer : public GraphicsPipelineRenderer
		{
			using GraphicsPipelineRenderer::GraphicsPipelineRenderer;

		private:
			void renderSingleGameObject(const std::tuple<RenderComponent&, TransformComponent&> go) override;
		};
	}
}