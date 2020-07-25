#include "DefaultTexturedRenderer.hh"
#include "PushConstants.hh"
#include <Components/RenderComponent.hh>
#include <ComponentBased/GameObject.hh>
#include <RenderObjects/Texture.hh>

#include <lava/objects/DescriptorSet.hh>

using namespace DCore::Components;
void DefaultTexturedRenderer::renderSingleGameObject(std::shared_ptr<GameObject> go)
{
	auto renderComp = go->getComponent<RenderComponent>();

	assert(renderComp->textureObj != nullptr);
	auto textureDescriptor =
		renderComp
		->textureObj
		->getDescriptorSet();

	mCurrentSubpass->bindDescriptorSets(
		{
			mCameraDescriptor,
			textureDescriptor,
			mAdvancedPipeline->mForwardDescriptor
		},
		0,
		vk::PipelineBindPoint::eGraphics,
		mLayout);

	glm::mat4 modelMatrixComplete =
		go->transform.getModelMatrix();

	PushConstants pushConsts;

	pushConsts.modelMatrix = modelMatrixComplete;
	pushConsts.normalMatrix = glm::transpose(glm::inverse(modelMatrixComplete));
	pushConsts.alpha = renderComp->alpha;

	mCurrentSubpass->pushConstantBlock(pushConsts);

	renderComp->geometryObj->draw(*mCurrentSubpass);
}