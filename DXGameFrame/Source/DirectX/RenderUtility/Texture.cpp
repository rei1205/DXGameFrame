// Texture.cpp
#include "Texture.h"
#include "../Direct3D.h"
#include "../../System/Debug.h"
#include <DirectXTex/DirectXTex.h>
#include <format>

#ifdef _X86_
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/Win32/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/Win32/Release/DirectXTex.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/x64/Debug/DirectXTex.lib")
#else
#pragma comment(lib, "DirectXTex/x64/Release/DirectXTex.lib")
#endif
#endif

Texture::Texture() :
	m_pSRV(nullptr),
	m_pDSV(nullptr),
	m_pRTV(nullptr),
	m_size{}
{
}

HRESULT Texture::Load(const std::string& filePath)
{
	HRESULT hr = S_OK;

	// ファイルからテクスチャを読み込む
	hr = LoadFromImageFile(filePath);
	if (FAILED(hr))
	{
		Debug::ErrorMessage(filePath + "の読み込みに失敗しました。");
		return hr;
	}

	Debug::ConsoleLog("Load Texture : " + filePath);
	return hr;
}

HRESULT Texture::Create(const TextureDesc& textureDesc)
{
	HRESULT hr = S_OK;

	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = textureDesc.width;
	desc.Height = textureDesc.height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = textureDesc.format;
	desc.SampleDesc.Count = 1;

	// テクスチャタイプごとの設定
	switch (textureDesc.textureType)
	{
	case TextureType::TEXTURE2D:
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		break;

	case TextureType::RENDER_TARGET:
		desc.BindFlags =
			D3D11_BIND_SHADER_RESOURCE |
			D3D11_BIND_RENDER_TARGET;
		break;

	case TextureType::DEPTH_STENCIL:
		desc.BindFlags =
			D3D11_BIND_SHADER_RESOURCE |
			D3D11_BIND_DEPTH_STENCIL;
		break;

	case TextureType::DYNAMIC:
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	}

	// テクスチャ生成
	ComPtr<ID3D11Texture2D> pTexture;
	hr = Direct3D::GetDevice()->CreateTexture2D(&desc, nullptr, pTexture.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	// SRV作成
	if (desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
	{
		if (textureDesc.SRVFormatOverride == DXGI_FORMAT_UNKNOWN)
		{
			hr = Direct3D::GetDevice()->CreateShaderResourceView(pTexture.Get(), nullptr, m_pSRV.GetAddressOf());
		}
		else
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = textureDesc.SRVFormatOverride;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = desc.MipLevels;

			hr = Direct3D::GetDevice()->CreateShaderResourceView(pTexture.Get(), &srvDesc, m_pSRV.GetAddressOf());
		}
		if (FAILED(hr)) { return hr; }
	}

	// RTV作成
	if (desc.BindFlags & D3D11_BIND_RENDER_TARGET)
	{
		if (textureDesc.RTVFormatOverride == DXGI_FORMAT_UNKNOWN)
		{
			hr = Direct3D::GetDevice()->CreateRenderTargetView(
				pTexture.Get(), nullptr, m_pRTV.GetAddressOf());
		}
		else
		{
			D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
			rtvDesc.Format = textureDesc.RTVFormatOverride;
			rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtvDesc.Texture2D.MipSlice = 0;

			hr = Direct3D::GetDevice()->CreateRenderTargetView(
				pTexture.Get(), &rtvDesc, m_pRTV.GetAddressOf());
		}
		if (FAILED(hr)) { return hr; }
	}

	// DSV作成
	if (desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		if (textureDesc.DSVFormatOverride == DXGI_FORMAT_UNKNOWN)
		{
			hr = Direct3D::GetDevice()->CreateDepthStencilView(
				pTexture.Get(), nullptr, m_pDSV.GetAddressOf());
		}
		else
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
			dsvDesc.Format = textureDesc.DSVFormatOverride;
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			dsvDesc.Flags = 0;
			dsvDesc.Texture2D.MipSlice = 0;

			hr = Direct3D::GetDevice()->CreateDepthStencilView(
				pTexture.Get(), &dsvDesc, m_pDSV.GetAddressOf());
		}

		if (FAILED(hr)) { return hr; }
	}

	m_size.x = desc.Width;
	m_size.y = desc.Height;

	std::string message = std::format("Create Texture : {} * {}", desc.Width, desc.Height);
	Debug::ConsoleLog(message);
	return hr;
}

HRESULT Texture::LoadFromImageFile(const std::string& filePath)
{
	HRESULT hr = S_OK;

	// 文字変換 (DirectXTexではwchar_t*を使用します)
	wchar_t wPath[MAX_PATH];
	MultiByteToWideChar(0, 0, filePath.c_str(), -1, wPath, MAX_PATH);

	// ファイル別読み込み
	DirectX::TexMetadata mdata;
	DirectX::ScratchImage image;
	if (strstr(filePath.c_str(), ".tga"))
	{
		hr = DirectX::LoadFromTGAFile(wPath, &mdata, image);
	}
	else
	{
		hr = DirectX::LoadFromWICFile(wPath, DirectX::WIC_FLAGS::WIC_FLAGS_IGNORE_SRGB, &mdata, image);
	}
	if (FAILED(hr)) { return hr; }

	// シェーダリソースビューを作成
	hr = CreateShaderResourceView(
		Direct3D::GetDevice(),
		image.GetImages(),
		image.GetImageCount(),
		mdata,
		m_pSRV.GetAddressOf()
	);
	if (FAILED(hr)) { return hr; }

	// ファイルサイズを保存
	m_size.x = (UINT)mdata.width;
	m_size.y = (UINT)mdata.height;

	return hr;
}
