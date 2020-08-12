#include "DreamroamScene.hh"

#include <ComponentBased/BaseComponents.hh>
#include <ComponentBased/Entity.hh>
#include <ComponentBased/Systems/SystemBase.hh>
#include <RenderingSystem/RenderComponent.hh>
#include <Utils/Debug/Profiling.hh>

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
        DR_PROFILE_FUNCTION();

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
    DR_PROFILE_FUNCTION();

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
    DR_PROFILE_FUNCTION();

    mGeometryStore->registerGeometryFromFileSingle("assets/world.obj", "World");
    for (auto x = 0; x < 20; x++) {
        for (auto y = 0; y < 20; y++) {
            {  // load world.obj
                auto houseGO = this->CreateEntity("World");
                auto& renderer = houseGO.AddComponent<RenderComponent>();
                renderer.active = true;
                renderer.hasTexture = true;
                renderer.textureObj =
                    mTextureStore->getTextureWithName("atlas");
                renderer.isTransparent = false;
                renderer.geometryObj =
                    mGeometryStore->getGeometryWithName("World");
                houseGO.GetComponent<TransformComponent>().position +=
                    glm::vec3(x * 20, 0, y * 15);
            }

            {  // render cube
                auto cube = this->CreateEntity("Cube");
                auto& renderer = cube.AddComponent<RenderComponent>();

                renderer.active = true;
                renderer.hasTexture = true;
                renderer.textureObj =
                    mTextureStore->getTextureWithName("atlas");
                renderer.isTransparent = false;
                renderer.geometryObj =
                    mGeometryStore->getGeometryWithName("cube");

                cube.GetComponent<TransformComponent>().position +=
                    glm::vec3(15, 1, 0);
                cube.GetComponent<TransformComponent>().scale +=
                    glm::vec3(2, 2, 2);
                cube.GetComponent<TransformComponent>().position +=
                    glm::vec3(x * 20, 0, y * 15);
            }
        }
    }
}

void DreamroamScene::registerSystems() {
    DR_PROFILE_FUNCTION();

    this->RegisterEntitySystem(std::make_shared<RotateCubesSystem>());
}