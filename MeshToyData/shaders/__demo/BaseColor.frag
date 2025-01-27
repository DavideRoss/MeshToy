#version 330 core
#extension GL_ARB_shading_language_include : require

#include "/includes/common.glsl"

out vec4 FragColor;

void main()
{
    vec2 viewSpace = vec2(gl_FragCoord.x / 1920, gl_FragCoord.y / 1080);
    float val = step(length(viewSpace), 0.5f);
    FragColor = vec4(val, val, val, 1.0f);
}