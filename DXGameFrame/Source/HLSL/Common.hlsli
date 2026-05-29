#ifndef INCLUDE_COMMON_SHADER
#define INCLUDE_COMMON_SHADER

struct VS_IN_MESH
{
    float3 pos : POSITION;          // 頂点座標
    float3 normal : NORMAL0;        // 法線
    float2 uv : TEXCOORD0;          // UV座標
    float4 color : COLOR0;          // 頂点カラー
};

struct VS_IN_SKINMESH
{
    float3 pos : POSITION;          // 頂点座標
    float3 normal : NORMAL0;        // 法線
    float2 uv : TEXCOORD0;          // UV座標
    float4 color : COLOR0;          // 頂点カラー
    float4 weight : BLENDWEIGHT0;   // 頂点スキンウエイト
    uint4 index : BLENDINDICES0;    // 対応ボーンインデックス
};

struct VS_IN_SPRITE
{
    
};

#endif