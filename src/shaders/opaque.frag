#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout (location = 0) in vec3 vColor;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vPosition;

layout (set = 1, binding = 1) uniform sampler2D shadowTexture;

//Out:
layout (location = 0) out vec4 fColor;

void main() {
    fColor = vec4(vColor,1.0);
    fColor = vec4(1,0,0,1);
    // Move light vector to PushConstants
    /*vec3 L = normalize(vec3(50,100,25) - vPosition);
    vec3 Idiff = fColor.rgb * max(dot(vNormal,L), 0.0);
    Idiff = clamp(Idiff, 0.0, 1.0);
	fColor.rgb = Idiff.rgb + 0.05 * fColor.rgb;*/
}
