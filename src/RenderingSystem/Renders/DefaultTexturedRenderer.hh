#pragma once
#include <ComponentBased/Entity.hh>
#include <RenderingSystem/RenderComponent.hh>
#include <RenderingSystem/Renders/RendererBase.hh>

using namespace DCore::ComponentSystem;
namespace DCore {
namespace Rendering {
/// <summary>
/// Renderer for textured objects.
/// </summary>
class DefaultTexturedRenderer : public RendererBase {
    using RendererBase::RendererBase;

private:
    void renderSingleGameObject(
        const std::tuple<RenderComponent&, TransformComponent&> go) override;
};
}  // namespace Rendering
}  // namespace DCore