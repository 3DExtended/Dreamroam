#pragma once

#include <lava/raii/ActiveRenderPass.hh>
#include <lava/objects/GraphicsPipeline.hh>
#include <ComponentBased/GameObject.hh>
#include "AdvancedRenderingPipeline.hh"

class GraphicsPipelineRenderer
{

public:
  explicit GraphicsPipelineRenderer(
      std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline>,
      lava::SharedGraphicsPipeline pipeline,
      lava::SharedPipelineLayout layout);

  virtual ~GraphicsPipelineRenderer(){};

  void prepareRendering(
      lava::InlineSubpass *sub, lava::SharedDescriptorSet cameraDescriptor);

  void renderGameObjects(const std::vector<std::shared_ptr<GameObject>> gos);

protected:
  lava::SharedGraphicsPipeline mPipeline;
  lava::SharedPipelineLayout mLayout;
  lava::SharedDescriptorSet mCameraDescriptor;
  lava::InlineSubpass *mCurrentSubpass;

  std::shared_ptr<lava::pipeline::AdvancedRenderingPipeline> mAdvancedPipeline;

private:
  virtual void
  renderSingleGameObject(
      std::shared_ptr<GameObject> go) = 0;
};
