#pragma once
#include <RenderingSystem/Renders/RendererBase.hh>

namespace DCore {
	namespace Rendering {
		/// <summary>
		/// Renderer for non-textured meshes.
		/// </summary>
		class DefaultRenderer : public RendererBase
		{
			using RendererBase::RendererBase;

		private:
			void renderSingleGameObject(const std::tuple<RenderComponent&, TransformComponent&> go) override;
		};
	}
}