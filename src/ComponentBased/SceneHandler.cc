#include "SceneHandler.hh"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

#include <RenderingSystem/PushConstants.hh>
#include <RenderingSystem/RenderComponent.hh>
#include <RenderingSystem/RenderingSystem.hh>
#include <Utils/Base.hh>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <lava-extras/camera/GenericCamera.hh>
#include <lava/common/log.hh>
#include <lava/createinfos/Buffers.hh>
#include <lava/createinfos/DescriptorSetLayoutCreateInfo.hh>
#include <lava/createinfos/Images.hh>
#include <lava/createinfos/Sampler.hh>
#include <lava/features/GlfwOutput.hh>
#include <lava/gpuselection/NthOfTypeStrategy.hh>
#include <lava/objects/Buffer.hh>
#include <lava/objects/DescriptorSetLayout.hh>
#include <lava/objects/Framebuffer.hh>
#include <lava/objects/Image.hh>
#include <lava/objects/ImageView.hh>
#include <lava/objects/Instance.hh>
#include <limits>
#include <thread>

#include "ComponentBased/BaseComponents.hh"
#include "GlobalSettings.hh"
#include "VulkanHelpers/GPUSelectorStrategy.hh"

std::shared_ptr<SceneHandler> SceneHandler::instance = nullptr;

std::shared_ptr<SceneHandler> SceneHandler::getInstance() {
    DR_PROFILE_FUNCTION();
    if (instance == nullptr) instance = std::make_shared<SceneHandler>();
    return instance;
}

SceneHandler::~SceneHandler() {}

void SceneHandler::_switchScene(uint16_t index) {
    DR_PROFILE_FUNCTION();
    if (curScene == nullptr && scenes.size() == 0) {
        std::cerr << "There are no scenes to switch to.." << std::endl;
    } else if (index >= scenes.size()) {
        std::cerr << "The scene you want to switch to is not registered."
                  << std::endl;
    } else {
        if (curScene != nullptr) {
            for (auto system : curScene->m_Systems) {
                system->InternalDestroy(curScene->m_Registry);
            }
            curScene->destroy();
        }
        curScene = scenes.at(index);
        curScene->m_InputSystem = m_InputSystem;

        start();
    }
}

uint16_t SceneHandler::_addScene(std::shared_ptr<AScene> newScene) {
    scenes.push_back(newScene);
    return scenes.size() - 1;
}

lava::SharedDevice SceneHandler::_getDevice() const { return mDevice; }

