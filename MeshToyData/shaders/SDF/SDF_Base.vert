#version 430 core

// TODO: this is the same for all SDF shaders, replace with standard one
//       after the material definition is done

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

layout (std140) uniform Matrices
{
    mat4 Projection;
    mat4 View;
};

uniform mat4 Model = mat4(1.0);

out vec3 WorldPos;

void main()
{
    WorldPos = (Model * vec4(aPos, 1.0)).xyz;
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
}
