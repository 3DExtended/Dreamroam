#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout (location = 0) in vec2 vUV;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vPosition;

layout (set = 1, binding = 0) uniform sampler2D uTexture;
layout (set = 2, binding = 1) uniform sampler2D shadowTexture;

layout(push_constant) uniform PushConsts {
    mat4x4 modelMatrix;
    mat4x4 normalMatrix;
} pu;

//Out:
layout (location = 0) out vec4 color;

void main() {
    color = texture(uTexture, vUV);
    color.a = 1.0;
    
	vec4 shadowMap = texture(shadowTexture, vUV);
	if(shadowMap.r >= 0.002){
		color.rgb = vec3(1,0,0);
	}

	//todo move this into the pushconstants
	vec3 lightDirectionIn = normalize(vec3(1,1,.5));
	//vec3 R = reflect(lightDirectionIn, vNormal);

	float intensity = dot(normalize(vNormal), normalize(lightDirectionIn));

	
	float shade = 1.0;
	shade = intensity <= 0.8 ? 0.8 : shade;
	shade = intensity <= 0.15 ? 0.5 : shade;
	shade = intensity <= -0.3 ? 0.1 : shade;

	color.rgb = (color.rgb * shade);
	//color.rgb = vNormal.rgb;

	
}
