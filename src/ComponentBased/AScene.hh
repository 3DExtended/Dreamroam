#pragma once

#include <vector>

#include "glm/glm.hpp"
#include <RenderObjects/GeometryStore.hh>
#include <RenderObjects/TextureStore.hh>

#include "GameObject.hh"
#include "AComponent.hh"

class GameObject;
class AComponent;

class AScene
{
  public:
	AScene();
	~AScene();

	virtual void start(){};
	virtual void update(double dt){};
	virtual void destroy(){};

	std::shared_ptr<GameObject> instantiate();

	std::shared_ptr<GameObject> instantiate(const std::string name);

  protected:
	lava::SharedDevice mDevice;

	std::shared_ptr<GeometryStore> mGeometryStore;
	std::shared_ptr<TextureStore> mTextureStore;

  private:
	std::vector<std::shared_ptr<GameObject>> gameObjects;

  private:
	friend class SceneHandler;
	void gameObjectAwake();
	void gameObjectStart();
	void gameObjectUpdate(double dt);
	void gameObjectLateUpdate();
	void gameObjectDestroy();

	const lava::SharedDescriptorSetLayout getTextureLayout();
};
