#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout (location = 0) in vec4 vColor;
layout (location = 1) in vec3 vNormal;

layout (set = 1, binding = 1) uniform sampler2D shadowTexture;


//Out:
layout (location = 0) out vec4 fColor;

void main() {
    vec3 lightDirection = normalize(vec3(1,1,1));
    vec4 color;

    float halfLambert =
        (dot(lightDirection, vNormal) + 1.0) / 2.0;
    color.rgb = vColor.rgb * halfLambert;
    color.a = vColor.a;

    fColor = color;
}
