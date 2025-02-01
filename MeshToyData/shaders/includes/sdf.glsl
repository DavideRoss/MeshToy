#define AA_BIAS 0.001f

float sdfCircle(vec2 position, float radius)
{
    return length(position) - radius;
}

float sdfLine(vec2 position, vec2 start, vec2 end, float Thickness)
{
    vec2 pa = position - start, diff = end - start;
    float h = clamp(dot(pa , diff) / dot(diff, diff), 0.0, 1.0);
    return length(pa - diff * h) - Thickness;
}