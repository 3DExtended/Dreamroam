#pragma once

#include <glm/mat4x4.hpp>
#include <lava/createinfos/PipelineVertexInputStateCreateInfo.hh>

namespace DCore {
	namespace Rendering {
		struct PushConstants
		{
			glm::mat4 modelMatrix;
			glm::mat4 normalMatrix;
			float alpha = 1.0;
		};

		struct CameraDataPrePass {
			glm::mat4 view;
			glm::mat4 proj;
		};

		struct CameraDataForwardPass {
			glm::mat4 view;
			glm::mat4 proj;
			glm::mat4 depthViewProj;
		};

		struct VertexAttributes
		{
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 tangent;
			glm::vec2 texCoord;
			glm::vec4 color = glm::vec4(1, 0, 0, 1);

			static void putAttributes(lava::PipelineVertexInputStateCreateInfo& info)
			{
				info.binding(0,                           //
					&VertexAttributes::position, //
					&VertexAttributes::normal,   //
					&VertexAttributes::tangent,  //
					&VertexAttributes::texCoord, //
					&VertexAttributes::color);
			};
		};
	}
}