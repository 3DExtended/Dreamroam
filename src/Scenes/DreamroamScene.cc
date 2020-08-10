#include "DreamroamScene.hh"

#include <ComponentBased/BaseComponents.hh>
#include <ComponentBased/Entity.hh>
#include <ComponentBased/Systems/SystemBase.hh>
#include <RenderingSystem/RenderComponent.hh>

using namespace DCore::ComponentSystem;
using namespace DCore::Meshes;
using namespace DCore::Textures;
using namespace DCore::Example;

class RotateCubesSystem : public SystemBase<TransformComponent, TagComponent> {
public:
    RotateCubesSystem() = default;
    ~RotateCubesSystem() = default;

    void Update(entt::basic_view<entt::entity, entt::exclude_t<>,
                                 TransformComponent, TagComponent>
                    entities,
                double dt) override {
        for (auto entity : entities) {
            auto [transform, tag] =
                entities.get<TransformComponent, TagComponent>(entity);
            if (tag.Tag == "Cube") {
                transform.rotation += glm::vec3(0, dt, 0);
            }
        }
    }
};

DreamroamScene::DreamroamScene() : AScene() {
    mGeometryStore = std::make_shared<GeometryStore>(mDevice);

    std::vector<std::pair<std::string, std::string>> imageTexturePathsAndNames;
    imageTexturePathsAndNames.push_back(
        std::pair<std::string, std::string>("assets/atlas.png", "atlas"));
    mTextureStore =
        std::make_shared<TextureStore>(mDevice, imageTexturePathsAndNames);

    registerSystems();
}

void DreamroamScene::start() { createGameObjects(); }

void DreamroamScene::update(double dt) {}

inline void DreamroamScene::createGameObjects() {
    {  // load world.obj
        mGeometryStore->registerGeometryFromFileSingle("assets/world.obj",
                                                       "World");
        auto houseGO = this->CreateEntity("World");
        auto& renderer = houseGO.AddComponent<RenderComponent>();
        renderer.active = true;
        renderer.hasTexture = true;
        renderer.textureObj = mTextureStore->getTextureWithName("atlas");
        renderer.isTransparent = false;
        renderer.geometryObj = mGeometryStore->getGeometryWithName("World");
    }

    {  // render cube
        auto cube = this->CreateEntity("Cube");
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

void DreamroamScene::registerSystems() {
    this->RegisterEntitySystem(std::make_shared<RotateCubesSystem>());
}