#pragma once

#include <lava/raii/ActiveRenderPass.hh>
#include <lava/objects/GraphicsPipeline.hh>
#include <RenderingSystem/Pipeline/AdvancedRenderingPipeline.hh>
#include "../RenderComponent.hh"
#include <ComponentBased/BaseComponents.hh>

#include <entt/entt.hpp>

namespace DCore {
	namespace Rendering {
		using namespace DCore::ComponentSystem;

		class RendererBase
		{
		public:
			explicit RendererBase(
				std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline>,
				lava::SharedGraphicsPipeline pipeline,
				lava::SharedPipelineLayout layout);

			virtual ~RendererBase() {};

			void prepareRendering(
				lava::InlineSubpass* sub, lava::SharedDescriptorSet cameraDescriptor);

			void renderGameObjects(const std::vector<std::tuple<RenderComponent&, TransformComponent&>>& gos);

		protected:
			lava::SharedGraphicsPipeline mPipeline;
			lava::SharedPipelineLayout mLayout;
			lava::SharedDescriptorSet mCameraDescriptor;
			lava::InlineSubpass* mCurrentSubpass;

			std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> mAdvancedPipeline;

		private:
			virtual void
				renderSingleGameObject(const std::tuple<RenderComponent&, TransformComponent&> go) = 0;
		};
	}
}