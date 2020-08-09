#pragma once

#include <memory>
#include <map>
#include <string>
#include <lava/objects/Device.hh>

#include "RenderComponent.hh"
#include <ComponentBased/Systems/SystemBase.hh>
#include <ComponentBased/BaseComponents.hh>
#include <RenderingSystem/Pipeline/GraphicsPipelineRenderer.hh>

namespace DCore {
	namespace Rendering {
		using namespace DCore::ComponentSystem;
		class RenderingSystemBase : public SystemBase<RenderComponent, TransformComponent>
		{
		public:
			RenderingSystemBase() = default;

			~RenderingSystemBase() = default;

			virtual void Render(entt::basic_view<entt::entity, entt::exclude_t<>, RenderComponent, TransformComponent> entities) {};
			virtual void Resize(int width, int height) {};
			virtual lava::camera::SharedGenericCamera getCamera() = 0;

		private:
			friend class DCore::ComponentSystem::SceneHandler;
			virtual void InternalRender(entt::registry& reg) { this->Render(GetEntitiesFromRegistry(reg)); }
		};
	}
}