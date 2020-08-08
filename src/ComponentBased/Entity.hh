#pragma once

/**
  DCore is the namespace for the engine.
  It provides access to all the structures needed to apply this engine.
  However, if you'd like to add external functionalities, this namespace should provide typesafty.
  */

#include <lava/objects/GraphicsPipeline.hh>
#include <lava-extras/geometry/fwd.hh>
#include <lava/fwd.hh>
#include <lava-extras/pipeline/RenderingPipeline.hh>
#include <lava/objects/RenderPass.hh>
#include <lava/raii/ActiveRenderPass.hh>
#include <lava/createinfos/GraphicsPipelineCreateInfo.hh>
#include <lava-extras/camera/fwd.hh>
#include <lava/fwd.hh>

#include "AScene.hh"

namespace DCore
{
	namespace ComponentSystem
	{
		class Entity
		{
		public:
			Entity() = default;
			Entity(entt::entity handle, AScene* scene);
			Entity(const Entity& other) = default;

			template<typename T, typename... Args>
			T& AddComponent(Args&&... args)
			{
				assert(!HasComponent<T>(), "Entity already has component!");
				return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			}

			template<typename T>
			T& GetComponent()
			{
				assert(HasComponent<T>(), "Entity does not have component!");
				return m_Scene->m_Registry.get<T>(m_EntityHandle);
			}

			template<typename T>
			bool HasComponent()
			{
				return m_Scene->m_Registry.has<T>(m_EntityHandle);
			}

			template<typename T>
			void RemoveComponent()
			{
				assert(HasComponent<T>(), "Entity does not have component!");
				m_Scene->m_Registry.remove<T>(m_EntityHandle);
			}

			operator bool() const { return m_EntityHandle != entt::null; }

		private:
			entt::entity m_EntityHandle{ entt::null };
			AScene* m_Scene = nullptr;
		};
	} // namespace ComponentSystem
} // namespace DCore