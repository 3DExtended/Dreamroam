#pragma once
#include <entt/entt.hpp>

namespace DCore
{
	namespace ComponentSystem
	{
		class UntypedSystemBase
		{
		public:
			UntypedSystemBase() = default;
			UntypedSystemBase(const UntypedSystemBase& other) = default;
		protected:
			friend class SceneHandler;

			virtual void InternalAwake(entt::registry& reg) {};
			virtual void InternalStart(entt::registry& reg) {};
			virtual void InternalUpdate(entt::registry& reg, double dt) {};
			virtual void InternalLateUpdate(entt::registry& reg, double dt) {};
			virtual void InternalDestroy(entt::registry& reg) {};
		};
	} // namespace ComponentSystem
} // namespace DCore