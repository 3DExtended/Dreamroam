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

#include "../AScene.hh"

namespace DCore
{
	namespace ComponentSystem
	{
		template <class... Types>
		class SystemBase
		{
		public:
			SystemBase() = default;
			SystemBase(const SystemBase& other) = default;

			virtual void Awake(std::vector<std::tuple<Types...>> entities) {};
			virtual void Start(std::vector<std::tuple<Types...>> entities) {};
			virtual void Update(std::vector<std::tuple<Types...>> entities) {};
			virtual void LateUpdate(std::vector<std::tuple<Types...>> entities) {};
			virtual void Destroy(std::vector<std::tuple<Types...>> entities) {};
		};
	} // namespace ComponentSystem
} // namespace DCore