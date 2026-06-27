// Texture.h
#pragma once
#include "../DirectXInclude.h"
#include <string>

/// テクスチャの種類
enum class TextureType
{
	TEXTURE2D,			// 通常のテクスチャ
	RENDER_TARGET,		// レンダーターゲット用
	DEPTH_STENCIL,		// 深度ステンシル用
	DYNAMIC				// 動的テクスチャ
};

/// テクスチャ生成情報
struct TextureDesc
{
	/// 幅
	UINT width = 1;

	/// 高さ
	UINT height = 1;

	/// テクスチャタイプ
	TextureType textureType = TextureType::TEXTURE2D;

	/// テクスチャフォーマット
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
};

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
	 * @brief テクスチャを生成する
	 * @param textureDesc テクスチャ生成方法
	 * @return 成功したかを返す
	 */
	HRESULT Create(const TextureDesc& textureDesc);

	/**
	 * @brief シェーダーリソースビューを取得する
	 * @return シェーダーリソースビューへのポインタ
	 */
	ID3D11ShaderResourceView* GetSRV()
	{
		return m_pSRV.Get();
	}

	/**
	 * @brief レンダーターゲットビューを取得する
	 * @return レンダーターゲットビューへのポインタ
	 */
	ID3D11RenderTargetView* GetRTV()
	{
		return m_pRTV.Get();
	}

	/**
	 * @brief 深度ステンシルビューを取得する
	 * @return 深度ステンシルビューへのポインタ
	 */
	ID3D11DepthStencilView* GetDSV()
	{
		return m_pDSV.Get();
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

	/// 深度ステンシルビュー
	ComPtr<ID3D11DepthStencilView> m_pDSV;

	/// レンダーターゲット
	ComPtr<ID3D11RenderTargetView> m_pRTV;

	/// テクスチャ画像のサイズ
	Size m_size;

	/**
	 * @brief 画像ファイルからテクスチャを読み込む
	 * @param filePath テクスチャ画像へのファイルパス
	 * @return 成功したかを返す
	 */
	HRESULT LoadFromImageFile(const std::string& filePath);
};