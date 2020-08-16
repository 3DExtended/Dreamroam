#pragma once
#include <ComponentBased/AScene.hh>
using namespace DCore::ComponentSystem;

namespace DCore {
namespace Example {
class DreamroamScene : public AScene {
public:
    DreamroamScene();
    void start() override;
    void update(double dt) override;
    void imGuiRender() override;

private:
    void createGameObjects();
    void ImGuiDebugWindow();

    void registerSystems();
};
}  // namespace Example
}  // namespace DCore