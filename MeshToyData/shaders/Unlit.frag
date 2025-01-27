#version 430 core

out vec4 FragColor;

in vec2 TexCoords;

uniform vec4 BaseColor;

void main()
{                
    FragColor = BaseColor;
}
