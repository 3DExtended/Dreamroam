#pragma once

#include <ComponentBased/BaseComponents.hh>
#include <RenderingSystem/Pipeline/AdvancedRenderingPipeline.hh>
#include <entt/entt.hpp>
#include <lava/objects/GraphicsPipeline.hh>
#include <lava/raii/ActiveRenderPass.hh>

#include "../RenderComponent.hh"

namespace DCore {
namespace Rendering {
using namespace DCore::ComponentSystem;

class RendererBase {
public:
    explicit RendererBase(
        std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline>,
        lava::SharedGraphicsPipeline pipeline,
        lava::SharedPipelineLayout layout);

    virtual ~RendererBase(){};

    void prepareRendering(lava::InlineSubpass* sub,
                          lava::SharedDescriptorSet cameraDescriptor);

    void renderGameObjects(
        const std::vector<std::tuple<RenderComponent&, TransformComponent&>>&
            gos);

protected:
    lava::SharedGraphicsPipeline mPipeline;
    lava::SharedPipelineLayout mLayout;
    lava::SharedDescriptorSet mCameraDescriptor;
    lava::InlineSubpass* mCurrentSubpass;

    std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline>
        mAdvancedPipeline;

private:
    virtual void renderSingleGameObject(
        const std::tuple<RenderComponent&, TransformComponent&> go) = 0;
};
}  // namespace Rendering
}  // namespace DCore