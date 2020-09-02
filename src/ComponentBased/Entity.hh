#pragma once

/**
  DCore is the namespace for the engine.
  It provides access to all the structures needed to apply this engine.
  However, if you'd like to add external functionalities, this namespace should
  provide typesafty.
  */
#include <Utils/Base.hh>
#include <entt/entt.hpp>
#include <lava-extras/camera/fwd.hh>
#include <lava-extras/geometry/fwd.hh>
#include <lava-extras/pipeline/RenderingPipeline.hh>
#include <lava/createinfos/GraphicsPipelineCreateInfo.hh>
#include <lava/fwd.hh>
#include <lava/objects/GraphicsPipeline.hh>
#include <lava/objects/RenderPass.hh>
#include <lava/raii/ActiveRenderPass.hh>

namespace DCore {
namespace ComponentSystem {
class AScene;
class Entity {
public:
    Entity() = default;
    Entity(entt::entity handle, AScene* scene);
    Entity(const Entity& other) = default;

    /// <summary>
    /// Returns the unique id for this entity.
    /// </summary>
    /// <returns>Internal Id for this entity</returns>
    const entt::entity GetEntityId() const { return m_EntityHandle; };

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        DR_ASSERT(!HasComponent<T>(), "Entity already has component!");
        return GetSceneRegistry().emplace<T>(m_EntityHandle,
                                             std::forward<Args>(args)...);
    }

    template <typename T>
    T& GetComponent() {
        DR_ASSERT(HasComponent<T>(), "Entity does not have component!");
        return GetSceneRegistry().get<T>(m_EntityHandle);
    }

    template <typename T>
    bool HasComponent() {
        return GetSceneRegistry().has<T>(m_EntityHandle);
    }

    template <typename T>
    void RemoveComponent() {
        DR_ASSERT(HasComponent<T>(), "Entity does not have component!");
        GetSceneRegistry().remove<T>(m_EntityHandle);
    }

    operator bool() const { return m_EntityHandle != entt::null; }

private:
    entt::entity m_EntityHandle{entt::null};
    AScene* m_Scene = nullptr;

    entt::registry& GetSceneRegistry();
};
}  // namespace ComponentSystem
}  // namespace DCore
