// Texture.cpp
#include "Texture.h"
#include "../Direct3D.h"
#include "../../System/Debug.h"
#include <DirectXTex/DirectXTex.h>

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
	m_size{}
{
}

HRESULT Texture::Load(const std::string& filePath)
{
	HRESULT hr = S_OK;

	// ファイルからテクスチャを読み込む
	hr = LoadFromFile(filePath);
	if (FAILED(hr))
	{
		Debug::ErrorMessage(filePath + "の読み込みに失敗しました。");
		return hr;
	}

	Debug::ConsoleLog("Load Texture : " + filePath);
	return hr;
}

HRESULT Texture::LoadFromFile(const std::string& filePath)
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
