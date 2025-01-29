#version 430 core

#define AA_BIAS 0.001f

out vec4 FragColor;

in vec3 WorldPos;

uniform vec2 Position = vec2(0.0f, 0.0f);
uniform float Radius = 0.1f;
uniform vec4 Color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

void main()
{
    float sdf = length(WorldPos.xy - Position);
    float softMask = smoothstep(Radius, Radius - AA_BIAS, sdf);
    float mask = step(sdf, Radius);
    
    if (mask <= 0.0f) discard;
    FragColor = Color;
    FragColor.a = softMask;
}
