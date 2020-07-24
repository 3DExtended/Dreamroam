#include "AScene.hh"
#include "SceneHandler.hh"

AScene::AScene()
{
	this->mDevice = SceneHandler::getInstance()->getDevice();
	// mGeometryStore = std::make_shared<GeometryStore>(mDevice);
	// mTextureStore = std::make_shared<TextureStore>(mDevice);
}

AScene::~AScene()
{
}

std::shared_ptr<GameObject> AScene::instantiate()
{
	return instantiate("");
}

std::shared_ptr<GameObject> AScene::instantiate(const std::string name)
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
