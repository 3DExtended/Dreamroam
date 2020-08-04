#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout (location = 0) in vec2 vUV;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vPosition;

layout (set = 1, binding = 0) uniform sampler2D uTexture;
layout (set = 1, binding = 1) uniform sampler2D shadowTexture;

layout(push_constant) uniform PushConsts {
    mat4x4 modelMatrix;
    mat4x4 normalMatrix;
    float alpha;
} pu;


//Out:
layout (location = 0) out vec4 fColor;

void main() {
    vec4 fColor = texture(uTexture, vUV);

    /*vec3 L = normalize(vec3(50,100,25) - vPosition);
    vec3 Idiff = fColor.rgb * max(dot(vNormal,L), 0.0);
    Idiff = clamp(Idiff, 0.0, 1.0);
    fColor.rgb = Idiff.rgb + 0.05 * fColor.rgb;
    fColor.a = pu.alpha;*/

    fColor.rgb = fColor.rgb;
    fColor.a = pu.alpha;

    /*vec3 lightDirection = normalize(vec3(1,1,1));
    vec4 color;

    float halfLambert =
        (dot(lightDirection, vNormal) + 1.0) / 2.0;
    color.rgb = surfaceColor.rgb * halfLambert;
    color.a = surfaceColor.a;

    fColor = color;*/

}
