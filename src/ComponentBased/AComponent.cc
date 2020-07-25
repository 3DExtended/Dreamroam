#include <glm/glm.hpp>

#include "AComponent.hh"
#include "GameObject.hh"
#include "SceneHandler.hh"
#include "AScene.hh"

std::shared_ptr<AScene> AComponent::getCurrentScene()
{
	return SceneHandler::getCurrentScene();
}

std::shared_ptr<GameObject> AComponent::instantiate()
{
	return instantiate("");
}

std::shared_ptr<GameObject> AComponent::instantiate(std::string name)
{
	return getCurrentScene()->instantiate(name);
}