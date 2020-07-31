#include "SceneHandler.hh"
#include "GlobalSettings.hh"
#include <RenderingSystem/PushConstants.hh>
#include <Components/RenderComponent.hh>

#include <thread>
#include <limits>
#include <lava/createinfos/Sampler.hh>

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <lava/common/log.hh>
#include <lava/features/MultiView.hh>
#include <lava/features/GlfwOutput.hh>
#include <lava/gpuselection/NthOfTypeStrategy.hh>
#include <lava/objects/Instance.hh>
#include <lava-extras/camera/GenericCamera.hh>
#include <lava/createinfos/Images.hh>
#include <lava/objects/Image.hh>
#include <lava/objects/Framebuffer.hh>
#include <lava/objects/ImageView.hh>
#include <lava/objects/DescriptorSetLayout.hh>
#include <lava/objects/Buffer.hh>
#include <lava/createinfos/Buffers.hh>
#include <lava/createinfos/DescriptorSetLayoutCreateInfo.hh>

using namespace DCore::Components;

float lightFOV = 45.0f;
// Keep depth range as small as possible
	// for better shadow map precision
float zNear = 1.0f;
float zFar = 96.0f;
std::shared_ptr<SceneHandler> SceneHandler::instance = nullptr;

std::shared_ptr<SceneHandler> SceneHandler::getInstance()
{
	if (instance == nullptr)
		instance = std::make_shared<SceneHandler>();
	return instance;
}

SceneHandler::~SceneHandler()
{
}

void SceneHandler::_switchScene(uint16_t index)
{
	if (curScene == nullptr && scenes.size() == 0)
	{
		std::cerr << "There are no scenes to switch to.." << std::endl;
	}
	else if (index >= scenes.size())
	{
		std::cerr << "The scene you want to switch to is not registered." << std::endl;
	}
	else
	{
		if (curScene != nullptr)
		{
			curScene->gameObjectDestroy();
			curScene->destroy();
		}
		curScene = scenes.at(index);
		start();
	}
}

uint16_t SceneHandler::_addScene(std::shared_ptr<AScene> newScene)
{
	scenes.push_back(newScene);
	return scenes.size() - 1;
}

lava::SharedDevice SceneHandler::_getDevice() const
{
	return mDevice;
}

std::shared_ptr<lava::features::GlfwOutput> SceneHandler::getGlfwOutput() const
{
	return mGlfwOutput;
}

