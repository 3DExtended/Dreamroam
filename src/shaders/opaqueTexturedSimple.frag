#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout (location = 0) in vec2 vUV;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vPosition;
layout (location = 3) in vec4 mlightviewVertexPos;

layout (set = 1, binding = 0) uniform sampler2D uTexture;
layout (set = 2, binding = 1) uniform sampler2D shadowTexture;

layout(push_constant) uniform PushConsts {
    mat4x4 modelMatrix;
    mat4x4 normalMatrix;
} pu;

//Out:
layout (location = 0) out vec4 color;


float shadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowTexture, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth - 0.2 >= closestDepth  ? 1.0 : 0.0;

    return shadow;
}  

void main() {
    color = texture(uTexture, vUV);
    color.a = 1.0;
    
	// vec4 shadowMap = texture(shadowTexture, vUV);
	// if(shadowMap.r >= 0.002){
	// 	color.rgb = vec3(shadowMap.r,shadowMap.g,shadowMap.b);
	// }

	//todo move this into the pushconstants
	vec3 lightDirectionIn = normalize(vec3(1,1,.5));
	//vec3 R = reflect(lightDirectionIn, vNormal);

	float intensity = dot(normalize(vNormal), normalize(lightDirectionIn));

	
	float shade = 1.0;
	/* shade = intensity <= 0.8 ? 0.8 : shade;
	shade = intensity <= 0.15 ? 0.5 : shade;
	shade = intensity <= -0.3 ? 0.1 : shade;*/ 

	color.rgb = (color.rgb * shadowCalculation(mlightviewVertexPos));

	// if ( < 0.5){
	// 	color.rgb = (color.rgb * shade);
	// }
	vec3 scaledShit = mlightviewVertexPos.xyz * mlightviewVertexPos.w;
	scaledShit = scaledShit * 0.5 + 0.5;
	// color.rgb = scaledShit;
	float closestDepth = texture(shadowTexture, scaledShit.xy).r; 
	color.rgb = vec3(closestDepth);
}

