#pragma once
#include <ComponentBased/AScene.hh>
#include <ComponentBased/Systems/SystemBase.hh>
#include <RenderingSystem/Pipeline/AdvancedRenderingPipeline.hh>
#include <RenderingSystem/Pipeline/GraphicsPipelineFactory.hh>
#include <RenderingSystem/RenderingSystemBase.hh>
#include <iostream>
#include <lava-extras/glfw/GlfwApp.hh>
#include <lava/features/Validation.hh>
#include <lava/objects/Device.hh>
#include <vector>

namespace DCore {
namespace ComponentSystem {
/// <summary>
/// A SceneHandler is the manager of the game engine.
/// It implements the singleton pattern and provides getters for the current
/// scene, the switch scene method and more.
/// </summary>
class SceneHandler {
public:
    /// <summary>
    /// Singleton pattern getter. Use this to get the scene handler from within
    /// your components.
    /// </summary>
    /// <returns>The current scene handler</returns>
    static std::shared_ptr<SceneHandler> getInstance();

    /// <summary>
    /// Add scene to the game. This has to be called before you can switch to
    /// this scene.
    /// </summary>
    /// <param name="newScene">The scene you want to add.</param>
    /// <returns>The index of the newly added scene</returns>
    static uint16_t addScene(std::shared_ptr<AScene> newScene) {
        return getInstance()->_addScene(newScene);
    }

    /// <summary>
    /// Getter for the currently loaded scene.
    /// </summary>
    /// <returns>A pointer to the currently loaded scene</returns>
    static std::shared_ptr<AScene> getCurrentScene() {
        return getInstance()->_getCurrentScene();
    }

    /// <summary>
    /// Getter for the currently loaded scene.
    /// </summary>
    /// <returns>A pointer to the currently loaded scene</returns>
    static lava::SharedDevice getDevice() {
        return getInstance()->_getDevice();
    }

    /// <summary>
    /// Switches the loaded and rendered scene.
    /// The index used here is returned in addScene(...).
    /// </summary>
    /// <param name="sceneIndex">The index of the scene to switch to.</param>
    static void switchScene(uint16_t sceneIndex) {
        getInstance()->_switchScene(sceneIndex);
    }

    /// <summary>
    /// If you want to supply a custom rendering system for rendering your
    /// scene, call this method after you have registered all scenes in your
    /// main.cc. You can take a look of the implementation of the default
    /// rendering system at RenderingSystem.cc
    /// </summary>
    /// <param name="renderer">The new renderer to use for the scene.</param>
    void setupRenderer(RenderingSystemBase* renderer) {
        this->rendererSystem = renderer;
    };

    /// <summary>
    /// Creates a new instance of the scene handler. Should only be called ONCE
    /// by the main function.
    /// </summary>
    /// <remarks>This should not be used to create a new instance. Instead,
    /// please use the GetInstance method.</remarks> <remarks>This needs to be
    /// public in order to create a new instance using std::make_shared in the
    /// GetInstance method.</remarks> <returns>A new SceneHandler</returns>
    SceneHandler();

    ~SceneHandler();

    void run();
    void updateCamera(double elapsedSeconds);

    double mMouseX = 0;
    double mMouseY = 0;
    int mWindowWidth = 0;
    int mWindowHeight = 0;

    bool mCatchCursor = true;
    float mCameraMoveSpeed = 10.0f;
    float mCameraMoveSpeedFactor = 5.0f;
    float mCameraTurnSpeed = 2.0f;
    float mCameraScrollSpeed = 5.0f;

    double mMouseLastX = -1.0;
    double mMouseLastY = -1.0;

    double mDoubleClickTime = 0.35f;
    int mClickCount = 0;
    int mClickButton = -1;
    glm::vec2 mClickPos;
    lava::Stopwatch mClickTimer;

private:
    static std::shared_ptr<SceneHandler> instance;
    std::vector<std::shared_ptr<AScene>> scenes;
    std::shared_ptr<AScene> curScene = nullptr;
    std::shared_ptr<lava::features::GlfwOutput> mGlfwOutput;
    std::shared_ptr<lava::features::Validation> mValidation;
    std::shared_ptr<lava::features::GlfwWindow> mWindow;
    lava::SharedDevice mDevice;
    RenderingSystemBase* rendererSystem = nullptr;

private:
    void setupGlfwCallbacks();

    void _switchScene(uint16_t index);

    lava::SharedDevice _getDevice() const;

    uint16_t _addScene(std::shared_ptr<AScene> newScene);

    std::shared_ptr<AScene> _getCurrentScene() { return curScene; }

    void start();
    void update(double dt);
    void render();
    bool onKey(int key, int scancode, int action, int mods);
    bool onMousePosition(double x, double y);
    bool onMouseButton(double x, double y, int button, int action, int mods,
                       int clickCount);
    bool onMouseScroll(double sx, double sy);
    bool onMouseEnter();
    bool onMouseExit();
    bool onFocusGain();
    bool onFocusLost();
    bool onFileDrop(const std::vector<std::string>& files);
    bool onChar(unsigned int codepoint, int mods);
    void internalOnMouseButton(double x, double y, int button, int action,
                               int mods);
    void onResize(int w, int h);
    void updateInput();
};
}  // namespace ComponentSystem
}  // namespace DCore