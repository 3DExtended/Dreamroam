#include "DreamroamScene.hh"
#include <RenderingSystem/RenderComponent.hh>
#include <ComponentBased/BaseComponents.hh>
#include <ComponentBased/Entity.hh>

using namespace DCore::ComponentSystem;
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

Entity cube;

void DreamroamScene::update(double dt) {
	cube.GetComponent<TransformComponent>().rotation += glm::vec3(0, dt, 0);
}

inline void DreamroamScene::createGameObjects()
{
	{ //load world.obj
		mGeometryStore->registerGeometryFromFileSingle("assets/world.obj", "World");
		auto houseGO = this->CreateEntity("World");
		auto& renderer = houseGO.AddComponent<RenderComponent>();
		renderer.active = true;
		renderer.hasTexture = true;
		renderer.textureObj = mTextureStore->getTextureWithName("atlas");
		renderer.isTransparent = false;
		renderer.geometryObj = mGeometryStore->getGeometryWithName("World");
	}

	{ // render cube
		cube = this->CreateEntity("Cube");
		auto& renderer = cube.AddComponent<RenderComponent>();

		renderer.active = true;
		renderer.hasTexture = true;
		renderer.textureObj = mTextureStore->getTextureWithName("atlas");
		renderer.isTransparent = false;
		renderer.geometryObj = mGeometryStore->getGeometryWithName("cube");

		cube.GetComponent<TransformComponent>().position += glm::vec3(15, 1, 0);
		cube.GetComponent<TransformComponent>().scale += glm::vec3(2, 2, 2);
	}
}