void SceneHandler::run() {
    DR_PROFILE_FUNCTION();
    DR_ASSERT(scenes.size() > 0);

    mWindowWidth = GlobalSettings::windowWidth;
    mWindowHeight = GlobalSettings::windowHeight;

    // the swapchain is setup in the rendering system
    mWindow = mGlfwOutput->openWindow(GlobalSettings::windowWidth,
                                      GlobalSettings::windowHeight, true,
                                      "DreamRoam");

    m_InputSystem = std::make_shared<InputSystem>(mWindow);
    switchScene(0);

    if (this->rendererSystem == nullptr) {
        this->rendererSystem = new RenderingSystem(
            getDevice(),
            getCurrentScene()->GetCurrentSceneTextureStoreTextureLayout(),
            mGlfwOutput, mWindow);
        this->rendererSystem->InternalSetCurrentScene(getCurrentScene().get());
    }

    this->setupGlfwCallbacks();

    double lastCpuTime = glfwGetTime();

    // FPS measuring
    uint16_t frames = 0;
    double FPStime = glfwGetTime();

    while (!glfwWindowShouldClose(mWindow->window())) {
        DR_PROFILE_SCOPE("Main Game Loop");
        // timing
        auto cpustart = glfwGetTime();
        auto dt = cpustart - lastCpuTime;

        // TODO this 2 should not be hard coded but instead use a counter for
        // how many command buffers are used per frame
        mDevice->graphicsQueue().catchUp(2);

        // update
        updateInput();
        update(dt);
        lastCpuTime += dt;

        // render
        render();

        // timing
        auto now = glfwGetTime();
        ++frames;
        if (now - FPStime >= 1) {
            lava::log() << "FPS: " << frames;
            frames = 0;
            FPStime = now;
        }

        // TODO(esser): remove this when we have a scene that takes longer to
        // render than the default cube scene...
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

SceneHandler::SceneHandler() {
    DR_PROFILE_FUNCTION();
    // Create device handle for vulkan
    std::vector<lava::features::SharedFeature> lavaFeatures;

    // GLFW Output
    mGlfwOutput = lava::features::GlfwOutput::create();
    lavaFeatures.push_back(mGlfwOutput);

    if (GlobalSettings::useValidation) {
        mValidation = lava::features::Validation::create();
        lavaFeatures.push_back(mValidation);
    }

    // === Create instance and device: ===
    // TODO make this parameterized
    lava::SharedInstance lavaInstance = lava::Instance::create(lavaFeatures);
    mDevice = lavaInstance->createDevice(
        {lava::QueueRequest::graphics("graphics")},
        DCore::ComponentSystem::GPUSelectorStrategy());
}

void SceneHandler::setupGlfwCallbacks() {
    DR_PROFILE_FUNCTION();
    static std::unordered_map<GLFWwindow*, SceneHandler*> sWindowApps;

    auto window = mWindow->window();
    auto insertion = sWindowApps.insert({window, this}).second;
    DR_ASSERT(insertion && "You can only have one app per GLFWwindow.");

    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode,
                                  int action, int mods) {
        sWindowApps.at(win)->onKey(key, scancode, action, mods);

        ImGuiIO& io = ImGui::GetIO();
        if (action == GLFW_PRESS) io.KeysDown[key] = true;
        if (action == GLFW_RELEASE) io.KeysDown[key] = false;

        // Modifiers are not reliable across systems
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] ||
                     io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] ||
                      io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt =
            io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
#ifdef _WIN32
        io.KeySuper = false;
#else
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
#endif
    });

    glfwSetCharModsCallback(
        window, [](GLFWwindow* win, unsigned int codepoint, int mods) {
            sWindowApps.at(win)->onChar(codepoint, mods);
        });

    glfwSetCharCallback(window, [](GLFWwindow* win, unsigned int c) {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter(c);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* win, double sx, double sy) {
        sWindowApps.at(win)->onMouseScroll(sx, sy);
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += (float)sx;
        io.MouseWheel += (float)sy;
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
        auto app = sWindowApps.at(win);
        app->mWindowWidth = w;
        app->mWindowHeight = h;
        app->onResize(w, h);
    });

    glfwSetWindowFocusCallback(window, [](GLFWwindow* win, int focused) {
        auto app = sWindowApps.at(win);
        if (focused)
            app->onFocusGain();
        else
            app->onFocusLost();
    });

    glfwSetDropCallback(window,
                        [](GLFWwindow* win, int count, const char** paths) {
                            std::vector<std::string> files;
                            for (auto i = 0; i < count; ++i)
                                files.push_back(paths[i]);
                            sWindowApps.at(win)->onFileDrop(files);
                        });
}

void SceneHandler::start() {
    DR_PROFILE_FUNCTION();
    curScene->start();
    for (auto system : curScene->m_Systems) {
        system->InternalAwake(curScene->m_Registry);
    }

    for (auto system : curScene->m_Systems) {
        system->InternalStart(curScene->m_Registry);
    }
}

void SceneHandler::update(double dt) {
    DR_PROFILE_FUNCTION();
    curScene->update(dt);
    for (auto system : curScene->m_Systems) {
        system->InternalUpdate(curScene->m_Registry, dt);
    }

    for (auto system : curScene->m_Systems) {
        system->InternalLateUpdate(curScene->m_Registry, dt);
    }
}

void SceneHandler::render() {
    DR_PROFILE_FUNCTION();
    this->rendererSystem->InternalRender(this->curScene->m_Registry);
}

void SceneHandler::onKey(int key, int scancode, int action, int mods) {
    DR_PROFILE_FUNCTION();
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        mCatchCursor = !mCatchCursor;
        if (!mCatchCursor) {
            glfwSetInputMode(mWindow->window(), GLFW_CURSOR,
                             GLFW_CURSOR_NORMAL);
        }
    }
}

void SceneHandler::onMouseButton(double x, double y, int button, int action,
                                 int mods, int clickCount) {}

void SceneHandler::onMouseScroll(double sx, double sy) {
    // Note: it seems that it is not possible to get scroll information based on
    // getters
    this->m_InputSystem->SetScrollWheel(glm::vec2(sx, sy));
}

void SceneHandler::onFocusGain() {
    // todo maybe reduce and fix framerate here..
}

void SceneHandler::onFocusLost() {
    // todo maybe reduce and fix framerate here..
}

void SceneHandler::onFileDrop(const std::vector<std::string>& files) {}

void SceneHandler::onChar(unsigned int codepoint, int mods) {}

void SceneHandler::onResize(int w, int h) {
    if (rendererSystem != nullptr) {
        rendererSystem->Resize(w, h);
    }
}

void SceneHandler::updateInput() {
    DR_PROFILE_FUNCTION();
    if (mCatchCursor == true) {
        glfwSetInputMode(mWindow->window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    // Poll for and process events
    glfwPollEvents();
}