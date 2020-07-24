#pragma once
#include <RenderingSystem/GraphicsPipelineRenderer.hh>

#include <memory>

#include <lava/objects/Device.hh>
#include <lava/objects/PipelineLayout.hh>
#include <lava-extras/pipeline/ForwardRenderingPipeline.hh>
#include <lava/createinfos/GraphicsPipelineCreateInfo.hh>
#include <lava-extras/pipeline/ForwardRenderingPipeline.hh>
#include "RenderingSystem/AdvancedRenderingPipeline.hh"

class GraphicsPipelineFactory
{
  public:
    static std::shared_ptr<GraphicsPipelineRenderer>
    createRenderer_opaqueUntextured(
        lava::SharedDevice device,
        lava::SharedPipelineLayout plLayout,
        std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);

    static std::shared_ptr<GraphicsPipelineRenderer>
    createRenderer_opaqueTextured(
        lava::SharedDevice device,
        lava::SharedPipelineLayout plLayout,
        std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);

    static std::shared_ptr<GraphicsPipelineRenderer>
    createRenderer_transparentUntextured(
        lava::SharedDevice device,
        lava::SharedPipelineLayout plLayout,
        std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);

    static std::shared_ptr<GraphicsPipelineRenderer>
    createRenderer_transparentTextured(
        lava::SharedDevice device,
        lava::SharedPipelineLayout plLayout,
        std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);

    static std::shared_ptr<GraphicsPipelineRenderer>
    createRenderer_shadowMap(
        lava::SharedDevice device, 
        lava::SharedPipelineLayout plLayout, 
        std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline);
};
