/*
* This code is inspired by https://iquilezles.org/www/articles/fog/fog.htm and modified.
*/

// fog settings
const vec3 blueSkyColor = vec3(0, 0.8, 1) ;

const float fogDistanceBias = 0.00032;

vec3 applyFog( in vec3  rgb,      // original color of the pixel
               in float distance, // camera to point distance
               in vec3  rayDir,   // camera to point vector
               in vec3  sunDir,   // sun light direction
			   in float bias)
{
	// TODO: we could mix a yellow tint into this color based on the sunAmount like presented here:
    // float sunAmount = max( dot( rayDir, sunDir ), 0.0 ) * 0.01;
	// https://iquilezles.org/www/articles/fog/fog.htm
	vec3  fogColor  = blueSkyColor;
    
	float fogAmount = 1.0 - exp( -distance*bias );
    return mix( rgb, fogColor, fogAmount );
}

vec3 applyFog( in vec3  rgb,      // original color of the pixel
               in float distance, // camera to point distance
               in vec3  rayDir,   // camera to point vector
               in vec3  sunDir)   // sun light direction
{
	return applyFog(rgb, distance, rayDir, sunDir, fogDistanceBias);
}