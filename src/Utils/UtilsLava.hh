#pragma once

/**

  Partially taken from the Vulkan Cookbook:
  https://github.com/PacktPublishing/Vulkan-Cookbook

  which is licensed under MIT License:

MIT License

Copyright (c) 2017 Packt

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

  */

#include <lava/objects/Device.hh>
#include <lava/objects/Image.hh>
#include <lava/common/vulkan.hh>

namespace UtilsLava
{
	lava::SharedImage
		loadCreateAndUploadImg(
			std::string filePath,
			lava::SharedDevice device,
			bool generateMipmaps);

	lava::SharedImage
		loadCreateAndUploadImgForTexture_default(
			std::string filePath,
			lava::SharedDevice device);

	bool createBuffer(
		VkDevice logical_device,
		VkDeviceSize size,
		VkBufferUsageFlags usage,
		VkBuffer& buffer);
} // namespace UtilsLava