void SceneHandler::run()
{
	assert(scenes.size() > 0);

	switchScene(0);
	mWindowWidth = GlobalSettings::windowWidth;
	mWindowHeight = GlobalSettings::windowHeight;
	setupRendering();

	double lastCpuTime = glfwGetTime();

	//FPS measuring
	uint16_t frames = 0;
	double FPStime = glfwGetTime();

	while (!glfwWindowShouldClose(mWindow->window()))
	{
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

		// TODO(esser): remove this when we have a scene that takes longer to render than the default cube scene...
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void SceneHandler::updateCamera(double elapsedSeconds)
{
	auto window = mWindow->window();
	if (mPipeline->getCamera())
	{
		auto speed = mCameraMoveSpeed;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			speed *= mCameraMoveSpeedFactor;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			mPipeline->getCamera()->moveForward(elapsedSeconds * speed);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			mPipeline->getCamera()->moveBack(elapsedSeconds * speed);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			mPipeline->getCamera()->moveLeft(elapsedSeconds * speed);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			mPipeline->getCamera()->moveRight(elapsedSeconds * speed);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			mPipeline->getCamera()->moveDown(elapsedSeconds * speed);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			mPipeline->getCamera()->moveUp(elapsedSeconds * speed);
	}
}

SceneHandler::SceneHandler()
{
	// Create device handle for vulkan
	std::vector<lava::features::SharedFeature> lavaFeatures;

	// Multiview
	auto multiview = lava::features::MultiView::create();
	lavaFeatures.push_back(multiview);

	// GLFW Output
	mGlfwOutput = lava::features::GlfwOutput::create();
	lavaFeatures.push_back(mGlfwOutput);

	if (GlobalSettings::useValidation)
	{
		mValidation = lava::features::Validation::create();
		lavaFeatures.push_back(mValidation);
	}

	// === Create instance and device: ===
	lava::SharedInstance lavaInstance = lava::Instance::create(lavaFeatures);

	mDevice = lavaInstance->createDevice(
		{ lava::QueueRequest::graphics("graphics") },
		lava::NthOfTypeStrategy(vk::PhysicalDeviceType::eDiscreteGpu));
}

void SceneHandler::setupGlfwCallbacks()
{
	static std::unordered_map<GLFWwindow*, SceneHandler*> sWindowApps;

	auto window = mWindow->window();
	auto insertion = sWindowApps.insert({ window, this }).second;
	assert(insertion && "You can only have one app per GLFWwindow.");

	glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode,
		int action, int mods) {
			sWindowApps.at(win)->onKey(key, scancode, action, mods);
		});

	glfwSetCharModsCallback(
		window, [](GLFWwindow* win, unsigned int codepoint,
			int mods) { sWindowApps.at(win)->onChar(codepoint, mods); });

	glfwSetMouseButtonCallback(
		window, [](GLFWwindow* win, int button, int action, int mods) {
			auto app = sWindowApps.at(win);
			app->internalOnMouseButton(app->mMouseX, app->mMouseY, button,
				action, mods);
		});

	glfwSetCursorEnterCallback(window, [](GLFWwindow* win, int entered) {
		try
		{
			auto app = sWindowApps.at(win);
			if (entered)
				app->onMouseEnter();
			else
				app->onMouseExit();
		}
		catch (std::out_of_range)
		{
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

void SceneHandler::start()
{
	curScene->start();
	curScene->gameObjectAwake();
	curScene->gameObjectStart();
}

void SceneHandler::update(double dt)
{
	curScene->update(dt);
	curScene->gameObjectUpdate(dt);
	curScene->gameObjectLateUpdate();
}

void SceneHandler::setupRendering()
{
	uint32_t width = GlobalSettings::windowWidth;
	uint32_t height = GlobalSettings::windowHeight;
	mWindow = getGlfwOutput()->openWindow(width, height, false, "Lava Companion Window");

	mWindow->buildSwapchainWith(
		[&](std::vector<lava::SharedImageView> const&) {});

	setupPipeline(curScene->getTextureLayout());

	mOpaqueUntextured = GraphicsPipelineFactory::createRenderer_opaqueUntextured(mDevice, mPlLayout, mPipeline);
	mOpaqueTextured = GraphicsPipelineFactory::createRenderer_opaqueTextured(mDevice, mPlLayout, mPipeline);
	mTransparendUntextured = GraphicsPipelineFactory::createRenderer_transparentUntextured(mDevice, mPlLayout, mPipeline);
	mTransparendTextured = GraphicsPipelineFactory::createRenderer_transparentTextured(mDevice, mPlLayout, mPipeline);
	mShadowMap = GraphicsPipelineFactory::createRenderer_shadowMap(mDevice, mPlLayout, mPipeline);
}

void SceneHandler::setupPipeline(const lava::SharedDescriptorSetLayout textureLayout)
{
	// Setup GLFW
	{
		mWindow = mGlfwOutput->openWindow(GlobalSettings::windowWidth, GlobalSettings::windowHeight, false, "DreamRoam");
		this->setupGlfwCallbacks();
	}

	// create CameraDataBuffer
	{
		// pre pass
		{
			mViewProjBufferPrePass = mDevice->createBuffer(
				lava::uniformBuffer(sizeof(CameraDataPrePass)));

			mViewProjBufferPrePass->keepStagingBuffer();
			mViewProjBufferPrePass->realizeVRAM();

			auto dslinfo = lava::DescriptorSetLayoutCreateInfo{};
			dslinfo.addUniformBuffer(vk::ShaderStageFlagBits::eAllGraphics);
			dslinfo.addUniformBuffer(vk::ShaderStageFlagBits::eAllGraphics);

			mViewProjDescriptorSetLayoutPrePass = dslinfo.create(mDevice);

			mViewProjDescriptorPre =
				mViewProjDescriptorSetLayoutPrePass->createDescriptorSet();
			mViewProjDescriptorPre->writeUniformBuffer(mViewProjBufferPrePass, 0);
		}

		// forward pass
		{
			mViewProjBufferForwardPass = mDevice->createBuffer(
				lava::uniformBuffer(sizeof(CameraDataForwardPass)));

			mViewProjBufferForwardPass->keepStagingBuffer();
			mViewProjBufferForwardPass->realizeVRAM();

			auto dslinfo = lava::DescriptorSetLayoutCreateInfo{};
			dslinfo.addUniformBuffer(vk::ShaderStageFlagBits::eAllGraphics);
			dslinfo.addUniformBuffer(vk::ShaderStageFlagBits::eAllGraphics);

			mViewProjDescriptorSetLayoutForwarPass = dslinfo.create(mDevice);

			mViewProjDescriptorForward =
				mViewProjDescriptorSetLayoutForwarPass->createDescriptorSet();
			mViewProjDescriptorForward->writeUniformBuffer(mViewProjBufferForwardPass, 0);
		}
	}

	// Object Rendering Pipeline
	{
		VkPushConstantRange pushConstantRange{
			VK_SHADER_STAGE_ALL,
			0,
			sizeof(PushConstants) };

		mPipeline = std::make_shared<lava::pipeline::AdvancedRenderingPipeline>(
			mDevice, mGlfwOutput->format());

		mPlLayout = mDevice->createPipelineLayout(
			{ pushConstantRange },
			{ mViewProjDescriptorForward->layout(), textureLayout, mPipeline->mForwardDescriptorLayout });

		mPipeline->getCamera()->setVerticalFieldOfView(60);
		mPipeline->getCamera()->setFarClippingPlane(25);
		mPipeline->getCamera()->setPosition({ 5, 2, 5 });
	}

	mWindow->buildSwapchainWith(
		[&](std::vector<lava::SharedImageView> const& views) {
			mPipeline->resize(mWindow->width(), mWindow->height());
			companionWindowFBO.clear();
			for (auto& view : views)
				companionWindowFBO.push_back(mPipeline->outputPass()->createFramebuffer({ view }));
		});
}

void SceneHandler::getFrustumCorners(std::vector<glm::vec4>& corners, glm::mat4 inverseProjection)
{
	corners.clear();

	// homogeneous corner coords
	glm::vec4 hcorners[8];
	// near
	hcorners[0] = glm::vec4(-1, 1, 1, 1);
	hcorners[1] = glm::vec4(1, 1, 1, 1);
	hcorners[2] = glm::vec4(1, -1, 1, 1);
	hcorners[3] = glm::vec4(-1, -1, 1, 1);
	// far
	hcorners[4] = glm::vec4(-1, 1, -1, 1);
	hcorners[5] = glm::vec4(1, 1, -1, 1);
	hcorners[6] = glm::vec4(1, -1, -1, 1);
	hcorners[7] = glm::vec4(-1, -1, -1, 1);

	glm::mat4 inverseProj = inverseProjection;
	for (int i = 0; i < 8; i++) {
		hcorners[i] = inverseProj * hcorners[i];
		hcorners[i] /= hcorners[i].w;

		corners.push_back(hcorners[i]);
	}
}

std::tuple<glm::mat4, glm::mat4> SceneHandler::rotateCameraFrustrumCornersToLightSpace(
	glm::vec3 lightDir,
	glm::vec3 camPosition,
	glm::vec3 upDirection = glm::vec3(0, 1, 0))
{
	std::vector<glm::vec4> corners;

	glm::vec3 cameraForward = mPipeline->getCamera()->getForwardDirection();
	glm::vec3 cameraUp = mPipeline->getCamera()->getUpDirection();

	glm::mat4 inverseCameraViewProj = glm::inverse(
		mPipeline->getCamera()->getProjectionMatrix()
		* glm::lookAt(glm::vec3(0), glm::vec3(0) + cameraForward, cameraUp)
		* mPipeline->getCamera()->getTranslationMatrix4()
	);

	this->getFrustumCorners(corners, inverseCameraViewProj);

	float minX = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float minY = std::numeric_limits<float>::max();
	float maxY = std::numeric_limits<float>::min();
	float minZ = std::numeric_limits<float>::max();
	float maxZ = std::numeric_limits<float>::min();

	for (auto c : corners) {
		if (c[0] < minX) minX = c[0];
		if (c[0] > maxX) maxX = c[0];
		if (c[1] < minY) minY = c[1];
		if (c[1] > maxY) maxY = c[1];
		if (c[2] < minZ) minZ = c[2];
		if (c[2] > maxZ) maxZ = c[2];
	}

	glm::vec3 frustumCenter = glm::vec3((maxX + minX) / 2.0f, (maxY + minY) / 2.0f, (maxZ + minZ) / 2.0f);

	float maxDistance = 0.0;

	// TODO this should always be the same index of the corner array. improv this
	for (auto c : corners) {
		auto tempDistance = glm::distance(glm::vec4(frustumCenter, 1.0f), c);
		if (tempDistance > maxDistance) {
			maxDistance = tempDistance;
		}
	}

	// maxZ = 100;

	glm::mat4 proj = glm::orthoRH_ZO(maxDistance, -maxDistance, maxDistance, -maxDistance, 0.0f, maxDistance * 2.0f);

	glm::vec3 newEyePosition = frustumCenter - glm::normalize(lightDir) * maxDistance;
	glm::mat4 view =
		glm::lookAt(newEyePosition, newEyePosition + lightDir, glm::vec3(0, 1, 0));

	return std::tuple<glm::mat4, glm::mat4 >(proj, view);
}

void SceneHandler::render()
{
	//classify gameObjects based on their renderers
	std::vector<std::shared_ptr<GameObject>>
		opaqueUntexturedObjects,
		opaqueTexturedObjects,
		transparendUntexturedObjects,
		transparendTexturedObjects,
		shadowThrowingObjects = std::vector<std::shared_ptr<GameObject>>();

	recurseGameObjects(curScene->gameObjects,
		opaqueUntexturedObjects,
		opaqueTexturedObjects,
		transparendUntexturedObjects,
		transparendTexturedObjects,
		shadowThrowingObjects);

	// todo for shadow:
	// DONE 1.: create a new pipeline for rendering shadows
	// DONE 2.: setup a camera using this command for perspective rendering  (mPipeline->updateViewProjMatrices(cmd, mCamera->getViewMatrix(), mCamera->getProjectionMatrix());)
	// 2a.: figure out which area we want to render to the shadow map!
	// DONE 3.: render objects that throw shadow
	// 4.: use shadowmap in default shaders (textured and colored) (figure out how to bind mShadowPipelineOutput as an 2D image for shader access)
	mDevice->graphicsQueue().handle().waitIdle();

	{
		auto frame = mWindow->startFrame();
		auto cmd = mDevice->graphicsQueue().beginCommandBuffer();

		cmd.wait(frame.imageReady());

		// Create light view and projection matrix
		glm::mat4 lightProjMatrix;
		glm::mat4 lightViewMatrix;

		std::tie(lightProjMatrix, lightViewMatrix) = this->rotateCameraFrustrumCornersToLightSpace(
			glm::vec3(1.0f, 0.5f, -1.0f),
			mPipeline->getCamera()->getPosition(),
			mPipeline->getCamera()->getUpDirection());
		{
			CameraDataPrePass matrixData
			{
				lightViewMatrix,
				lightProjMatrix
			};
			mViewProjBufferPrePass->setDataVRAM(&matrixData, sizeof(matrixData), cmd);
		}

		// load scene camera
		{
			CameraDataForwardPass matrixData
			{
				mPipeline->getCamera()->getViewMatrix(),
				mPipeline->getCamera()->getProjectionMatrix(),
				lightProjMatrix * lightViewMatrix
			};
			mViewProjBufferForwardPass->setDataVRAM(&matrixData, sizeof(matrixData), cmd);
		}

		// render all objects.
		// Note that this includes two render passes.
		// The first one beeing for rendering objects to the shadow map and the second one rendering all objects.
		mPipeline->render(cmd, companionWindowFBO[frame.imageIndex()],
			[&](lava::pipeline::AdvancedRenderPass const& pass) {
				auto sub = pass.pass.startInlineSubpass();

				if (pass.type == lava::pipeline::RenderPassType::Shadow)
				{
					sub.setViewports(
						{ {0, 0, float(mWindow->width()), float(mWindow->height())} });

					mShadowMap->prepareRendering(&sub, mViewProjDescriptorPre);
					mShadowMap->renderGameObjects(shadowThrowingObjects);
				}
				else if (pass.type == lava::pipeline::RenderPassType::Opaque)
				{
					sub.setViewports(
						{ {0, 0, float(mWindow->width()), float(mWindow->height())} });

					if (opaqueUntexturedObjects.size() > 0) {
						mOpaqueUntextured->prepareRendering(&sub, mViewProjDescriptorForward);
						mOpaqueUntextured->renderGameObjects(opaqueUntexturedObjects);
					}

					if (opaqueTexturedObjects.size() > 0) {
						mOpaqueTextured->prepareRendering(&sub, mViewProjDescriptorForward);
						mOpaqueTextured->renderGameObjects(opaqueTexturedObjects);
					}

					if (transparendUntexturedObjects.size() > 0) {
						mTransparendUntextured->prepareRendering(&sub, mViewProjDescriptorForward);
						mTransparendUntextured->renderGameObjects(transparendUntexturedObjects);
					}

					if (transparendTexturedObjects.size() > 0) {
						mTransparendTextured->prepareRendering(&sub, mViewProjDescriptorForward);
						mTransparendTextured->renderGameObjects(transparendTexturedObjects);
					}
				}
			});
		cmd.signal(frame.renderingComplete());
	}
}

bool SceneHandler::onKey(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS && mPipeline)
	{
		mPipeline->setFXAA(!mPipeline->getFXAA());
		std::cout << "Turned FXAA "
			<< ((mPipeline->getFXAA()) ? "on" : "off");
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		mCatchCursor = !mCatchCursor;
		if (!mCatchCursor)
		{
			glfwSetInputMode(mWindow->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	return false;
}

bool SceneHandler::onMousePosition(double x, double y)
{
	// if (TwEventMousePosGLFW(mWindow, x, y))
	//    return true;
	auto window = mWindow->window();
	mWindowWidth = mWindow->width();
	mWindowHeight = mWindow->height();
	if (mCatchCursor && mMouseLastX != 0.0 && mPipeline->getCamera())
	{
		auto alt = glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS;
		auto ctrl = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;

		auto dx = x - mMouseLastX;
		auto dy = y - mMouseLastY;

		float ax = (float)(dx / mWindowWidth * mCameraTurnSpeed);
		float ay = (float)(dy / mWindowHeight * mCameraTurnSpeed);

		if (!alt && !ctrl) // from cam
		{
			mPipeline->getCamera()->FPSstyleLookAround(ax, ay);
		}
	}

	mMouseLastX = x;
	mMouseLastY = y;
	return false;
}

bool SceneHandler::onMouseButton(double x, double y, int button, int action,
	int mods, int clickCount)
{
	return false;
}

bool SceneHandler::onMouseScroll(double sx, double sy)
{
	return false;
}

bool SceneHandler::onMouseEnter() { return false; }

bool SceneHandler::onMouseExit() { return false; }

bool SceneHandler::onFocusGain() { return false; }

bool SceneHandler::onFocusLost() { return false; }

bool SceneHandler::onFileDrop(const std::vector<std::string>& files)
{
	return false;
}

bool SceneHandler::onChar(unsigned int codepoint, int mods)
{
	return false;
}

void SceneHandler::internalOnMouseButton(double x, double y, int button, int action,
	int mods)
{
	// check double click
	if (distance(mClickPos, glm::vec2(x, y)) > 5) // too far
		mClickCount = 0;
	if (mClickTimer.seconds() > mDoubleClickTime) // too slow
		mClickCount = 0;
	if (mClickButton != button) // wrong button
		mClickCount = 0;

	mClickTimer.reset();
	mClickButton = button;
	mClickPos = { x, y };
	mClickCount++;

	onMouseButton(x, y, button, action, mods, mClickCount);
}

void SceneHandler::onResize(int w, int h)
{
	if (mPipeline->getCamera())
		mPipeline->getCamera()->resize(w, h);
	if (mPipeline)
		mPipeline->resize(w, h);
}

void SceneHandler::updateInput()
{
	if (mCatchCursor == true)
	{
		glfwSetInputMode(mWindow->window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	// Poll for and process events
	glfwPollEvents();
}

void SceneHandler::recurseGameObjects(
	std::vector<std::shared_ptr<GameObject>> objects,
	std::vector<std::shared_ptr<GameObject>>& opaqueUntexturedObjects,
	std::vector<std::shared_ptr<GameObject>>& opaqueTexturedObjects,
	std::vector<std::shared_ptr<GameObject>>& transparendUntexturedObjects,
	std::vector<std::shared_ptr<GameObject>>& transparendTexturedObjects,
	std::vector<std::shared_ptr<GameObject>>& shadowThrowingObjects
) {
	for (size_t i = 0; i < objects.size(); i++)
	{
		auto go = objects.at(i);

		auto renderer = go->getComponent<RenderComponent>();
		if (renderer != nullptr)
		{
			if (renderer->active)
			{
				if (renderer->isThrowingShadow) {
					shadowThrowingObjects.push_back(go);
				}
				if (renderer->hasTexture)
				{
					renderer->isTransparent ? transparendTexturedObjects.push_back(go) : opaqueTexturedObjects.push_back(go);
				}
				else
				{
					renderer->isTransparent ? transparendUntexturedObjects.push_back(go) : opaqueUntexturedObjects.push_back(go);
				}
			}
		}

		recurseGameObjects(go->getChilds(),
			opaqueUntexturedObjects,
			opaqueTexturedObjects,
			transparendUntexturedObjects,
			transparendTexturedObjects,
			shadowThrowingObjects);
	}
}