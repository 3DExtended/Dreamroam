#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout(location=0) in vec3 aPosition;

layout(set = 0, binding = 0) uniform CameraMatrices {
    mat4 view;
    mat4 proj;
} cams;

layout(push_constant) uniform PushConsts {
    mat4x4 modelMatrix;
    mat4x4 normalMatrix;
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
}
