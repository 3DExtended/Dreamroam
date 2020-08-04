#include "UtilsLava.hh"

#include <iostream>

#include <lava/objects/ImageData.hh>

#define STB_IMAGE_IMPLEMENTATION
#include <extern/stb_image.hh>
#include <lava\src\lava\common\log.hh>

namespace UtilsLava
{
	lava::SharedImage
		loadCreateAndUploadImg(
			const std::string& filePath,
			lava::SharedDevice device,
			bool generateMipmaps)
	{
		int texWidth, texHeight, texChannels;

		unsigned char* pixels = stbi_load(
			filePath.c_str(),
			&texWidth,
			&texHeight,
			&texChannels,
			STBI_rgb_alpha);

		if (pixels == nullptr) {
			lava::log(lava::LogLevel::Error) << "Could not load image with title: '" << filePath << "'";
			assert(false);
		}

		auto imgData = lava::ImageData::createFromData(
			pixels,
			texWidth,
			texHeight,
			1, // depth
			vk::Format::eR8G8B8A8Srgb);

		if (!generateMipmaps)
		{
			imgData->disableMipmapGen();
		}
		//imgData->setMipLevels(1);

		lava::SharedImage img = imgData->uploadTo(device);
		img->changeLayout(vk::ImageLayout::eShaderReadOnlyOptimal);

		return img;
	}

	lava::SharedImage
		loadCreateAndUploadImgForTexture_default(
			const std::string& filePath,
			lava::SharedDevice device)
	{
		return loadCreateAndUploadImg(
			filePath,
			device,
			true // generate mipmaps
		);
	}
} // namespace UtilsLava