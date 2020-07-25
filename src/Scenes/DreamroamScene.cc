#include "DreamroamScene.hh"
#include <Components/RenderComponent.hh>

using namespace DCore::ComponentSystem;
using namespace DCore::Components;
using namespace DCore::Meshes;
using namespace DCore::Textures;
using namespace DCore::Example;

DreamroamScene::DreamroamScene() : AScene()
{
	mGeometryStore = std::make_shared<GeometryStore>(mDevice);

	std::vector<std::pair<std::string, std::string>> imageTexturePathsAndNames;
	imageTexturePathsAndNames.push_back(std::pair<std::string, std::string>("assets/atlas.png", "atlas"));
	mTextureStore = std::make_shared<TextureStore>(mDevice, imageTexturePathsAndNames);
}

void DreamroamScene::start()
{
	createGameObjects();
}

std::shared_ptr<GameObject> cube;

void DreamroamScene::update(double dt) {
	cube->transform.rotation += glm::vec3(0, dt, 0);
}

inline void DreamroamScene::createGameObjects()
{
	{ //load world.obj
		mGeometryStore->registerGeometryFromFileSingle("assets/world.obj", "World");
		auto houseGO = this->instantiate("World");
		auto renderer = std::make_shared<RenderComponent>();
		renderer->active = true;
		renderer->hasTexture = true;
		renderer->textureObj = mTextureStore->getTextureWithName("atlas");
		renderer->isTransparent = false;
		renderer->geometryObj = mGeometryStore->getGeometryWithName("World");
		houseGO->addComponent(renderer);
	}

	{ // render cube
		cube = this->instantiate("Cube");
		auto renderer = std::make_shared<RenderComponent>();
		renderer->active = true;
		renderer->hasTexture = true;
		renderer->textureObj = mTextureStore->getTextureWithName("atlas");
		renderer->isTransparent = false;
		renderer->geometryObj = mGeometryStore->getGeometryWithName("cube");
		cube->addComponent(renderer);
		cube->transform.position += glm::vec3(15, 1, 0);
		cube->transform.scale += glm::vec3(2, 2, 2);
	}
}