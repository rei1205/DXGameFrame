// PipelineStateManager.cpp
#include "PipelineStateManager.h"
#include "../../System/Debug.h"

std::unordered_map<std::string, std::shared_ptr<BlendState>> PipelineStateManager::s_blendStates;
std::unordered_map<std::string, std::shared_ptr<DepthStencilState>> PipelineStateManager::s_depthStencilStates;
std::unordered_map<std::string, std::shared_ptr<RasterizerState>> PipelineStateManager::s_rasterizerStates;
std::unordered_map<std::string, std::shared_ptr<SamplerState>> PipelineStateManager::s_samplerStates;
BlendState* PipelineStateManager::s_pCurrentBlendState = nullptr;
DepthStencilState* PipelineStateManager::s_pCurrentDepthStencilState = nullptr;
RasterizerState* PipelineStateManager::s_pCurrentRasterizerState = nullptr;
SamplerState* PipelineStateManager::s_pCurrentSamplerState = nullptr;

HRESULT PipelineStateManager::Init()
{
    HRESULT hr = S_OK;

    // 初期ブレンドステートを作成
    hr = CreateDefaultBlendStates();
    if (FAILED(hr)) { return hr; }

    // 初期深度ステンシルステートを作成
    hr = CreateDefaultDepthStencilStates();
    if (FAILED(hr)) { return hr; }

    // 初期ラスタライザーステートを作成
    hr = CreateDefaultRasterizerStates();
    if (FAILED(hr)) { return hr; }
    
    // 初期サンプラーステートを作成
    hr = CreateDefaultSamplerStates();
    if (FAILED(hr)) { return hr; }

    return hr;
}

void PipelineStateManager::Uninit()
{
    s_blendStates.clear();
    s_depthStencilStates.clear();
    s_rasterizerStates.clear();
    s_samplerStates.clear();
    s_pCurrentBlendState = nullptr;
    s_pCurrentDepthStencilState = nullptr;
    s_pCurrentRasterizerState = nullptr;
    s_pCurrentSamplerState = nullptr;
}

BlendState* PipelineStateManager::GetBlendState(const std::string& name)
{
    auto it = s_blendStates.find(name);
    if (it == s_blendStates.end())
        return nullptr;

    return it->second.get();
}

DepthStencilState* PipelineStateManager::GetDepthStencilState(const std::string& name)
{
    auto it = s_depthStencilStates.find(name);
    if (it == s_depthStencilStates.end())
        return nullptr;

    return it->second.get();
}

RasterizerState* PipelineStateManager::GetRasterizerState(const std::string& name)
{
    auto it = s_rasterizerStates.find(name);
    if (it == s_rasterizerStates.end())
        return nullptr;

    return it->second.get();
}

SamplerState* PipelineStateManager::GetSamplerState(const std::string& name)
{
    auto it = s_samplerStates.find(name);
    if (it == s_samplerStates.end())
        return nullptr;

    return it->second.get();
}

HRESULT PipelineStateManager::CreateBlendStates(const D3D11_BLEND_DESC* pDesc, const std::string& name)
{
    auto it = s_blendStates.find(name);
    if (it == s_blendStates.end())
    {
        // ブレンドステートを作成
        auto state = std::make_shared<BlendState>();
        HRESULT hr = state->Create(pDesc, name);

        // 成功したら終了
        if (SUCCEEDED(hr))
        {
            s_blendStates[name] = state;
            return hr;
        }
    }

    Debug::ErrorMessage("ブレンドステート[" + name + "]の作成に失敗しました。");
    return S_FALSE;
}

HRESULT PipelineStateManager::CreateDepthStencilStates(const D3D11_DEPTH_STENCIL_DESC* pDesc, const std::string& name)
{
    auto it = s_depthStencilStates.find(name);
    if (it == s_depthStencilStates.end())
    {
        // 深度ステンシルステートを作成
        auto state = std::make_shared<DepthStencilState>();
        HRESULT hr = state->Create(pDesc, name);

        // 成功したら終了
        if (SUCCEEDED(hr))
        {
            s_depthStencilStates[name] = state;
            return hr;
        }
    }

    Debug::ErrorMessage("深度ステンシルステート[" + name + "]の作成に失敗しました。");
    return S_FALSE;
}

HRESULT PipelineStateManager::CreateRasterizerStates(const D3D11_RASTERIZER_DESC* pDesc, const std::string& name)
{
    auto it = s_rasterizerStates.find(name);
    if (it == s_rasterizerStates.end())
    {
        // ラスタライザーステートを作成
        auto state = std::make_shared<RasterizerState>();
        HRESULT hr = state->Create(pDesc, name);

        // 成功したら終了
        if (SUCCEEDED(hr))
        {
            s_rasterizerStates[name] = state;
            return hr;
        }
    }

    Debug::ErrorMessage("ラスタライザーステート[" + name + "]の作成に失敗しました。");
    return S_FALSE;
}

