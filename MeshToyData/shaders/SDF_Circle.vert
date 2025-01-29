#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

layout (std140) uniform Matrices
{
    mat4 Projection;
    mat4 View;
};

uniform mat4 Model;

out vec3 WorldPos;

void main()
{
    WorldPos = (Model * vec4(aPos, 1.0)).xyz;
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
}
