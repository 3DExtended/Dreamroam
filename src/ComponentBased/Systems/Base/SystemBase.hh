#pragma once

/**
  DCore is the namespace for the engine.
  It provides access to all the structures needed to apply this engine.
  However, if you'd like to add external functionalities, this namespace should
  provide typesafty.
  */

#include <entt/entt.hpp>
#include <lava-extras/camera/fwd.hh>
#include <lava-extras/geometry/fwd.hh>
#include <lava-extras/pipeline/RenderingPipeline.hh>
#include <lava/createinfos/GraphicsPipelineCreateInfo.hh>
#include <lava/fwd.hh>
#include <lava/objects/GraphicsPipeline.hh>
#include <lava/objects/RenderPass.hh>
#include <lava/raii/ActiveRenderPass.hh>

#include "../../AScene.hh"
#include "UntypedSystemBase.hh"

namespace DCore {
namespace ComponentSystem {
/// <summary>
/// System base is the recommended method for accessing your entities and their
/// components. The system originates from the core concept of ECS (entity
/// component systems): You write custom components which can be assigned to
/// entities. When you want to update those components (or want to read them),
/// you have to create a system.
///
/// For this system you have to specify before hand, which components you try to
/// access. For example, a RenderingSystem has to access the RenderComponent and
/// the transform component of all entities. (If an entity doesn't provide both,
/// we don't want to access it in our RenderingSystem).
///	Thus, the actual rendering system in this engine implements:
///    class RenderingSystemBase : public SystemBase<RenderComponent,
///    TransformComponent>
///
/// Now, in order to act on those selected entities we can implement one of the
/// five methods: Awake, Start, Update, LateUpdate, Destroy. A registered system
/// (see the Samples/Systems folder for an example) can now access the entities
/// like this:
///
///    for each (auto entity in entities)
///        auto& [renderer, transform] = entities.get<RenderComponent,
///        TransformComponent>(entity);
///
/// Use this pattern to update your entities (i.e. their components) as you
/// wish.
///
/// This pattern was chosen as it allows multithreading at a later point.
///
/// </summary>
/// <typeparam name="firstType">The component you want to access</typeparam>
/// <typeparam name="...Types">A list of components you need access
/// to</typeparam>
template <class firstType, class... Types>
class SystemBase : public UntypedSystemBase {
public:
    SystemBase() = default;
    SystemBase(const SystemBase& other) = default;

    // TODO all this methods (including the Render method of the rendering
    // system should take a custom wrapper around the basic view.. We don't want
    // to expose external dependencies.

    /// <summary>
    /// This method is called before the systems start method is called for all
    /// components already present in the scene.
    /// </summary>
    /// <param name="entities">A view on the entities that match the systems
    /// component selection.</param>
    virtual void Awake(
        entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...>
            entities){};

    /// <summary>
    /// This method is called on the systems start right before we enter the
    /// game loop for all components already present in the scene.
    /// </summary>
    /// <param name="entities">A view on the entities that match the systems
    /// component selection.</param>
    virtual void Start(
        entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...>
            entities){};

    /// <summary>
    /// This method is called in every game logic update for all components
    /// already present in the scene.
    /// </summary>
    /// <param name="entities">A view on the entities that match the systems
    /// component selection.</param>
    virtual void Update(
        entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...>
            entities,
        double dt){};

    /// <summary>
    /// This method is called in every game logic update right after the physics
    /// has been updated for all components already present in the scene.
    /// </summary>
    /// <param name="entities">A view on the entities that match the systems
    /// component selection.</param>
    virtual void LateUpdate(
        entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...>
            entities,
        double dt){};

    /// <summary>
    /// This method is called right before application shutdown. Use this to
    /// clean up your systems when they need component access.
    /// </summary>
    /// <param name="entities">A view on the entities that match the systems
    /// component selection.</param>
    virtual void Destroy(
        entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...>
            entities){};

protected:
    /// <summary>
    /// Returns a view for a given registry for this system.
    /// </summary>
    /// <param name="reg">The registry to pull entities from</param>
    /// <returns>A view of the entities present in the registry</returns>
    auto GetEntitiesFromRegistry(entt::registry& reg) {
        auto view = reg.view<firstType, Types...>();
        return view;
    }

    /// <summary>
    /// Returns a reference to the input system used on the current scene.
    /// </summary>
    /// <returns></returns>
    auto GetInput() { return this->GetCurrentScene()->GetInput(); }

private:
    friend class SceneHandler;
    void InternalAwake(entt::registry& reg) override {
        this->Awake(GetEntitiesFromRegistry(reg));
    }
    void InternalStart(entt::registry& reg) override {
        this->Start(GetEntitiesFromRegistry(reg));
    }
    void InternalUpdate(entt::registry& reg, double dt) override {
        this->Update(GetEntitiesFromRegistry(reg), dt);
    }
    void InternalLateUpdate(entt::registry& reg, double dt) override {
        this->LateUpdate(GetEntitiesFromRegistry(reg), dt);
    }
    void InternalDestroy(entt::registry& reg) override {
        this->Destroy(GetEntitiesFromRegistry(reg));
    }
};
}  // namespace ComponentSystem
}  // namespace DCore