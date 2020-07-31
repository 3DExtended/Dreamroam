#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout(location=0) in vec3 aPosition;
layout(location=1) in vec2 aUV;
layout(location=2) in vec3 aNormal;

layout(set = 0, binding = 0) uniform CameraMatrices {
    mat4 view;
    mat4 proj;
    mat4 depthViewProj;
} cams;

layout(push_constant) uniform PushConsts {
    mat4x4 modelMatrix;
    mat4x4 normalMatrix;
    float alpha;
} pu;

//Out:
layout (location = 0) out vec2 vUV;
layout (location = 1) out vec3 vNormal;
layout (location = 2) out vec3 vPosition;
layout (location = 3) out vec4 mlightviewVertexPos;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main() {
    vUV = aUV;
    vPosition = aPosition;
	vNormal = (pu.normalMatrix * vec4(aNormal,1.0)).xyz;

    vec4 worldPos = pu.modelMatrix * vec4(aPosition, 1.0);

	vec4 pos = cams.proj
                * cams.view
                * worldPos;
    gl_Position = pos;

    mlightviewVertexPos = cams.depthViewProj * worldPos;
}
