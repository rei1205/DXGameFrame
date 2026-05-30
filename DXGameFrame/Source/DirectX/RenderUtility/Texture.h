// Texture.h
#pragma once
#include "../DirectXInclude.h"
#include <string>

/**
 * @brief テクスチャ情報を扱う
 */
class Texture
{
public:
	Texture();
	~Texture() = default;

	/// テクスチャサイズ
	struct Size
	{
		UINT x;		// テクスチャの幅
		UINT y;		// テクスチャの高さ
	};

	/**
	 * @brief テクスチャを読み込む
	 * @param filePath テクスチャ画像へのファイルパス
	 * @return 成功したかを返す
	 */
	HRESULT Load(const std::string& filePath);

	/**
	 * @brief シェーダーリソースビューを取得する
	 * @return シェーダーリソースビューへのポインタ
	 */
	ID3D11ShaderResourceView* GetSRV()
	{
		return m_pSRV.Get();
	}

	/**
	 * @brief このテクスチャのサイズを取得する
	 * @return テクスチャサイズ (ピクセル)
	 */
	Size GetSize()
	{
		return m_size;
	}

private:
	/// シェーダーリソースビュー
	ComPtr<ID3D11ShaderResourceView> m_pSRV;

	/// テクスチャ画像のサイズ
	Size m_size;

	/**
	 * @brief 実際のテクスチャ読み込み処理
	 * @param filePath テクスチャ画像へのファイルパス
	 * @return 成功したかを返す
	 */
	HRESULT LoadFromFile(const std::string& filePath);
};