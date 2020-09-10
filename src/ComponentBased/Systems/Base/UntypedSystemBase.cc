#include "UntypedSystemBase.hh"

#include <ComponentBased/AScene.hh>

DCore::ComponentSystem::Entity
DCore::ComponentSystem::UntypedSystemBase::GetEntityFromId(
    entt::entity entityId) {
    return Entity(entityId, this->curScene);
}

DCore::ComponentSystem::AScene*
DCore::ComponentSystem::UntypedSystemBase::GetCurrentScene() const {
    return this->curScene;
}