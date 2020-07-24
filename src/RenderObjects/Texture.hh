#pragma once

#include <lava/objects/DescriptorSet.hh>

class Texture
{
public:
  Texture(lava::SharedDescriptorSet descriptorSet);

  lava::SharedDescriptorSet getDescriptorSet() { return mDescriptorSet; };

private:
  lava::SharedDescriptorSet mDescriptorSet;
};
