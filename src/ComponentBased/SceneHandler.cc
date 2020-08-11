#include "SceneHandler.hh"

#include <GLFW/glfw3.h>

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

std::shared_ptr<SceneHandler> SceneHandler::instance = nullptr;

std::shared_ptr<SceneHandler> SceneHandler::getInstance() {
    if (instance == nullptr) instance = std::make_shared<SceneHandler>();
    return instance;
}

SceneHandler::~SceneHandler() {}

void SceneHandler::_switchScene(uint16_t index) {
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
        start();
    }
}

uint16_t SceneHandler::_addScene(std::shared_ptr<AScene> newScene) {
    scenes.push_back(newScene);
    return scenes.size() - 1;
}

lava::SharedDevice SceneHandler::_getDevice() const { return mDevice; }

void SceneHandler::run() {
    DR_ASSERT(scenes.size() > 0);

    switchScene(0);
    mWindowWidth = GlobalSettings::windowWidth;
    mWindowHeight = GlobalSettings::windowHeight;

    // the swapchain is setup in the rendering system
    mWindow = mGlfwOutput->openWindow(GlobalSettings::windowWidth,
                                      GlobalSettings::windowHeight, true,
                                      "DreamRoam");

    if (this->rendererSystem == nullptr) {
        this->rendererSystem = new RenderingSystem(
            getDevice(),
            getCurrentScene()->GetCurrentSceneTextureStoreTextureLayout(),
            mGlfwOutput, mWindow);
    }

    this->setupGlfwCallbacks();

    double lastCpuTime = glfwGetTime();

    // FPS measuring
    uint16_t frames = 0;
    double FPStime = glfwGetTime();

    while (!glfwWindowShouldClose(mWindow->window())) {
        // timing
        auto cpustart = glfwGetTime();
        auto dt = cpustart - lastCpuTime;

        // update
        updateInput();
        update(dt);
        this->updateCamera(dt);
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void SceneHandler::updateCamera(double elapsedSeconds) {
    auto window = mWindow->window();
    if (rendererSystem->getCamera()) {
        auto speed = mCameraMoveSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            speed *= mCameraMoveSpeedFactor;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            rendererSystem->getCamera()->moveForward(elapsedSeconds * speed);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            rendererSystem->getCamera()->moveBack(elapsedSeconds * speed);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            rendererSystem->getCamera()->moveLeft(elapsedSeconds * speed);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            rendererSystem->getCamera()->moveRight(elapsedSeconds * speed);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            rendererSystem->getCamera()->moveDown(elapsedSeconds * speed);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            rendererSystem->getCamera()->moveUp(elapsedSeconds * speed);
    }
}

SceneHandler::SceneHandler() {
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
        lava::NthOfTypeStrategy(vk::PhysicalDeviceType::eDiscreteGpu));
}

void SceneHandler::setupGlfwCallbacks() {
    static std::unordered_map<GLFWwindow*, SceneHandler*> sWindowApps;

    auto window = mWindow->window();
    auto insertion = sWindowApps.insert({window, this}).second;
    DR_ASSERT(insertion && "You can only have one app per GLFWwindow.");

    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode,
                                  int action, int mods) {
        sWindowApps.at(win)->onKey(key, scancode, action, mods);
    });

    glfwSetCharModsCallback(
        window, [](GLFWwindow* win, unsigned int codepoint, int mods) {
            sWindowApps.at(win)->onChar(codepoint, mods);
        });

    glfwSetMouseButtonCallback(
        window, [](GLFWwindow* win, int button, int action, int mods) {
            auto app = sWindowApps.at(win);
            app->internalOnMouseButton(app->mMouseX, app->mMouseY, button,
                                       action, mods);
        });

    glfwSetCursorEnterCallback(window, [](GLFWwindow* win, int entered) {
        try {
            auto app = sWindowApps.at(win);
            if (entered)
                app->onMouseEnter();
            else
                app->onMouseExit();
        } catch (std::out_of_range) {
        }
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
        auto app = sWindowApps.at(win);
        app->mMouseX = x;
        app->mMouseY = y;
        app->onMousePosition(x, y);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* win, double sx, double sy) {
        sWindowApps.at(win)->onMouseScroll(sx, sy);
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int w, int h) {
        auto app = sWindowApps.at(win);
        app->mWindowWidth = w;
        app->mWindowHeight = h;
        app->onResize(w, h);
        // TwWindowSize(w, h);
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
    curScene->start();
    for (auto system : curScene->m_Systems) {
        system->InternalAwake(curScene->m_Registry);
    }

    for (auto system : curScene->m_Systems) {
        system->InternalStart(curScene->m_Registry);
    }
}

void SceneHandler::update(double dt) {
    curScene->update(dt);
    for (auto system : curScene->m_Systems) {
        system->InternalUpdate(curScene->m_Registry, dt);
    }

    for (auto system : curScene->m_Systems) {
        system->InternalLateUpdate(curScene->m_Registry, dt);
    }
}

void SceneHandler::render() {
    // TODO find all entities with transform and renderComponent and call
    // the render methode of the active renderingSystem

    // classify gameObjects based on their renderers
    /*std::vector<std::tuple<RenderComponent&, TransformComponent&>>
    objectsToRender2 = std::vector<std::tuple<RenderComponent&,
    TransformComponent&>>();

    auto view = curScene->m_Registry.view<RenderComponent,
    TransformComponent>();
    // using an input iterator
    for (auto entity : view) {
        auto& tuple = view.get<RenderComponent, TransformComponent>(entity);
        auto [render, transform] = view.get<RenderComponent,
    TransformComponent>(entity); objectsToRender2.push_back(tuple);
    }//*/

    this->rendererSystem->InternalRender(this->curScene->m_Registry);
}

bool SceneHandler::onKey(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        mCatchCursor = !mCatchCursor;
        if (!mCatchCursor) {
            glfwSetInputMode(mWindow->window(), GLFW_CURSOR,
                             GLFW_CURSOR_NORMAL);
        }
    }

    return false;
}

