#include "DefaultTexturedRenderer.hh"

#include <ComponentBased/Entity.hh>
#include <lava/objects/DescriptorSet.hh>

#include "../PushConstants.hh"
#include "../RenderComponent.hh"
#include "../TextureHandlers/Texture.hh"

using namespace DCore::ComponentSystem;
using namespace DCore::Rendering;
void DefaultTexturedRenderer::renderSingleGameObject(
    const std::tuple<RenderComponent&, TransformComponent&> go) {
    auto& [renderComp, transform] = go;

    assert(renderComp.textureObj != nullptr);
    auto textureDescriptor = renderComp.textureObj->getDescriptorSet();

    mCurrentSubpass->bindDescriptorSets({mCameraDescriptor, textureDescriptor,
                                         mAdvancedPipeline->mForwardDescriptor},
                                        0, vk::PipelineBindPoint::eGraphics,
                                        mLayout);

    glm::mat4 modelMatrixComplete = transform.getModelMatrix();

    PushConstants pushConsts;

    pushConsts.modelMatrix = modelMatrixComplete;
    pushConsts.normalMatrix = glm::transpose(glm::inverse(modelMatrixComplete));
    pushConsts.alpha = renderComp.alpha;

    mCurrentSubpass->pushConstantBlock(pushConsts);

    renderComp.geometryObj->draw(*mCurrentSubpass);
}