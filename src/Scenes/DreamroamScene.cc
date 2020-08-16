#include "DreamroamScene.hh"

#include <imgui-node-editor/imgui_node_editor.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui_internal.h>

#include <ComponentBased/BaseComponents.hh>
#include <ComponentBased/Entity.hh>
#include <ComponentBased/Systems/SystemBase.hh>
#include <RenderingSystem/RenderComponent.hh>
#include <Utils/Debug/Profiling.hh>
#include <imgui/imgui_widgets.cpp>

using namespace DCore::ComponentSystem;
using namespace DCore::Meshes;
using namespace DCore::Textures;
using namespace DCore::Example;

namespace ed = ax::NodeEditor;

// Struct to hold basic information about connection between
// pins. Note that connection (aka. link) has its own ID.
// This is useful later with dealing with selections, deletion
// or other operations.
struct LinkInfo {
    ed::LinkId Id;
    ed::PinId InputId;
    ed::PinId OutputId;
};

static ed::EditorContext* g_Context = nullptr;
static bool g_FirstFrame = true;  // Flag set for first frame only, some action
                                  // need to be executed once.
static ImVector<LinkInfo>
    g_Links;  // List of live links. It is dynamic unless you want to create
              // read-only view over nodes.
static int g_NextLinkId =
    100;  // Counter to help generate link ids. In real application this will
          // probably based on pointer to user data structure.

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

    ed::Config config;
    config.SettingsFile = "Simple.json";
    g_Context = ed::CreateEditor(&config);
}

void DreamroamScene::start() { createGameObjects(); }

void DreamroamScene::update(double dt) {}

void DreamroamScene::ImGuiDebugWindow() {
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

void DreamroamScene::imGuiRender() {
    ImGuiDebugWindow();

    auto& io = ImGui::GetIO();

    ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate,
                io.Framerate ? 1000.0f / io.Framerate : 0.0f);

    ImGui::Separator();

    ed::SetCurrentEditor(g_Context);

    // Start interaction with editor.
    ed::Begin("My Editor", ImVec2(0.0, 0.0f));

    int uniqueId = 1;

    //
    // 1) Commit known data to editor
    //

    // Submit Node A
    ed::NodeId nodeA_Id = uniqueId++;
    ed::PinId nodeA_InputPinId = uniqueId++;
    ed::PinId nodeA_OutputPinId = uniqueId++;
    ed::PinId nodeA_OutputPin2Id = uniqueId++;

    if (g_FirstFrame) ed::SetNodePosition(nodeA_Id, ImVec2(10, 10));
    ed::BeginNode(nodeA_Id);
    ImGui::Text("Node A");
    ed::BeginPin(nodeA_InputPinId, ed::PinKind::Input);
    ImGui::Text("-> In");
    ed::EndPin();
    ImGui::SameLine();
    ed::BeginPin(nodeA_OutputPinId, ed::PinKind::Output);
    ImGui::Text("Out ->");
    ed::EndPin();
    ed::EndNode();

    // Submit Node B
    ed::NodeId nodeB_Id = uniqueId++;
    ed::PinId nodeB_InputPinId1 = uniqueId++;
    ed::PinId nodeB_InputPinId2 = uniqueId++;
    ed::PinId nodeB_OutputPinId = uniqueId++;

    if (g_FirstFrame) ed::SetNodePosition(nodeB_Id, ImVec2(210, 60));
    ed::BeginNode(nodeB_Id);
    ImGui::Text("Node B");
    ImGui::BeginGroup();
    ed::BeginPin(nodeB_InputPinId1, ed::PinKind::Input);
    ImGui::Text("-> In1");
    ed::EndPin();
    ed::BeginPin(nodeB_InputPinId2, ed::PinKind::Input);
    ImGui::Text("-> In2");
    ed::EndPin();
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::BeginGroup();
    ed::BeginPin(nodeB_OutputPinId, ed::PinKind::Output);
    ImGui::Text("Out ->");
    ed::EndPin();
    ImGui::EndGroup();
    ed::EndNode();

    // Submit Links
    for (auto& linkInfo : g_Links)
        ed::Link(linkInfo.Id, linkInfo.InputId, linkInfo.OutputId);

    //
    // 2) Handle interactions
    //

    // Handle creation action, returns true if editor want to create new object
    // (node or link)
    if (ed::BeginCreate()) {
        ed::PinId inputPinId, outputPinId;
        if (ed::QueryNewLink(&inputPinId, &outputPinId)) {
            // QueryNewLink returns true if editor want to create new link
            // between pins.
            //
            // Link can be created only for two valid pins, it is up to you to
            // validate if connection make sense. Editor is happy to make any.
            //
            // Link always goes from input to output. User may choose to drag
            // link from output pin or input pin. This determine which pin ids
            // are valid and which are not:
            //   * input valid, output invalid - user started to drag new ling
            //   from input pin
            //   * input invalid, output valid - user started to drag new ling
            //   from output pin
            //   * input valid, output valid   - user dragged link over other
            //   pin, can be validated

            if (inputPinId && outputPinId)  // both are valid, let's accept link
            {
                // ed::AcceptNewItem() return true when user release mouse
                // button.
                if (ed::AcceptNewItem()) {
                    // Since we accepted new link, lets add one to our list of
                    // links.
                    g_Links.push_back(
                        {ed::LinkId(g_NextLinkId++), inputPinId, outputPinId});

                    // Draw new link.
                    ed::Link(g_Links.back().Id, g_Links.back().InputId,
                             g_Links.back().OutputId);
                }

                // You may choose to reject connection between these nodes
                // by calling ed::RejectNewItem(). This will allow editor to
                // give visual feedback by changing link thickness and color.
            }
        }
    }
    ed::EndCreate();  // Wraps up object creation action handling.

    // Handle deletion action
    if (ed::BeginDelete()) {
        // There may be many links marked for deletion, let's loop over them.
        ed::LinkId deletedLinkId;
        while (ed::QueryDeletedLink(&deletedLinkId)) {
            // If you agree that link can be deleted, accept deletion.
            if (ed::AcceptDeletedItem()) {
                // Then remove link from your data.
                for (auto& link : g_Links) {
                    if (link.Id == deletedLinkId) {
                        g_Links.erase(&link);
                        break;
                    }
                }
            }

            // You may reject link deletion by calling:
            // ed::RejectDeletedItem();
        }
    }
    ed::EndDelete();  // Wrap up deletion action

    // End of interaction with editor.
    ed::End();

    if (g_FirstFrame) ed::NavigateToContent(0.0f);

    ed::SetCurrentEditor(nullptr);

    g_FirstFrame = false;
}

inline void DreamroamScene::createGameObjects() {
    DR_PROFILE_FUNCTION();

    mGeometryStore->registerGeometryFromFileSingle("assets/world.obj", "World");
    for (auto x = 0; x < 5; x++) {
        for (auto y = 0; y < 5; y++) {
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