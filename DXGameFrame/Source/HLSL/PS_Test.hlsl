#include "Common.hlsli"

struct PS_IN
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
    float4 wPos : POSITION0;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
    float3 N = normalize(pin.normal);
    float3 L = normalize(dLight.dir);

    float t = dot(N, L);
    t = saturate(-t);

    float4 color = tex.Sample(samp, pin.uv);
    color.rgb *= t;

    return color;
}