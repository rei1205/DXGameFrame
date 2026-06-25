// Material.h
#pragma once
#include "../Manager/TextureManager.h"
#include "../Manager/ShaderManager.h"
#include "../Manager/ConstantBufferManager.h"
#include "../Manager/PipelineStateManager.h"
#include <array>

/**
 * @brief 描画情報をまとめたクラス
 */
class Material
{
public:
	Material();
	virtual ~Material() = default;

	/**
	 * @brief マテリアルをセットする
	 */
	void Bind() const;

	/**
	 * @brief テクスチャ画像を設定する
	 * @param filePath テクスチャ画像へのファイルパス
	 * @param slot 設定するスロット番号
	 */
	void SetTexture(const std::string& filePath, UINT slot = TextureSlot::Main);

	/**
	 * @brief テクスチャ画像を設定する
	 * @param pTexture テクスチャへのポインタ (shared_ptr)
	 * @param slot 設定するスロット番号
	 */
	void SetTexture(std::shared_ptr<Texture> pTexture, UINT slot = TextureSlot::Main);

	/**
	 * @brief テクスチャを取得する
	 * @param slot テクスチャスロット番号
	 * @return テクスチャへのポインタ
	 */
	Texture* GetTexture(UINT slot = TextureSlot::Main);

	/**
	 * @brief 頂点シェーダーを設定する
	 * @param filePath 頂点シェーダー(.cso)へのファイルパス
	 */
	void SetVertexShader(const std::string& filePath);

	/**
	 * @brief 頂点シェーダーを設定する
	 * @param pVertexShader 頂点シェーダーへのポインタ (shared_ptr)
	 */
	void SetVertexShader(std::shared_ptr<VertexShader> pVertexShader);

	/**
	 * @brief ピクセルシェーダーを設定する
	 * @param filePath ピクセルシェーダー(.cso)へのファイルパス
	 */
	void SetPixelShader(const std::string& filePath);

	/**
	 * @brief ピクセルシェーダーを設定する
	 * @param pPixelShader ピクセルシェーダーへのポインタ (shared_ptr)
	 */
	void SetPixelShader(std::shared_ptr<PixelShader> pPixelShader);

	/**
	 * @brief マテリアルのパラメータを設定する
	 * @param data 設定するデータへのポインタ (256バイト以下)
	 * @param size 設定するデータのメモリサイズ
	 */
	void SetParameter(const void* pData, UINT size);

	/**
	 * @brief ブレンドステートを設定する
	 * @param blendStateName ブレンドステート名
	 */
	void SetBlendState(const std::string& blendStateName);

	/**
	 * @brief 深度ステンシルステートを設定する
	 * @param depthStencilStateName 深度ステンシルステート名
	 */
	void SetDepthStencilState(const std::string& depthStencilStateName);

	/**
	 * @brief ラスタライザーステートを設定する
	 * @param rasterizerStateName ラスタライザーステート名
	 */
	void SetRasterizerState(const std::string& rasterizerStateName);

	/**
	 * @brief サンプラーステートを設定する
	 * @param samplerStateName サンプラーステート名
	 * @param slot 設定するスロット番号
	 */
	void SetSamplerState(const std::string& samplerStateName, UINT slot);

private:
	/// テクスチャ配列
	std::array<std::shared_ptr<Texture>, TextureSlot::MaterialSlotCount> m_pTextures;

	/// 頂点シェーダーへのポインタ
	std::shared_ptr<VertexShader> m_pVertexShader;

	/// ピクセルシェーダーへのポインタ
	std::shared_ptr<PixelShader> m_pPixelShader;

	/// マテリアルごとのパラメータ
	std::vector<BYTE> m_customParameter;

	/// ブレンドステート
	BlendState* m_pBlendState;

	/// 深度ステンシルステート
	DepthStencilState* m_pDepthStencilState;

	/// ラスタライザーステート
	RasterizerState* m_pRasterizerState;

	/// サンプラーステート
	std::array<SamplerState*, TextureSlot::MaterialSlotCount> m_pSamplerState;
};