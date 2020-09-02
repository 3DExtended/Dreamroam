#include "RotateCubeScene.hh"

#include <ComponentBased/BaseComponents.hh>
#include <ComponentBased/Entity.hh>
#include <ComponentBased/Systems/Base/SystemBase.hh>
#include <RenderingSystem/RenderComponent.hh>
#include <Utils/Debug/Profiling.hh>
#include <imgui/imgui_widgets.cpp>

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

RotateCubeScene::RotateCubeScene() : AScene() {
    DR_PROFILE_FUNCTION();

    mGeometryStore = std::make_shared<GeometryStore>(mDevice);

    std::vector<std::pair<std::string, std::string>> imageTexturePathsAndNames;
    imageTexturePathsAndNames.push_back(
        std::pair<std::string, std::string>("assets/atlas.png", "atlas"));
    mTextureStore =
        std::make_shared<TextureStore>(mDevice, imageTexturePathsAndNames);

    registerSystems();
}

void RotateCubeScene::start() { createGameObjects(); }

void RotateCubeScene::update(double dt) {}

void RotateCubeScene::ImGuiDebugWindow() {
    const float DISTANCE = 10.0f;
    static int corner = 3;
    ImGuiIO& io = ImGui::GetIO();
    if (corner != -1) {
        ImVec2 window_pos =
            ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE,
                   (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
        ImVec2 window_pos_pivot =
            ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    }
    ImGui::SetNextWindowBgAlpha(0.35f);  // Transparent background
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav;
    if (corner != -1) window_flags |= ImGuiWindowFlags_NoMove;
    if (ImGui::Begin("Debug Details", nullptr, window_flags)) {
        ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate,
                    io.Framerate);

        if (ImGui::BeginPopupContextWindow()) {
            if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
            if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
            if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
            if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
            if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}

void RotateCubeScene::imGuiRender() { ImGuiDebugWindow(); }

inline void RotateCubeScene::createGameObjects() {
    DR_PROFILE_FUNCTION();

    {  // create a cube entity
        auto cube = this->CreateEntity("Cube");
        auto& renderer = cube.AddComponent<RenderComponent>();

        renderer.active = true;
        renderer.hasTexture = true;
        renderer.textureObj = mTextureStore->getTextureWithName("atlas");
        renderer.isTransparent = false;
        renderer.geometryObj = mGeometryStore->getGeometryWithName("cube");

        cube.GetComponent<TransformComponent>().position += glm::vec3(15, 1, 0);
        cube.GetComponent<TransformComponent>().scale += glm::vec3(2, 2, 2);
    }  //*/
}

void RotateCubeScene::registerSystems() {
    DR_PROFILE_FUNCTION();

    this->RegisterEntitySystem(std::make_shared<RotateCubesSystem>());
}