#include "Entity.hh"

#include <glm/glm.hpp>

#include "AScene.hh"
#include "SceneHandler.hh"

namespace DCore {
namespace ComponentSystem {
Entity::Entity(entt::entity handle, AScene* scene)
    : m_EntityHandle(handle), m_Scene(scene) {}

entt::registry& Entity::GetSceneRegistry() { return m_Scene->m_Registry; }
}  // namespace ComponentSystem
}  // namespace DCore