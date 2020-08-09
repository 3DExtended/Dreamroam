#pragma once

#include <memory>
#include <map>
#include <string>
#include <lava/objects/Device.hh>

#include "RenderComponent.hh"
#include <ComponentBased/Systems/SystemBase.hh>
#include <ComponentBased/BaseComponents.hh>
#include <RenderingSystem/Pipeline/GraphicsPipelineRenderer.hh>
#include <RenderingSystem/RenderingSystemBase.hh>

namespace DCore {
	namespace Rendering {
		using namespace DCore::ComponentSystem;
		class RenderingSystem : public RenderingSystemBase
		{
		public:
			RenderingSystem(
				lava::SharedDevice device,
				lava::SharedDescriptorSetLayout textureLayout,
				std::shared_ptr<lava::features::GlfwOutput> glfwOutput,
				std::shared_ptr<lava::features::GlfwWindow> glfwWindow);

			~RenderingSystem() = default;

			void Render(std::vector<std::tuple<RenderComponent&, TransformComponent&>> entities) override;

			void Resize(int width, int height) override;

			lava::camera::SharedGenericCamera getCamera() override {
				return mPipeline->getCamera();
			}

		private:
			lava::SharedDevice mDevice;

			std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> mPipeline;
			lava::SharedPipelineLayout mPlLayout;

			lava::SharedBuffer mViewProjBufferPrePass;
			lava::SharedBuffer mViewProjBufferForwardPass;
			lava::SharedDescriptorSet mViewProjDescriptorForward;
			lava::SharedDescriptorSet mViewProjDescriptorPre;

			std::shared_ptr<lava::features::GlfwOutput> mGlfwOutput;
			std::shared_ptr<lava::features::Validation> mValidation;
			std::shared_ptr<lava::features::GlfwWindow> mWindow;

			lava::SharedDescriptorSetLayout mViewProjDescriptorSetLayoutPrePass;
			lava::SharedDescriptorSetLayout mViewProjDescriptorSetLayoutForwarPass;

			// Pipelines
			std::shared_ptr<GraphicsPipelineRenderer> mOpaqueUntextured;
			std::shared_ptr<GraphicsPipelineRenderer> mOpaqueTextured;
			std::shared_ptr<GraphicsPipelineRenderer> mTransparendUntextured;
			std::shared_ptr<GraphicsPipelineRenderer> mTransparendTextured;
			std::shared_ptr<GraphicsPipelineRenderer> mShadowMap;

			std::vector<lava::SharedFramebuffer> companionWindowFBO;

		private:
			void getFrustumCorners(std::vector<glm::vec4>& corners, glm::mat4 projection);
			std::tuple<glm::mat4, glm::mat4> rotateCameraFrustrumCornersToLightSpace(glm::vec3 forward, glm::vec3 camPosition, glm::vec3 upDirection);
			void setupPipeline(const lava::SharedDescriptorSetLayout textureLayout);
		};
	}
}