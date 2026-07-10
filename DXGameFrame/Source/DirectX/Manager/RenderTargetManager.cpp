// RenderTargetManager.cpp
#include "RenderTargetManager.h"
#include "../Direct3D.h"
#include "../../System/Debug.h"

std::array<std::unique_ptr<Texture>, (UINT)RTVType::COUNT> RenderTargetManager::s_RTVTextures;
std::array<std::unique_ptr<Texture>, (UINT)DSVType::COUNT> RenderTargetManager::s_DSVTextures;
std::array<TextureDesc, (UINT)RTVType::COUNT> RenderTargetManager::s_RTVTextureDescs;
std::array<TextureDesc, (UINT)DSVType::COUNT> RenderTargetManager::s_DSVTextureDescs;

HRESULT RenderTargetManager::Init(UINT width, UINT height)
{
    HRESULT hr = S_OK;

    hr = CreateAllRenderTargetTexture(width, height);
    if (FAILED(hr)) { return hr; }

    hr = CreateAllDepthStencilTexture(width, height);
    if (FAILED(hr)) { return hr; }

    Debug::ConsoleLog("RenderTargetManager : Initialized");
    return hr;
}

void RenderTargetManager::Uninit()
{
    for (auto& tex : s_RTVTextures)
    {
        tex.reset();
    }
    for (auto& tex : s_DSVTextures)
    {
        tex.reset();
    }

    Debug::ConsoleLog("RenderTargetManager : Unitialized");
}

HRESULT RenderTargetManager::ReSize(UINT width, UINT height)
{
    if (width == 0 || height == 0)
        return S_FALSE;

    HRESULT hr = S_OK;

    // RTVリサイズ
    for (UINT i = 0; i < (UINT)RTVType::COUNT; ++i)
    {
        switch ((RTVType)i)
        {
        case RTVType::SCENE:
            s_RTVTextureDescs[i].width = width;
            s_RTVTextureDescs[i].height = height;
            hr = s_RTVTextures[i]->Create(s_RTVTextureDescs[i]);
            if (FAILED(hr)) { return hr; }
        }
    }

    // DSVリサイズ
    for (UINT i = 0; i < (UINT)DSVType::COUNT; ++i)
    {
        switch ((DSVType)i)
        {
        case DSVType::SCENE:
            s_DSVTextureDescs[i].width = width;
            s_DSVTextureDescs[i].height = height;
            hr = s_DSVTextures[i]->Create(s_DSVTextureDescs[i]);
            if (FAILED(hr)) { return hr; }
        }
    }

    return hr;
}

void RenderTargetManager::ClearAllRenderTarget()
{
    float clearColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    for (auto& rtv : s_RTVTextures)
    {
        if (rtv == nullptr)
            continue;

        Direct3D::GetContext()->ClearRenderTargetView(rtv->GetRTV(), clearColor);
    }
}

void RenderTargetManager::ClearAllDepthStencil()
{
    for (auto& dsv : s_DSVTextures)
    {
        if (dsv == nullptr)
            continue;

        Direct3D::GetContext()->ClearDepthStencilView(dsv->GetDSV(),
            D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }
}

Texture* RenderTargetManager::GetRTVTexture(RTVType type)
{
    return s_RTVTextures[(UINT)type].get();
}

Texture* RenderTargetManager::GetDSVTexture(DSVType type)
{
    return s_DSVTextures[(UINT)type].get();
}

HRESULT RenderTargetManager::CreateAllRenderTargetTexture(UINT width, UINT height)
{
    HRESULT hr = S_OK;

    for (UINT i = 0; i < (UINT)RTVType::COUNT; ++i)
    {
        TextureDesc desc;
        desc.textureType = TextureType::RENDER_TARGET;

        switch ((RTVType)i)
        {
        case RTVType::SCENE:
            // シーンカラー
            desc.width = width;
            desc.height = height;
            desc.format = DXGI_FORMAT_R8G8B8A8_UNORM;
            break;

        case RTVType::EDITOR_SCENE:
            // シーンビュー用
            desc.width = width;
            desc.height = height;
            desc.format = DXGI_FORMAT_R8G8B8A8_UNORM;
            break;
        }

        auto texture = std::make_unique<Texture>();
        hr = texture->Create(desc);
        if (FAILED(hr)) { return hr; }

        s_RTVTextures[i] = std::move(texture);
        s_RTVTextureDescs[i] = desc;
    }

    return hr;
}

HRESULT RenderTargetManager::CreateAllDepthStencilTexture(UINT width, UINT height)
{
    HRESULT hr = S_OK;

    for (UINT i = 0; i < (UINT)DSVType::COUNT; ++i)
    {
        TextureDesc desc;
        desc.textureType = TextureType::DEPTH_STENCIL;

        switch ((DSVType)i)
        {
        case DSVType::SCENE:
            // シーン深度
            desc.width = width;
            desc.height = height;
            desc.format = DXGI_FORMAT_R24G8_TYPELESS;
            desc.SRVFormatOverride = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
            desc.DSVFormatOverride = DXGI_FORMAT_D24_UNORM_S8_UINT;
            break;

        case DSVType::EDITOR_SCENE:
            // シーンビュー用
            desc.width = width;
            desc.height = height;
            desc.format = DXGI_FORMAT_R24G8_TYPELESS;
            desc.SRVFormatOverride = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
            desc.DSVFormatOverride = DXGI_FORMAT_D24_UNORM_S8_UINT;
            break;
        }

        auto texture = std::make_unique<Texture>();
        hr = texture->Create(desc);
        if (FAILED(hr)) { return hr; }

        s_DSVTextures[i] = std::move(texture);
        s_DSVTextureDescs[i] = desc;
    }

    return hr;
}
