#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
#extension GL_GOOGLE_include_directive : enable
#include "fxaa.glsl"
#include "shadow.glsl"
#include "fog.glsl"

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

// TODO make this part of push constants..
const vec3 lightDirectionIn = normalize(vec3(0.5,1,-.5));

// TODO make this part of push constants...
const vec3 cameraPos = vec3(0);

void main() {
    vec4 color = texture(uColor, gl_FragCoord.xy).rgba;
    vec4 normal = texture(uNormal, gl_FragCoord.xy).rgba;
    vec4 position = texture(uPosition, gl_FragCoord.xy).rgba;
    float depth = texture(uDepth, gl_FragCoord.xy).r;

    if (specialization == 0){
        float diffuseFactor = max(dot(normalize(normal.xyz), normalize(lightDirectionIn)), 0.0) * calcShadowFactor(shadowTexture, position.xyz, pu.depthViewProj);
        fColor = vec3(color.xyz * (diffuseFactor * 0.7 + 0.3));
        fColor = applyFog(fColor, length(position.xyz-cameraPos), cameraPos-position.xyz, -lightDirectionIn, 0.00032);
    }
    else if (specialization == 1){
        float diffuseFactor = max(dot(normalize(normal.xyz), normalize(lightDirectionIn)), 0.0) * calcShadowFactor(shadowTexture, position.xyz, pu.depthViewProj);
        fColor = vec3(color.xyz * (diffuseFactor * 0.7 + 0.3));
    }
    // render color g buffer
    else if (specialization == 2){
        fColor = color.xyz;
    }
    // render normal g buffer
    else if (specialization == 3){
        fColor = normal.xyz;
    }
    // render position g buffer
    else if (specialization == 4){
        fColor = position.xyz;
    }
    // render position g buffer
    else if (specialization == 5){
        fColor = vec3(depth);
    }
    else if (specialization == 6){
        fColor = vec3(calcShadowFactor(shadowTexture, position.xyz, pu.depthViewProj));
    }
}
