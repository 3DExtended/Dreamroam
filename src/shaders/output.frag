#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
#extension GL_GOOGLE_include_directive : enable

#include "fxaa.glsl"

// deferred rendering
layout (binding = 0) uniform sampler2D uColor;
layout (binding = 1) uniform sampler2D uNormal;
layout (binding = 2) uniform sampler2D uPosition;
layout (binding = 3) uniform sampler2D uDepth;

// shadow map
layout (binding = 4) uniform sampler2D shadowTexture;

layout(push_constant) uniform PushConsts {
	mat4 depthViewProj;
    mat4x4 futureUseMat4;
	float futureUseFloat;
} pu;

// output to render
layout (location = 0) out vec3 fColor;

// constant that can be changed through specializations of the rendering pipeline
// default value for this is 0.
layout (constant_id = 0) const int specialization = 0;

void main() {
    vec3 color = vec3(0);
    vec3 normal = vec3(0);
    vec3 position = vec3(0);
    float depth = 0;

    if (specialization == 0) {
        fColor = fxaa(uColor, gl_FragCoord.xy).rgb;
    } 
    else if (specialization == 1) {
        fColor = texture(uColor, gl_FragCoord.xy).rgb;
    }
    else if (specialization == 2) {
        fColor = fxaa(uNormal, gl_FragCoord.xy).rgb;
    }
    else if (specialization == 3) {
        fColor = texture(uNormal, gl_FragCoord.xy).rgb;
    }
    else if (specialization == 4) {
        fColor = fxaa(uPosition, gl_FragCoord.xy).rgb;
    }
    else if (specialization == 5) {
        fColor = texture(uPosition, gl_FragCoord.xy).rgb;
    }
    else if (specialization == 6) {
        fColor = fxaa(uDepth, gl_FragCoord.xy).rgb;
    }
    else if (specialization == 7) {
        fColor = texture(uDepth, gl_FragCoord.xy).rgb;
    }
    else if (specialization == 8) {
        fColor = fxaa(shadowTexture, gl_FragCoord.xy).rgb;
    }
    else if (specialization == 9) {
        fColor = texture(shadowTexture, gl_FragCoord.xy).rgb;
    }
}
