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


cbuffer World : register(b0)
{
    float4x4 world;             // ワールド行列
    float4x4 invWorld;          // ワールド逆行列
}

struct DirectionalLight
{
    float3 dir;                 // ライト方向
    float intensity;            // ライトの強さ
    float3 lightColor;          // ライトの色
    float lightSize;            // ライトサイズ (ソフトシャドウ用)
    float3 ambientColor;        // 環境光
    float pad;
    float viewProj;             // ライトビュープロジェクション行列
};

cbuffer PerFrame : register(b1)
{
    float4x4 view;              // ビュー行列
    float4x4 projection;        // プロジェクション逆行列
    
    float3 cameraPos;           // カメラ座標
    float time;                 // 経過時間
    
    DirectionalLight dLight;    // ディレクショナルライト情報
}

cbuffer Bone : register(b2)
{
    float4x4 bone[64];          // ボーン行列
}

#endif