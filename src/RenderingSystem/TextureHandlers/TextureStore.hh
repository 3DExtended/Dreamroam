#pragma once

#include <lava/objects/Device.hh>
#include <map>
#include <memory>
#include <string>
namespace DCore {
namespace Textures {
using namespace lava;
class Texture;

class TextureStore {
public:
    TextureStore(lava::SharedDevice device);

    TextureStore(lava::SharedDevice device,
                 std::vector<std::pair<std::string, std::string>>
                     imageTexturePathsAndNames);

    ~TextureStore();

    std::shared_ptr<Texture> getTextureWithName(std::string name) const;

    lava::SharedDescriptorSetLayout getTextureLayout() const;

private:
    void createAllTextures(
        lava::SharedDevice device,
        std::vector<std::pair<std::string, std::string>>& texturePathsAndNames);

    std::map<std::string, std::shared_ptr<Texture>> mTextures;

    lava::SharedDescriptorSetLayout mTextureLayout;
};
}  // namespace Textures
}  // namespace DCore