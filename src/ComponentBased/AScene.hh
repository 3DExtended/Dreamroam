#pragma once

#include <vector>

#include "glm/glm.hpp"
#include <RenderObjects/GeometryStore.hh>
#include <RenderObjects/TextureStore.hh>

#include "GameObject.hh"
#include "AComponent.hh"

class GameObject;
class AComponent;

/// <summary>
/// This class is abstract and has to be inherited.
/// It provides the standard functions as start() or update().
/// Use your instance of this class in combination with the SceneHandler to define your world.
/// </summary>
class AScene
{
public:
	/// <summary>
	/// Creates the rendering device instance.
	/// </summary>
	AScene();

	~AScene();

	/// <summary>
	/// This is called right after the sceneHandler switches to the new scene.
	/// Use this to register your gameObjects, textures and components.
	/// </summary>
	virtual void start() {};

	/// <summary>
	/// This is called for each frame while the scene is loaded.
	/// Can be used to call all entity systems.
	/// Note: This function should not be used to run the games logic. However, at the current time this is all you got.
	/// </summary>
	/// <param name="dt">Delta Time of the frame in seconds</param>
	virtual void update(double dt) {};

	/// <summary>
	/// This is called right before this scene is destroyed. Use this to deconstruct any game objects and handlers.
	/// </summary>
	virtual void destroy() {};

	/// <summary>
	/// Creates and registers a new game object.
	/// The name of this game object will be the empty string.
	/// Please note that you need to keep your own pointer to this object when you want to update it later.
	/// </summary>
	/// <returns>A new gameObject instance.</returns>
	std::shared_ptr<GameObject> instantiate();

	/// <summary>
	/// Creates and registers a new game object.
	/// Please note that you need to keep your own pointer to this object when you want to update it later.
	/// </summary>
	/// <param name="name">The name of the gameObject in the scene.</param>
	/// <returns>A new gameObject instance.</returns>
	std::shared_ptr<GameObject> instantiate(const std::string name);

protected:
	/// <summary>
	/// The device which is used to render the scene.
	/// This will be used for a number of initialization procedures.
	/// </summary>
	lava::SharedDevice mDevice;

	/// <summary>
	/// This GeometryStore is used to load meshes and push them to the GPU.
	/// </summary>
	std::shared_ptr<GeometryStore> mGeometryStore;

	/// <summary>
	/// This TextureStore is used to load textures and push them to the GPU.
	/// </summary>
	std::shared_ptr<TextureStore> mTextureStore;

private:
	/// <summary>
	/// The list of registered gameObjects for this scene.
	/// </summary>
	std::vector<std::shared_ptr<GameObject>> gameObjects;

private:
	/// <summary>
	/// The only class that should be able to call the gameObject handlers is the SceneHandler. Thus, we define it as friend class here.
	/// </summary>
	friend class SceneHandler;

	void gameObjectAwake();
	void gameObjectStart();
	void gameObjectUpdate(double dt);
	void gameObjectLateUpdate();
	void gameObjectDestroy();

	const lava::SharedDescriptorSetLayout getTextureLayout();
};