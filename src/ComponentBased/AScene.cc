#include "AScene.hh"
#include "SceneHandler.hh"
#include "../ComponentBased/BaseComponents.hh"
#include "./Entity.hh"

using namespace DCore::ComponentSystem;
using namespace DCore::Textures;

AScene::AScene()
{
	this->mDevice = SceneHandler::getDevice();
}

AScene::~AScene()
{
}

Entity AScene::CreateEntity(const std::string& name)
{
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
	tag.Tag = name.empty() ? "Entity" : name;
	return entity;
}

const lava::SharedDescriptorSetLayout AScene::GetCurrentSceneTextureStoreTextureLayout()
{
	return mTextureStore->getTextureLayout();
}