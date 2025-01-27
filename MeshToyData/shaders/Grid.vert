#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

layout (std140) uniform Matrices
{
    mat4 Projection;
    mat4 View;
};

out vec2 TexCoords;
out vec3 WorldPos;

void main()
{
    TexCoords = aTexCoords;
    WorldPos = (inverse(Projection * View) * vec4(aPos, 1.0)).xyz;
    gl_Position = vec4(aPos, 1.0);
}