bool SceneHandler::onMousePosition(double x, double y) {
    // if (TwEventMousePosGLFW(mWindow, x, y))
    //    return true;
    auto window = mWindow->window();
    mWindowWidth = mWindow->width();
    mWindowHeight = mWindow->height();
    if (mCatchCursor && mMouseLastX != 0.0 && rendererSystem->getCamera()) {
        auto alt = glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS;
        auto ctrl = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;

        auto dx = x - mMouseLastX;
        auto dy = y - mMouseLastY;

        float ax = (float)(dx / mWindowWidth * mCameraTurnSpeed);
        float ay = (float)(dy / mWindowHeight * mCameraTurnSpeed);

        if (!alt && !ctrl)  // from cam
        {
            rendererSystem->getCamera()->FPSstyleLookAround(ax, ay);
        }
    }

    mMouseLastX = x;
    mMouseLastY = y;
    return false;
}

bool SceneHandler::onMouseButton(double x, double y, int button, int action,
                                 int mods, int clickCount) {
    return false;
}

bool SceneHandler::onMouseScroll(double sx, double sy) { return false; }

bool SceneHandler::onMouseEnter() { return false; }

bool SceneHandler::onMouseExit() { return false; }

bool SceneHandler::onFocusGain() { return false; }

bool SceneHandler::onFocusLost() { return false; }

bool SceneHandler::onFileDrop(const std::vector<std::string>& files) {
    return false;
}

bool SceneHandler::onChar(unsigned int codepoint, int mods) { return false; }

void SceneHandler::internalOnMouseButton(double x, double y, int button,
                                         int action, int mods) {
    // check double click
    if (distance(mClickPos, glm::vec2(x, y)) > 5)  // too far
        mClickCount = 0;
    if (mClickTimer.seconds() > mDoubleClickTime)  // too slow
        mClickCount = 0;
    if (mClickButton != button)  // wrong button
        mClickCount = 0;

    mClickTimer.reset();
    mClickButton = button;
    mClickPos = {x, y};
    mClickCount++;

    onMouseButton(x, y, button, action, mods, mClickCount);
}

void SceneHandler::onResize(int w, int h) {
    if (rendererSystem != nullptr) {
        rendererSystem->Resize(w, h);
    }
}

void SceneHandler::updateInput() {
    if (mCatchCursor == true) {
        glfwSetInputMode(mWindow->window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    // Poll for and process events
    glfwPollEvents();
}