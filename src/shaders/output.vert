#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable


const vec2 verts[] = {
    vec2(-1.0, -1.0),
    vec2(-1.0,  3.0),
    vec2( 3.0, -1.0)
};

void main() {
    gl_Position = vec4(verts[gl_VertexIndex], 0.0, 1.0);
}

