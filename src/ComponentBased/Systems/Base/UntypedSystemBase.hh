#pragma once
#include <ComponentBased/Entity.hh>
#include <entt/entt.hpp>

namespace DCore {
namespace ComponentSystem {
class UntypedSystemBase {
public:
    UntypedSystemBase() = default;
    UntypedSystemBase(const UntypedSystemBase& other) = default;

protected:
    Entity GetEntityFromId(entt::entity entityId);

protected:
    friend class AScene;
    friend class SceneHandler;

    virtual void InternalAwake(entt::registry& reg){};
    virtual void InternalStart(entt::registry& reg){};
    virtual void InternalUpdate(entt::registry& reg, double dt){};
    virtual void InternalLateUpdate(entt::registry& reg, double dt){};
    virtual void InternalDestroy(entt::registry& reg){};

    AScene* GetCurrentScene() const { return this->curScene; };

private:
    void InternalSetCurrentScene(AScene* scene) { this->curScene = scene; }
    AScene* curScene = 0;
};
}  // namespace ComponentSystem
}  // namespace DCore