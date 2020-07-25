#include "DefaultRenderer.hh"
#include <RenderingSystem/PushConstants.hh>
#include <Components/RenderComponent.hh>

using namespace DCore::Components;

void DefaultRenderer::renderSingleGameObject(std::shared_ptr<GameObject> go)
{
	PushConstants pushConsts;

	auto renderComp = go->getComponent<RenderComponent>();

	mCurrentSubpass->bindDescriptorSets(
		{ mCameraDescriptor },
		0,
		vk::PipelineBindPoint::eGraphics,
		mLayout);

	glm::mat4 modelMatrixComplete = go->transform.getModelMatrix();
	pushConsts.modelMatrix = modelMatrixComplete;
	pushConsts.normalMatrix = glm::transpose(glm::inverse(modelMatrixComplete));
	mCurrentSubpass->pushConstantBlock(pushConsts);

	renderComp->geometryObj->draw(*mCurrentSubpass);
}