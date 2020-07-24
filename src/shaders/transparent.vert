#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(location=0) in vec3 aPosition;
layout(location=1) in vec4 aColor;
layout(location=2) in vec3 aNormal;

layout(set = 0, binding = 0) uniform CameraMatrices {
    mat4 view;
    mat4 proj;
} cams;

layout (location = 0) out vec4 vColor;
layout (location = 1) out vec3 vNormal;

layout(push_constant) uniform PushConsts {
    mat4x4 modelMatrix;
    float alpha;
} pu;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main() {
    vec4 worldPos = pu.modelMatrix * vec4(aPosition, 1.0);

    gl_Position = cams.proj
                * cams.view
                * worldPos;

    vColor = aColor;
    vNormal = aNormal;
}
