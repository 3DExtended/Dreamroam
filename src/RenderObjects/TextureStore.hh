#pragma once

#include <memory>
#include <map>
#include <string>

#include <lava/objects/Device.hh>

class Texture;

class TextureStore
{

  public:
    TextureStore(
        lava::SharedDevice device);

    TextureStore(
        lava::SharedDevice device,
        std::vector<std::pair<std::string, std::string>> imageTexturePathsAndNames);

    ~TextureStore();

    inline std::shared_ptr<Texture>
    getTextureWithName(
        std::string name)
        const;

    inline lava::SharedDescriptorSetLayout
    getTextureLayout()
        const;

  private:
    void
    createAllTextures(
        lava::SharedDevice device,
        std::vector<std::pair<std::string, std::string>> &texturePathsAndNames);

    std::map<std::string, std::shared_ptr<Texture>> mTextures;

    lava::SharedDescriptorSetLayout mTextureLayout;
};

inline std::shared_ptr<Texture>
TextureStore::getTextureWithName(
    std::string name)
    const
{

    return mTextures.at(name);
}

inline lava::SharedDescriptorSetLayout
TextureStore::getTextureLayout()
    const
{

    return mTextureLayout;
}
