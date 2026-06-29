#ifndef INCLUDE_COMMON_SHADER
#define INCLUDE_COMMON_SHADER

struct VS_IN_MESH
{
    float3 pos : POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
    float3 tangent : TANGENT0;
    float4 color : COLOR0;
};

struct VS_IN_SKINMESH
{
    float3 pos : POSITION;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
    float3 tangent : TANGENT0;
    float4 color : COLOR0;
    float4 weight : BLENDWEIGHT0;
    uint4 index : BLENDINDICES0;
};

struct VS_IN_SPRITE
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

cbuffer World : register(b0)
{
    float4x4 world;
    float4x4 invWorld;
};

struct DirectionalLight
{
    float3 dir;
    float intensity;
    float3 lightColor;
    float lightSize;
    float3 ambientColor;
    float pad;
    float4x4 viewProj;
};


cbuffer PerFrame : register(b1)
{
    float4x4 view;
    float4x4 projection;

    float3 cameraPos;
    float time;
    
    DirectionalLight dLight;
};

cbuffer Bone : register(b2)
{
    float4x4 bone[64];
};

#endif