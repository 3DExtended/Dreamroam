float normpdf(in float x, in float sigma)
{
	return 0.39894*exp(-0.5*x*x/(sigma*sigma))/sigma;
}

// shadow mapping settings
const float bias = 0.0023;
const int shadowMapKernelSize = 1;
const float usedShadowPixels = shadowMapKernelSize * 2 + 1;

float calcShadowFactor(sampler2D shadowTexture, vec3 fragmentWorldPos, mat4x4 depthViewProj){
   	vec2 inc = 1.0 / textureSize(shadowTexture, 0);

    // calculate fragments/pixel (since we are in deferred rendering we know, every fragment will be displayed as pixel on the screen) position on the shadow map
    vec3 fragmentPositionOnShadowmap = (depthViewProj * vec4(fragmentWorldPos.xyz,1)).xyz;
	fragmentPositionOnShadowmap.xy = fragmentPositionOnShadowmap.xy * 0.5 + 0.5;

    float shadowFactor = 0.0f;

    for(int row = -shadowMapKernelSize; row <= shadowMapKernelSize; ++row)
	{
		for(int col = -shadowMapKernelSize; col <= shadowMapKernelSize; ++col)
		{
			vec2 uvOffset = vec2(row, col) * inc;
			float rowColShadowEffectWeight = 1.0;
			float textDepthOfFragmentOnShadowmap = texture(shadowTexture, fragmentPositionOnShadowmap.xy + uvOffset).r;
            
            // shadow factor is based on comparison of textDepthOfFragmentOnShadowmap and fragmentPositionOnShadowmap.z
			shadowFactor += fragmentPositionOnShadowmap.z + bias < textDepthOfFragmentOnShadowmap ? 1.0 * rowColShadowEffectWeight : 0.0;        
		}    
	}

    return shadowFactor = 1.0-(shadowFactor / usedShadowPixels);
}