#include <Utils/UtilsLava.hh>
#include <GlobalSettings.hh>
#include "Texture.hh"
#include "TextureStore.hh"

#include <utility>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <glm/vec4.hpp>
#include <lava/common/vulkan.hh>
#include <lava/createinfos/Sampler.hh>
#include <lava/createinfos/DescriptorSetLayoutCreateInfo.hh>
#include <lava/objects/DescriptorSet.hh>
#include <lava/objects/DescriptorSetLayout.hh>
#include <lava/objects/Image.hh>
#include <lava/objects/ImageData.hh>
#include <lava/common/GlLikeFormats.hh>
#include <lava/objects/Buffer.hh>
#include <lava/createinfos/Buffers.hh>

using namespace DCore::Textures;

TextureStore::TextureStore(lava::SharedDevice device) : TextureStore(device, std::vector<std::pair<std::string, std::string>>(0))
{
}

std::shared_ptr<Texture>
TextureStore::getTextureWithName(
	std::string name)
	const
{
	return mTextures.at(name);
}

lava::SharedDescriptorSetLayout
TextureStore::getTextureLayout()
const
{
	return mTextureLayout;
}

TextureStore::TextureStore(
	lava::SharedDevice device,
	std::vector<std::pair<std::string, std::string>> imageTexturePathsAndNames)
{
	;

	createAllTextures(
		device,
		imageTexturePathsAndNames);
}

TextureStore::~TextureStore()
{
}

void TextureStore::createAllTextures(
	lava::SharedDevice device,
	std::vector<std::pair<std::string, std::string>>& texturePathsAndNames)
{
	// Currently each descriptor set has either an image texture or a uniform
	// texel buffer texture. Having both at once is not supported currently.

	auto texlayoutinfo = lava::DescriptorSetLayoutCreateInfo{};

	texlayoutinfo.addCombinedImageSampler(
		vk::ShaderStageFlagBits::eFragment);

	texlayoutinfo.addBinding(
		vk::DescriptorType::eCombinedImageSampler);

	/*texlayoutinfo.addCombinedImageSampler(
		vk::ShaderStageFlagBits::eFragment);

	texlayoutinfo.addBinding(vk::DescriptorType::eCombinedImageSampler,
		vk::ShaderStageFlagBits::eFragment, 1);*/

	size_t poolSize = texturePathsAndNames.size();
	mTextureLayout = device->createDescriptorSetLayout(
		texlayoutinfo,
		poolSize + 1); // since we need one additional for shadow mapping

	for (auto pathAndName : texturePathsAndNames)
	{
		auto filePath = pathAndName.first;
		lava::SharedImage img =
			UtilsLava::loadCreateAndUploadImgForTexture_default(
				filePath,
				device);

		auto samplerCreateInfo = lava::SamplerCreateInfo();
		auto sampler = device->createSampler(samplerCreateInfo);

		auto ds = mTextureLayout->createDescriptorSet();
		ds->writeCombinedImageSampler(
			{ sampler, img->createView() },
			0 // binding
		);

		mTextures[pathAndName.second] = std::make_shared<Texture>(ds);
	}
}