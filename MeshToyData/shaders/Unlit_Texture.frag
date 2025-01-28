#version 430 core

out vec4 FragColor;

in vec2 TexCoords;

uniform vec4 BaseColor;
uniform sampler2D Texture;

void main()
{                
    FragColor = texture(Texture, TexCoords) * BaseColor;
}
