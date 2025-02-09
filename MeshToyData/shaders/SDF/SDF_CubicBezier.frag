#version 430 core

#include "/includes/sdf.glsl"

out vec4 FragColor;

in vec3 WorldPos;

uniform vec2 P0 = vec2(0.0f, 0.0f);
uniform vec2 P1 = vec2(0.0f, 0.0f);
uniform vec2 P2 = vec2(0.0f, 0.0f);
uniform vec2 P3 = vec2(0.0f, 0.0f);
uniform float Thickness = 0.1f;
uniform vec4 Color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

void main()
{
    float sdf = sdfCubicBezier(WorldPos.xy, P0, P1, P2, P3, Thickness);
    float softMask = smoothstep(0, -AA_BIAS, sdf);
    float mask = step(sdf, 0);
    if (mask <= 0.0f) discard;

    FragColor = Color;
    FragColor.a = softMask * Color.a;
}
