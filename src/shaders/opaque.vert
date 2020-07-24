#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout(location=0) in vec3 aPosition;
layout(location=1) in vec4 aColor;
layout(location=2) in vec3 aNormal;

layout(set = 0, binding = 0) uniform CameraMatrices {
    mat4 view;
    mat4 proj;
} cams;

layout(push_constant) uniform PushConsts {
    mat4x4 modelMatrix;
    mat4x4 normalMatrix;
    float alpha;
} pu;

//Out:
layout (location = 0) out vec3 vColor;
layout (location = 1) out vec3 vNormal;
layout (location = 2) out vec3 vPosition;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main() {
    //mat4 normalMatrix = transpose(inverse(pu.modelMatrix));
    vPosition = aPosition;
	vNormal = (pu.normalMatrix * vec4(aNormal,0.0)).xyz;

    vec4 worldPos = pu.modelMatrix * vec4(aPosition, 1.0);
    gl_Position = cams.proj
                * cams.view
                * worldPos;
                //* vec4(aPosition * 0.2 + vec3(0,0.75,-1.5), 1.0);
    vColor = vec3(aColor);
}
