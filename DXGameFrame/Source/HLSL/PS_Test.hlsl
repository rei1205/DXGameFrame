struct PS_IN
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
    float4 wPos : POSITION0;
};

float4 main(PS_IN pin) : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}