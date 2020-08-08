#include <glm/glm.hpp>

#include "Entity.hh"
#include "SceneHandler.hh"
#include "AScene.hh"

namespace DCore
{
	namespace ComponentSystem
	{
		Entity::Entity(entt::entity handle, AScene* scene)
			: m_EntityHandle(handle), m_Scene(scene)
		{
		}
	}
}