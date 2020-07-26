#include "AScene.hh"
#include "SceneHandler.hh"

using namespace DCore::ComponentSystem;
using namespace DCore::Textures;

AScene::AScene()
{
	this->mDevice = SceneHandler::getDevice();
}

AScene::~AScene()
{
}

std::shared_ptr<GameObject> AScene::instantiate()
{
	return instantiate("");
}

std::shared_ptr<GameObject> AScene::instantiate(const std::string& name)
{
	auto go = std::make_shared<GameObject>(name);
	gameObjects.push_back(go);
	return go;
}

void AScene::gameObjectAwake()
{
	for (auto go : gameObjects)
	{
		go->awake();
	}
}

void AScene::gameObjectStart()
{
	for (auto go : gameObjects)
	{
		go->start();
	}
}

void AScene::gameObjectUpdate(double dt)
{
	for (auto go : gameObjects)
	{
		go->update(dt);
	}
}

void AScene::gameObjectLateUpdate()
{
	for (auto go : gameObjects)
	{
		go->lateUpdate();
	}
}

void AScene::gameObjectDestroy()
{
	for (auto go : gameObjects)
	{
		go->destroy();
	}
}

const lava::SharedDescriptorSetLayout AScene::getTextureLayout()
{
	return mTextureStore->getTextureLayout();
}