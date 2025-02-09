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

// TODO: review this (from https://www.shadertoy.com/view/XdVBWd)
float length2( in vec2 v ) { return dot(v,v); }

// TODO: review this (from https://www.shadertoy.com/view/XdVBWd)
float sdSegmentSq( in vec2 p, in vec2 a, in vec2 b )
{
    vec2 pa = p-a, ba = b-a;
    float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
    return length2( pa - ba*h );
}

float sdfCubicBezier(vec2 position, vec2 P0, vec2 P1, vec2 P2, vec2 P3, float Thickness)
{
    const int kNum = 50;
    float res = 1e10;
    vec2 a = P0;

    for (int i = 1; i < kNum; i++)
    {
        float t = float(i) / float(kNum - 1);
        float s = 1.0f - t;
        vec2 b = P0 * s * s * s + P1 * 3.0f * s * s * t + P2 * 3.0 * s * t * t + P3 * t * t * t;

        float d = sdSegmentSq(position, a, b);
        res = min(d, res);
        a = b;
    }
    
    return sqrt(res) - Thickness;
}
