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

float normpdf(in float x, in float sigma)
{
	return 0.39894*exp(-0.5*x*x/(sigma*sigma))/sigma;
}

void main() {
    color = texture(uTexture, vUV);
    color.a = 1.0;
    
	//todo move this into the pushconstants
	vec3 lightDirectionIn = normalize(vec3(1,1,.5));
	//vec3 R = reflect(lightDirectionIn, vNormal);

	float intensity = dot(normalize(vNormal), normalize(lightDirectionIn));

	
	float shade = 1.0;
	/*shade = intensity <= 0.8 ? 0.8 : shade;
	shade = intensity <= 0.15 ? 0.5 : shade;
	shade = intensity <= -0.3 ? 0.1 : shade;//*/

	vec3 lightFragmentPosition = mlightviewVertexPos.xyz;
	lightFragmentPosition.xy = lightFragmentPosition.xy * 0.5 + 0.5;
	vec2 texSize = vec2(textureSize(shadowTexture, 0));

	float shadowFactor = 0.0;
	float bias = 0.005;

	vec2 inc = 1.0 / textureSize(shadowTexture, 0);
	int counter = 0;
	int missedCounter = 0;
	vec2 originalUV = lightFragmentPosition.xy;

	float orgFragDepth = texture(shadowTexture, originalUV).r; 
	for(int row = -1; row <= 1; ++row)
	{
		for(int col = -1; col <= 1; ++col)
		{
			vec2 uvOffset = vec2(row, col) * inc;
			vec2 uv = lightFragmentPosition.xy + uvOffset;
			if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0){
				shadowFactor += lightFragmentPosition.z + bias < orgFragDepth ? 1.0 * (normpdf(row,1.0) * normpdf(col,1.0)) : 0.0;        
				continue;
			}

			float textDepth = texture(shadowTexture, uv).r;

			if (textDepth > 0){
				shadowFactor += lightFragmentPosition.z + bias < textDepth ? 1.0 * (normpdf(row,1.0) * normpdf(col,1.0)) : 0.0;        
				counter ++;
			}else {
				shadowFactor += lightFragmentPosition.z + bias < orgFragDepth ? 1.0 * (normpdf(row,1.0) * normpdf(col,1.0)) : 0.0;        
			}
		}    
	}

	color.rgb *= 1.0-shadowFactor; 
}
