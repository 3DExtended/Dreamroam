#include "DefaultRenderer.hh"

#include <RenderingSystem/PushConstants.hh>

#include "../RenderComponent.hh"

using namespace DCore::Rendering;

void DefaultRenderer::renderSingleGameObject(
    const std::tuple<RenderComponent&, TransformComponent&> go) {
    PushConstants pushConsts;
    auto& [renderComp, transform] = go;

    mCurrentSubpass->bindDescriptorSets(
        {mCameraDescriptor}, 0, vk::PipelineBindPoint::eGraphics, mLayout);

    glm::mat4 modelMatrixComplete = transform.getModelMatrix();
    pushConsts.modelMatrix = modelMatrixComplete;
    pushConsts.normalMatrix = glm::transpose(glm::inverse(modelMatrixComplete));
    mCurrentSubpass->pushConstantBlock(pushConsts);

    if (renderComp.geometryObj != nullptr) {
        renderComp.geometryObj->draw(*mCurrentSubpass);
    }
}