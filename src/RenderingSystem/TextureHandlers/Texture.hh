#pragma once

#include <lava/objects/DescriptorSet.hh>

namespace DCore {
namespace Textures {
class Texture {
public:
    Texture(lava::SharedDescriptorSet descriptorSet);

    lava::SharedDescriptorSet getDescriptorSet() { return mDescriptorSet; };

private:
    lava::SharedDescriptorSet mDescriptorSet;
};
}  // namespace Textures
}  // namespace DCore