HRESULT PipelineStateManager::CreateSamplerStates(const D3D11_SAMPLER_DESC* pDesc, const std::string& name)
{
    auto it = s_samplerStates.find(name);
    if (it == s_samplerStates.end())
    {
        // サンプラーステートを作成
        auto state = std::make_shared<SamplerState>();
        HRESULT hr = state->Create(pDesc, name);

        // 成功したら終了
        if (SUCCEEDED(hr))
        {
            s_samplerStates[name] = state;
            return hr;
        }
    }

    Debug::ErrorMessage("サンプラーステート[" + name + "]の作成に失敗しました。");
    return S_FALSE;
}

HRESULT PipelineStateManager::CreateDefaultBlendStates()
{
    HRESULT hr = S_OK;
    D3D11_BLEND_DESC blendDesc;		// ブレンドステート設定情報
    D3D11_RENDER_TARGET_BLEND_DESC* rt;

    // ブレンド無し
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    rt = &blendDesc.RenderTarget[0];
    rt->BlendEnable = FALSE;
    rt->SrcBlend = D3D11_BLEND_ONE;
    rt->DestBlend = D3D11_BLEND_ZERO;
    rt->BlendOp = D3D11_BLEND_OP_ADD;
    rt->SrcBlendAlpha = D3D11_BLEND_ONE;
    rt->DestBlendAlpha = D3D11_BLEND_ZERO;
    rt->BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rt->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    hr = CreateBlendStates(&blendDesc, BlendStateName::None);
    if (FAILED(hr)) { return hr; }

    // アルファブレンド
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    rt = &blendDesc.RenderTarget[0];
    rt->BlendEnable = TRUE;
    rt->SrcBlend = D3D11_BLEND_SRC_ALPHA;
    rt->DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    rt->BlendOp = D3D11_BLEND_OP_ADD;
    rt->SrcBlendAlpha = D3D11_BLEND_ONE;
    rt->DestBlendAlpha = D3D11_BLEND_ZERO;
    rt->BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rt->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    hr = CreateBlendStates(&blendDesc, BlendStateName::Alpha);
    if (FAILED(hr)) { return hr; }

    // 加算
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    rt = &blendDesc.RenderTarget[0];
    rt->BlendEnable = TRUE;
    rt->SrcBlend = D3D11_BLEND_SRC_ALPHA;
    rt->DestBlend = D3D11_BLEND_ONE;
    rt->BlendOp = D3D11_BLEND_OP_ADD;
    rt->SrcBlendAlpha = D3D11_BLEND_ONE;
    rt->DestBlendAlpha = D3D11_BLEND_ZERO;
    rt->BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rt->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    hr = CreateBlendStates(&blendDesc, BlendStateName::Add);
    if (FAILED(hr)) { return hr; }

    // 減算
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    rt = &blendDesc.RenderTarget[0];
    rt->BlendEnable = TRUE;
    rt->SrcBlend = D3D11_BLEND_SRC_ALPHA;
    rt->DestBlend = D3D11_BLEND_ONE;
    rt->BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
    rt->SrcBlendAlpha = D3D11_BLEND_ONE;
    rt->DestBlendAlpha = D3D11_BLEND_ZERO;
    rt->BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rt->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    hr = CreateBlendStates(&blendDesc, BlendStateName::Subtract);
    if (FAILED(hr)) { return hr; }

    // 乗算
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    rt = &blendDesc.RenderTarget[0];
    rt->BlendEnable = TRUE;
    rt->SrcBlend = D3D11_BLEND_DEST_COLOR;
    rt->DestBlend = D3D11_BLEND_ZERO;
    rt->BlendOp = D3D11_BLEND_OP_ADD;
    rt->SrcBlendAlpha = D3D11_BLEND_ONE;
    rt->DestBlendAlpha = D3D11_BLEND_ZERO;
    rt->BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rt->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    hr = CreateBlendStates(&blendDesc, BlendStateName::Multiply);
    if (FAILED(hr)) { return hr; }

    // カラー描画無し
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    rt = &blendDesc.RenderTarget[0];
    rt->BlendEnable = FALSE;
    rt->RenderTargetWriteMask = 0;
    hr = CreateBlendStates(&blendDesc, BlendStateName::Disable);
    if (FAILED(hr)) { return hr; }

    return hr;
}

