#pragma once

#include <lava/objects/GraphicsPipeline.hh>
#include <lava-extras/geometry/fwd.hh>
#include <lava/fwd.hh>
#include <lava-extras/pipeline/RenderingPipeline.hh>
#include <lava/objects/RenderPass.hh>
#include <lava/raii/ActiveRenderPass.hh>
#include <lava/createinfos/GraphicsPipelineCreateInfo.hh>
#include <lava-extras/camera/fwd.hh>
#include <lava/fwd.hh>

namespace DCore
{
	namespace ComponentSystem
	{
		class GameObject;
		class AScene;

		/// <summary>
		/// This class is abstract and has to be inherited.
		/// It provides the standard functions as start() or update() and when added to an active GameObject instance is called by the engine.
		/// It also provides basic functionality to the engine like a ShowMouse function.
		/// </summary>
		class AComponent
		{
		public:
			AComponent() {};

			/// <summary>
			/// Returns a handle to the active scene (to access their functionalities).
			/// </summary>
			/// <returns>A pointer to the active/current scene.</returns>
			std::shared_ptr<AScene> getCurrentScene();

			/// <summary>
			/// Returns a pointer to the gameObject the component is running on/connected to.
			/// </summary>
			/// <returns>A pointer to the gameObject.</returns>
			std::weak_ptr<GameObject> getCurrentGameObject() { return gameObject; };

			/// <summary>
			/// Creates a new gameObject with name "".
			/// This GameObject is introduced to the current scene.
			/// </summary>
			/// <returns>A pointer to the empty gameObject.</returns>
			std::shared_ptr<GameObject> instantiate();

			/// <summary>
			/// Creates a new gameObject with a specified name.
			/// This GameObject is introduced to the current scene.
			/// </summary>
			/// <param name="name" >The name for the new GameObject</param>
			/// <returns>A pointer to the empty gameObject with the name.</returns>
			std::shared_ptr<GameObject> instantiate(std::string name);

		private:
			friend class GameObject; //So the GameObject can call the component standard functions

			/// <summary>
			/// This function is called in the following frame after the component was created.
			/// Is called BEFORE start().
			/// </summary>
			virtual void awake() {};

			/// <summary>
			/// This function is called in the following frame after the component was created
			/// Is called AFTER awake().
			/// </summary>
			virtual void start() {};

			/// <summary>
			/// This function is called each frame to update the component (and/or scene).
			/// Is called as first update function each frame.
			/// </summary>
			virtual void update(double dt) {};

			/// <summary>
			/// This function is called each frame to update the component (and/or scene).
			/// Is called AFTER update().
			/// </summary>
			virtual void lateUpdate() {};

			/// <summary>
			/// This function is called when the component gets destroyed.
			/// </summary>
			virtual void destroy() {};

		protected:
			friend class GameObject;

			//a pointer to the current GameObject
			std::weak_ptr<GameObject> gameObject;
		};
	}
}