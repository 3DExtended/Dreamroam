#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout (location = 0) in vec2 vUV;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec4 vPosition;
layout (location = 3) in vec4 mlightviewVertexPos;

layout (set = 1, binding = 0) uniform sampler2D uTexture;
layout (set = 2, binding = 1) uniform sampler2D shadowTexture;

layout(push_constant) uniform PushConsts {
	mat4x4 modelMatrix;
	mat4x4 normalMatrix;
} pu;

//Out:
layout (location = 0) out vec4 color;
layout (location = 1) out vec4 normal;
layout (location = 2) out vec4 fragPos;


float normpdf(in float x, in float sigma)
{
	return 0.39894*exp(-0.5*x*x/(sigma*sigma))/sigma;
}

const int kernelSize = 1;
const float bias = 0.0023;

void main() {
	color = vec4(texture(uTexture, vUV).rgb, 1);
	normal = vec4(vNormal,0);
	fragPos = vPosition;
}
