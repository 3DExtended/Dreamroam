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
#include <entt/entt.hpp>

#include "../AScene.hh"

namespace DCore
{
	namespace ComponentSystem
	{
		template <class firstType, class... Types>
		class SystemBase
		{
		public:
			SystemBase() = default;
			SystemBase(const SystemBase& other) = default;

			// TODO all this methods (including the Render method of the rendering system should take a custom wrapper around the basic view..
			// We don't want to expose external dependencies.

			virtual void Awake(entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...> entities) {};
			virtual void Start(entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...> entities) {};
			virtual void Update(entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...> entities) {};
			virtual void LateUpdate(entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...> entities) {};
			virtual void Destroy(entt::basic_view<entt::entity, entt::exclude_t<>, firstType, Types...> entities) {};

		protected:
			auto GetEntitiesFromRegistry(entt::registry& reg) {
				auto view = reg.view<firstType, Types...>();
				return view;
			}

		private:
			friend class DCore::ComponentSystem::SceneHandler;
			virtual void InternalAwake(entt::registry& reg) { this->Awake(GetEntitiesFromRegistry(reg)); }
			virtual void InternalStart(entt::registry& reg) { this->Start(GetEntitiesFromRegistry(reg)); }
			virtual void InternalUpdate(entt::registry& reg) { this->Update(GetEntitiesFromRegistry(reg)); }
			virtual void InternalLateUpdate(entt::registry& reg) { this->LateUpdate(GetEntitiesFromRegistry(reg)); }
			virtual void InternalDestroy(entt::registry& reg) { this->Destroy(GetEntitiesFromRegistry(reg)); }
		};
	} // namespace ComponentSystem
} // namespace DCore