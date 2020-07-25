#pragma once
#include "GraphicsPipelineRenderer.hh"

namespace DCore {
	namespace Rendering {
		class DefaultRenderer : public GraphicsPipelineRenderer
		{
			using GraphicsPipelineRenderer::GraphicsPipelineRenderer;

		private:
			void renderSingleGameObject(std::shared_ptr<GameObject> go) override;
		};
	}
}