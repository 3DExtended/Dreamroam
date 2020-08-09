#pragma once
#include <RenderingSystem/Renders/RendererBase.hh>
#include <RenderingSystem/RenderComponent.hh>
#include <ComponentBased/Entity.hh>

using namespace DCore::ComponentSystem;
namespace DCore {
	namespace Rendering {
		/// <summary>
		/// Renderer for textured objects.
		/// </summary>
		class DefaultTexturedRenderer : public RendererBase
		{
			using RendererBase::RendererBase;

		private:
			void renderSingleGameObject(const std::tuple<RenderComponent&, TransformComponent&> go) override;
		};
	}
}