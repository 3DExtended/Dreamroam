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

const float bias = 0.0023;

void main() {
    vec4 color = vec4(0);
    vec4 normal = vec4(0);
    vec4 position = vec4(0);
    float depth = 0;

    // default case is to use fxaa. however, for debugging shaders it is more feasible to view at the raw inputs.
    if (specialization == 0){
        color = fxaa(uColor, gl_FragCoord.xy).rgba;
        normal = fxaa(uNormal, gl_FragCoord.xy).rgba;
        position = fxaa(uPosition, gl_FragCoord.xy).rgba;
        depth = fxaa(uDepth, gl_FragCoord.xy).r;
    }else{
        color = texture(uColor, gl_FragCoord.xy).rgba;
        normal = texture(uNormal, gl_FragCoord.xy).rgba;
        position = texture(uPosition, gl_FragCoord.xy).rgba;
        depth = texture(uDepth, gl_FragCoord.xy).r;
    }

    // calculate fragments/pixel (since we are in deferred rendering we know, every fragment will be displayed as pixel on the screen) position on the shadow map
    vec3 fragmentPositionOnShadowmap = (pu.depthViewProj * vec4(position.xyz,1)).xyz;
	fragmentPositionOnShadowmap.xy = fragmentPositionOnShadowmap.xy * 0.5 + 0.5;
    float textDepthOfFragmentOnShadowmap = texture(shadowTexture, fragmentPositionOnShadowmap.xy).r;

    // shadow factor is based on comparison of textDepthOfFragmentOnShadowmap and fragmentPositionOnShadowmap.z
    float shadowFactor = fragmentPositionOnShadowmap.z - bias > textDepthOfFragmentOnShadowmap ? 1.0 : 0.0;        

    if (specialization == 0){
        fColor = vec3(shadowFactor,shadowFactor,shadowFactor);
    }
    else if (specialization == 1){
        fColor = fragmentPositionOnShadowmap.xyz;
    }
    else if (specialization == 2){
        fColor = vec3(1-fragmentPositionOnShadowmap.z - bias,0,0); // broken
    }
    else if (specialization == 3){
        fColor = vec3(textDepthOfFragmentOnShadowmap,0,0); // seems to be correct
    }
    else if (specialization == 4){
        fColor = vec3(fragmentPositionOnShadowmap.xy, 0); // seems to be correct
    }
    else if (specialization == 5){
        fColor = texture(shadowTexture, fragmentPositionOnShadowmap.xy).rgb; // seems to be correct
    }
    else if (specialization == 6){
        fColor = texture(shadowTexture, gl_FragCoord.xy * 4.0).rgb;
    }
}
