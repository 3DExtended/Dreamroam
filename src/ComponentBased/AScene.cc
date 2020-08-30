#include "AScene.hh"

#include "../ComponentBased/BaseComponents.hh"
#include "Entity.hh"
#include "SceneHandler.hh"

using namespace DCore::ComponentSystem;
using namespace DCore::Textures;

AScene::AScene() { this->mDevice = SceneHandler::getDevice(); }

AScene::~AScene() {}

DCore::ComponentSystem::Entity AScene::CreateEntity(const std::string& name) {
    DCore::ComponentSystem::Entity entity = {m_Registry.create(), this};
    entity.AddComponent<TransformComponent>();
    auto& tag = entity.AddComponent<TagComponent>();
    tag.Tag = name.empty() ? "Entity" : name;
    return entity;
}

const lava::SharedDescriptorSetLayout
AScene::GetCurrentSceneTextureStoreTextureLayout() {
    return mTextureStore->getTextureLayout();
}