HRESULT PipelineStateManager::CreateDefaultDepthStencilStates()
{
    HRESULT hr = S_OK;
    D3D11_DEPTH_STENCIL_DESC dsDesc;	// 深度ステンシルステート設定情報

    // 深度テストON 深度書き込みON (通常)
    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.DepthEnable = TRUE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
    dsDesc.StencilEnable = FALSE;
    hr = CreateDepthStencilStates(&dsDesc, DepthStencilStateName::Write);
    if (FAILED(hr)) { return hr; }

    // 深度テストON 深度書き込みOFF (半透明用)
    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.DepthEnable = TRUE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    dsDesc.StencilEnable = FALSE;
    hr = CreateDepthStencilStates(&dsDesc, DepthStencilStateName::ReadOnly);
    if (FAILED(hr)) { return hr; }

    // 深度テストOFF (UI・2D用)
    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.DepthEnable = FALSE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    dsDesc.StencilEnable = FALSE;
    hr = CreateDepthStencilStates(&dsDesc, DepthStencilStateName::Disable);
    if (FAILED(hr)) { return hr; }

    return hr;
}

HRESULT PipelineStateManager::CreateDefaultRasterizerStates()
{
    HRESULT hr = S_OK;
    D3D11_RASTERIZER_DESC rasterizerDesc;		// ラスタライザーステート設定情報

    // 前面描画
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.FrontCounterClockwise = FALSE;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = TRUE;
    hr = CreateRasterizerStates(&rasterizerDesc, RasterizerStateName::Front);
    if (FAILED(hr)) { return hr; }

    // 背面描画
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_FRONT;
    rasterizerDesc.FrontCounterClockwise = FALSE;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = TRUE;
    hr = CreateRasterizerStates(&rasterizerDesc, RasterizerStateName::Back);
    if (FAILED(hr)) { return hr; }

    // 両面描画
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = TRUE;
    hr = CreateRasterizerStates(&rasterizerDesc, RasterizerStateName::None);
    if (FAILED(hr)) { return hr; }

    // ワイヤーフレーム描画
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.MultisampleEnable = TRUE;
    rasterizerDesc.AntialiasedLineEnable = TRUE;
    hr = CreateRasterizerStates(&rasterizerDesc, RasterizerStateName::Wireframe);
    if (FAILED(hr)) { return hr; }

    return hr;
}

HRESULT PipelineStateManager::CreateDefaultSamplerStates()
{
    HRESULT hr = S_OK;
    D3D11_SAMPLER_DESC samplerDesc;		// サンプラーステート設定情報

    // 線形補間 + 繰り返し
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = CreateSamplerStates(&samplerDesc, SamplerStateName::Linear_Wrap);
    if (FAILED(hr)) { return hr; }

    // 線形補間 + 端固定
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = CreateSamplerStates(&samplerDesc, SamplerStateName::Linear_Clamp);
    if (FAILED(hr)) { return hr; }

    // 線形補間 + 枠外黒
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    samplerDesc.BorderColor[0] = 0.0f;
    samplerDesc.BorderColor[1] = 0.0f;
    samplerDesc.BorderColor[2] = 0.0f;
    samplerDesc.BorderColor[3] = 1.0f;
    hr = CreateSamplerStates(&samplerDesc, SamplerStateName::Linear_Border_Black);
    if (FAILED(hr)) { return hr; }

    // 線形補間 + 枠外白
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    samplerDesc.BorderColor[0] = 1.0f;
    samplerDesc.BorderColor[1] = 1.0f;
    samplerDesc.BorderColor[2] = 1.0f;
    samplerDesc.BorderColor[3] = 1.0f;
    hr = CreateSamplerStates(&samplerDesc, SamplerStateName::Linear_Border_White);
    if (FAILED(hr)) { return hr; }

    // 最近傍 + 繰り返し
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = CreateSamplerStates(&samplerDesc, SamplerStateName::Point_Wrap);
    if (FAILED(hr)) { return hr; }

    // 最近傍 + 端固定
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = CreateSamplerStates(&samplerDesc, SamplerStateName::Point_Clamp);
    if (FAILED(hr)) { return hr; }

    // 最近傍 + 枠外黒
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    samplerDesc.BorderColor[0] = 0.0f;
    samplerDesc.BorderColor[1] = 0.0f;
    samplerDesc.BorderColor[2] = 0.0f;
    samplerDesc.BorderColor[3] = 1.0f;
    hr = CreateSamplerStates(&samplerDesc, SamplerStateName::Point_Border_Black);
    if (FAILED(hr)) { return hr; }

    // 最近傍 + 枠外白
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.MinLOD = 0.0f;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    samplerDesc.BorderColor[0] = 1.0f;
    samplerDesc.BorderColor[1] = 1.0f;
    samplerDesc.BorderColor[2] = 1.0f;
    samplerDesc.BorderColor[3] = 1.0f;
    hr = CreateSamplerStates(&samplerDesc, SamplerStateName::Point_Border_White);
    if (FAILED(hr)) { return hr; }

    return hr;
}
