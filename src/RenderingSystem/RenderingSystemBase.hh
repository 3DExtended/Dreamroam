#pragma once

#include <ComponentBased/BaseComponents.hh>
#include <ComponentBased/Systems/Base/SystemBase.hh>
#include <Utils/Debug/Profiling.hh>
#include <lava/objects/Device.hh>
#include <map>
#include <memory>
#include <string>

#include "RenderComponent.hh"

namespace DCore {
namespace ComponentSystem {
class RenderingSystemBase
    : public SystemBase<RenderComponent, TransformComponent> {
public:
    RenderingSystemBase() = default;

    ~RenderingSystemBase() = default;

    virtual void Render(entt::basic_view<entt::entity, entt::exclude_t<>,
                                         RenderComponent, TransformComponent>
                            entities){};
    virtual void Resize(int width, int height){};

private:
    friend class SceneHandler;
    virtual void InternalRender(entt::registry& reg) {
        DR_PROFILE_FUNCTION();

        this->Render(GetEntitiesFromRegistry(reg));
    }
};
}  // namespace ComponentSystem
}  // namespace DCore