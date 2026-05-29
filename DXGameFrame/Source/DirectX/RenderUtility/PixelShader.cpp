// PixelShader.cpp
#include "PixelShader.h"
#include "../Direct3D.h"


PixelShader::PixelShader() :
	m_pPS(nullptr)
{
}

HRESULT PixelShader::LoadFromCSOFile(const std::string& filePath)
{
	HRESULT hr;			// 関数の結果
	FILE* fp;			// ファイルポインタ
	char* data;			// ファイル読み込み先
	long dataSize;		// ファイルサイズ

	// csoファイルを開く
	fopen_s(&fp, filePath.c_str(), "rb");
	if (fp == nullptr)
		return E_FAIL;

	// ファイルサイズを取得
	fseek(fp, 0, SEEK_END);
	dataSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// ファイル読み込み
	data = new char[dataSize];
	fread_s(data, dataSize, 1, dataSize, fp);
	fclose(fp);

	// ピクセルシェーダーを作成
	hr = CreatePixelShader(data, dataSize);

	// メモリ解放
	delete[] data;

	return hr;
}

HRESULT PixelShader::CreatePixelShader(const char* data, int dataSize)
{
	HRESULT hr;		// 関数の結果

	// ピクセルシェーダーを作成
	hr = Direct3D::GetDevice()->CreatePixelShader(
		data,
		dataSize,
		nullptr,
		m_pPS.GetAddressOf()
	);

	return hr;
}