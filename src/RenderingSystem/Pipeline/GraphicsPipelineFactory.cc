#include "GraphicsPipelineFactory.hh"

#include <lava-extras/geometry/Geometry.hh>
#include <lava-extras/pack/pack.hh>

#include "../PushConstants.hh"
#include "../Renders/DefaultRenderer.hh"
#include "../Renders/DefaultTexturedRenderer.hh"

using namespace DCore::Rendering;

inline std::shared_ptr<RendererBase>
GraphicsPipelineFactory::createRenderer_opaqueUntextured(
    lava::SharedDevice device, lava::SharedPipelineLayout plLayout,
    std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline) {
    auto ci = lava::GraphicsPipelineCreateInfo::defaults();
    ci.setLayout(plLayout);

    ci.depthStencilState.depthTestEnable = true;
    ci.depthStencilState.depthWriteEnable = true;
    ci.rasterizationState.frontFace = vk::FrontFace::eClockwise;
    ci.addStage(lava::pack::shader(device, "shaders/opaque_vert.spv"));
    ci.addStage(lava::pack::shader(device, "shaders/opaque_frag.spv"));

    ci.vertexInputState.addAttribute(&VertexAttributes::position, 0);
    ci.vertexInputState.addAttribute(&VertexAttributes::color, 1);
    ci.vertexInputState.addAttribute(&VertexAttributes::normal, 2);
    auto graphicsPipeline = pipeline->forwardPass()->createPipeline(1, ci);

    auto renderer =
        std::make_shared<DefaultRenderer>(pipeline, graphicsPipeline, plLayout);

    return renderer;
}

inline std::shared_ptr<RendererBase>
GraphicsPipelineFactory::createRenderer_opaqueTextured(
    lava::SharedDevice device, lava::SharedPipelineLayout plLayout,
    std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline) {
    auto ci = lava::GraphicsPipelineCreateInfo::defaults();
    ci.setLayout(plLayout);

    ci.depthStencilState.depthTestEnable = true;
    ci.depthStencilState.depthCompareOp = vk::CompareOp::eLess;
    ci.depthStencilState.depthWriteEnable = true;
    ci.rasterizationState.frontFace = vk::FrontFace::eClockwise;
    // ci.rasterizationState.cullMode = vk::CullModeFlagBits::eNone;

    ci.addStage(
        lava::pack::shader(device, "shaders/opaqueTexturedSimple_vert.spv"));
    ci.addStage(
        lava::pack::shader(device, "shaders/opaqueTexturedSimple_frag.spv"));

    ci.vertexInputState.addAttribute(&VertexAttributes::position, 0);
    ci.vertexInputState.addAttribute(&VertexAttributes::texCoord, 1);
    ci.vertexInputState.addAttribute(&VertexAttributes::normal, 2);

    auto graphicsPipeline = pipeline->forwardPass()->createPipeline(1, ci);

    auto renderer = std::make_shared<DefaultTexturedRenderer>(
        pipeline, graphicsPipeline, plLayout);

    return renderer;
}

inline std::shared_ptr<RendererBase>
GraphicsPipelineFactory::createRenderer_transparentUntextured(
    lava::SharedDevice device, lava::SharedPipelineLayout plLayout,
    std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline) {
    auto ci = lava::GraphicsPipelineCreateInfo::defaults();
    ci.setLayout(plLayout);

    ci.depthStencilState.depthTestEnable = true;
    ci.depthStencilState.depthWriteEnable = true;
    ci.rasterizationState.cullMode = vk::CullModeFlagBits::eNone;

    ci.addStage(lava::pack::shader(device, "shaders/transparent_vert.spv"));
    ci.addStage(lava::pack::shader(device, "shaders/transparent_frag.spv"));

    ci.vertexInputState.addAttribute(&VertexAttributes::position, 0);
    ci.vertexInputState.addAttribute(&VertexAttributes::color, 1);
    ci.vertexInputState.addAttribute(&VertexAttributes::normal, 2);
    ci.colorBlendState.clear();

    VkPipelineColorBlendAttachmentState blendAttachementState = {
        true,
        VK_BLEND_FACTOR_SRC_ALPHA,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        VK_BLEND_OP_ADD,
        VK_BLEND_FACTOR_SRC_ALPHA,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        VK_BLEND_OP_ADD,
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT};

    ci.colorBlendState.add(blendAttachementState);

    auto graphicsPipeline = pipeline->forwardPass()->createPipeline(1, ci);

    auto renderer =
        std::make_shared<DefaultRenderer>(pipeline, graphicsPipeline, plLayout);

    return renderer;
}

inline std::shared_ptr<RendererBase>
GraphicsPipelineFactory::createRenderer_transparentTextured(
    lava::SharedDevice device, lava::SharedPipelineLayout plLayout,
    std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline) {
    auto ci = lava::GraphicsPipelineCreateInfo::defaults();
    ci.setLayout(plLayout);

    ci.depthStencilState.depthTestEnable = true;
    ci.depthStencilState.depthWriteEnable = true;
    ci.rasterizationState.cullMode = vk::CullModeFlagBits::eNone;

    ci.addStage(lava::pack::shader(
        device, "shaders/transparentTexturedSimple_vert.spv"));
    ci.addStage(lava::pack::shader(
        device, "shaders/transparentTexturedSimple_frag.spv"));

    ci.vertexInputState.addAttribute(&VertexAttributes::position, 0);
    ci.vertexInputState.addAttribute(&VertexAttributes::texCoord, 1);
    ci.vertexInputState.addAttribute(&VertexAttributes::normal, 2);

    ci.colorBlendState.clear();

    VkPipelineColorBlendAttachmentState blendAttachementState = {
        true,
        VK_BLEND_FACTOR_SRC_ALPHA,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        VK_BLEND_OP_ADD,
        VK_BLEND_FACTOR_SRC_ALPHA,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        VK_BLEND_OP_ADD,
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT};

    ci.colorBlendState.add(blendAttachementState);

    auto graphicsPipeline = pipeline->forwardPass()->createPipeline(1, ci);
    auto renderer = std::make_shared<DefaultTexturedRenderer>(
        pipeline, graphicsPipeline, plLayout);

    return renderer;
}

inline std::shared_ptr<RendererBase>
GraphicsPipelineFactory::createRenderer_shadowMap(
    lava::SharedDevice device, lava::SharedPipelineLayout plLayout,
    std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> pipeline) {
    auto ci = lava::GraphicsPipelineCreateInfo::defaults();
    ci.setLayout(plLayout);

    ci.depthStencilState.depthTestEnable = true;
    ci.depthStencilState.depthWriteEnable = true;
    ci.rasterizationState.cullMode = vk::CullModeFlagBits::eNone;

    ci.addStage(lava::pack::shader(device, "shaders/shadowMap_vert.spv"));
    ci.addStage(lava::pack::shader(device, "shaders/shadowMap_frag.spv"));

    ci.vertexInputState.addAttribute(&VertexAttributes::position, 0);

    ci.colorBlendState.clear();

    VkPipelineColorBlendAttachmentState blendAttachementState = {
        true,
        VK_BLEND_FACTOR_SRC_ALPHA,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        VK_BLEND_OP_ADD,
        VK_BLEND_FACTOR_SRC_ALPHA,
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        VK_BLEND_OP_ADD,
        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT};

    ci.colorBlendState.add(blendAttachementState);

    auto graphicsPipeline = pipeline->prePass()->createPipeline(0, ci);
    auto renderer =
        std::make_shared<DefaultRenderer>(pipeline, graphicsPipeline, plLayout);

    return renderer;
}