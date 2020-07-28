#pragma once
#include <ComponentBased/AScene.hh>
#include "AComponent.hh"
#include "GameObject.hh"
#include <RenderingSystem/GraphicsPipelineFactory.hh>
#include "RenderingSystem/AdvancedRenderingPipeline.hh"

#include <vector>
#include <iostream>

#include <lava/features/Validation.hh>
#include <lava/objects/Device.hh>
#include <lava-extras/glfw/GlfwApp.hh>
namespace DCore
{
	namespace ComponentSystem
	{
		class GameObject;
		class AComponent;

		/// <summary>
		/// A SceneHandler is the manager of the game engine.
		/// It implements the singleton pattern and provides getters for the current scene,
		/// the switch scene method and more.
		/// </summary>
		class SceneHandler
		{
		public:
			/// <summary>
			/// Singleton pattern getter. Use this to get the scene handler from within your components.
			/// </summary>
			/// <returns>The current scene handler</returns>
			static std::shared_ptr<SceneHandler> getInstance();

			/// <summary>
			/// Add scene to the game. This has to be called before you can switch to this scene.
			/// </summary>
			/// <param name="newScene">The scene you want to add.</param>
			/// <returns>The index of the newly added scene</returns>
			static uint16_t addScene(std::shared_ptr<AScene> newScene) { return getInstance()->_addScene(newScene); }

			/// <summary>
			/// Getter for the currently loaded scene.
			/// </summary>
			/// <returns>A pointer to the currently loaded scene</returns>
			static std::shared_ptr<AScene> getCurrentScene() { return getInstance()->_getCurrentScene(); }

			/// <summary>
			/// Getter for the currently loaded scene.
			/// </summary>
			/// <returns>A pointer to the currently loaded scene</returns>
			static lava::SharedDevice getDevice() { return getInstance()->_getDevice(); }

			/// <summary>
			/// Switches the loaded and rendered scene.
			/// The index used here is returned in addScene(...).
			/// </summary>
			/// <param name="sceneIndex">The index of the scene to switch to.</param>
			static void switchScene(uint16_t sceneIndex) { getInstance()->_switchScene(sceneIndex); }

			std::shared_ptr<lava::features::GlfwOutput> getGlfwOutput() const;

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

			lava::SharedBuffer mViewProjBufferPrePass;

			lava::SharedBuffer mViewProjBufferForwardPass;
			lava::SharedDescriptorSet mViewProjDescriptorForward;
			lava::SharedDescriptorSet mViewProjDescriptorPre;

		public:
			static std::shared_ptr<SceneHandler> instance;
			std::vector<std::shared_ptr<AScene>> scenes;

			std::shared_ptr<AScene> curScene = nullptr;

			std::shared_ptr<lava::features::GlfwOutput> mGlfwOutput;
			std::shared_ptr<lava::features::Validation> mValidation;
			std::shared_ptr<lava::features::GlfwWindow> mWindow;
			lava::SharedDevice mDevice;

			void setupPipeline(const lava::SharedDescriptorSetLayout textureLayout);

			void getFrustumCorners(std::vector<glm::vec4>& corners, glm::mat4 projection);

			std::tuple<glm::mat4, glm::mat4> rotateCameraFrustrumCornersToLightSpace(glm::vec3 forward, glm::vec3 camPosition, glm::vec3 upDirection);

			lava::SharedPipelineLayout mPlLayout;
			std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> mPipeline;
			std::vector<lava::SharedFramebuffer> companionWindowFBO;

			void setupGlfwCallbacks();

			/// <summary>
			/// Creates a new instance of the scene handler. Should only be called ONCE by the main function.
			/// </summary>
			/// <remarks>This should not be used to create a new instance. Instead, please use the GetInstance method.</remarks>
			/// <remarks>This needs to be public in order to create a new instance using std::make_shared in the GetInstance method.</remarks>
			/// <returns>A new SceneHandler</returns>
			SceneHandler();

			~SceneHandler();

		private:
			lava::SharedDescriptorSetLayout mViewProjDescriptorSetLayoutPrePass;
			lava::SharedDescriptorSetLayout mViewProjDescriptorSetLayoutForwarPass;

		private:

			void _switchScene(uint16_t index);

			lava::SharedDevice _getDevice() const;

			uint16_t _addScene(std::shared_ptr<AScene> newScene);

			std::shared_ptr<AScene> _getCurrentScene() { return curScene; }

			void start();
			void setupRendering();
			void update(double dt);
			void recurseGameObjects(std::vector<std::shared_ptr<GameObject>> objects, std::vector<std::shared_ptr<GameObject>>& opaqueUntexturedObjects, std::vector<std::shared_ptr<GameObject>>& opaqueTexturedObjects, std::vector<std::shared_ptr<GameObject>>& transparendUntexturedObjects, std::vector<std::shared_ptr<GameObject>>& transparendTexturedObjects, std::vector<std::shared_ptr<GameObject>>& shadowThrowingObjects);
			void render();
			bool onKey(int key, int scancode, int action, int mods);
			bool onMousePosition(double x, double y);
			bool onMouseButton(double x, double y, int button, int action, int mods, int clickCount);
			bool onMouseScroll(double sx, double sy);
			bool onMouseEnter();
			bool onMouseExit();
			bool onFocusGain();
			bool onFocusLost();
			bool onFileDrop(const std::vector<std::string>& files);
			bool onChar(unsigned int codepoint, int mods);
			void internalOnMouseButton(double x, double y, int button, int action, int mods);
			void onResize(int w, int h);
			void updateInput();

		protected:
			std::shared_ptr<GraphicsPipelineRenderer> mOpaqueUntextured;
			std::shared_ptr<GraphicsPipelineRenderer> mOpaqueTextured;
			std::shared_ptr<GraphicsPipelineRenderer> mTransparendUntextured;
			std::shared_ptr<GraphicsPipelineRenderer> mTransparendTextured;
			std::shared_ptr<GraphicsPipelineRenderer> mShadowMap;
		};
	}
}