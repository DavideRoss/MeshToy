#version 430 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 WorldPos;

void main()
{
    // TODO: move to grid settings
    vec3 MainColor = vec3(0.0, 0.0, 0.0);
    vec3 XAxisColor = vec3(1.0, 0.0, 0.0);
    vec3 YAxisColor = vec3(0.0, 1.0, 0.0);
    float Edge = 0.01f;
    float MainAlpha = 0.125f;
    float AxisAlpha = 0.25f;

    vec2 normWorld = fract(WorldPos.xy + Edge / 2.0f);
    float mask = 1.0f - clamp(step(Edge, normWorld.x) * step(Edge, normWorld.y), 0.0, 1.0);

    float xAxis = 1.0f - step(Edge, abs(WorldPos.x) + Edge / 2.0f);
    float yAxis = 1.0f - step(Edge, abs(WorldPos.y) + Edge / 2.0f);

    vec3 finalColor = MainColor;
    finalColor = mix(finalColor, XAxisColor, xAxis);
    finalColor = mix(finalColor, YAxisColor, yAxis);

    float finalAlpha = MainAlpha;
    finalAlpha = mix(finalAlpha, AxisAlpha, clamp(xAxis + yAxis, 0.0, 1.0));

    FragColor = vec4(finalColor, mask * finalAlpha);
}
