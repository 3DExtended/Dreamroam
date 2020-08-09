#pragma once
#include <RenderingSystem/Renders/RendererBase.hh>

#include <memory>

#include <lava/objects/Device.hh>
#include <lava/objects/PipelineLayout.hh>
#include <lava-extras/pipeline/ForwardRenderingPipeline.hh>
#include <lava/createinfos/GraphicsPipelineCreateInfo.hh>
#include <lava-extras/pipeline/ForwardRenderingPipeline.hh>
#include "AdvancedRenderingPipeline.hh"

namespace DCore {
	namespace Rendering {
		/// <summary>
		/// Factory for all different renderers.
		/// </summary>
		class GraphicsPipelineFactory
		{
		public:
			static inline std::shared_ptr<RendererBase>
				createRenderer_opaqueUntextured(
					lava::SharedDevice device,
					lava::SharedPipelineLayout plLayout,
					std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);

			static inline std::shared_ptr<RendererBase>
				createRenderer_opaqueTextured(
					lava::SharedDevice device,
					lava::SharedPipelineLayout plLayout,
					std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);

			static inline std::shared_ptr<RendererBase>
				createRenderer_transparentUntextured(
					lava::SharedDevice device,
					lava::SharedPipelineLayout plLayout,
					std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);

			static inline std::shared_ptr<RendererBase>
				createRenderer_transparentTextured(
					lava::SharedDevice device,
					lava::SharedPipelineLayout plLayout,
					std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);

			static inline std::shared_ptr<RendererBase>
				createRenderer_shadowMap(
					lava::SharedDevice device,
					lava::SharedPipelineLayout plLayout,
					std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);
		};
	}
}