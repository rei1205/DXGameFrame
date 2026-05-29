// ShaderManager.h
#pragma once
#include "../RenderUtility/VertexShader.h"
#include "../RenderUtility/PixelShader.h"
#include <unordered_map>
#include <memory>

/**
 * @brief シェーダーを管理する
 */
class ShaderManager
{
public:
	/**
	 * @brief 多重読み込みを防ぎつつ頂点シェーダーを読み込む
	 * @param filePath 頂点シェーダー(.cso)へのファイルパス
	 * @return 頂点シェーダーへのポインタ(shared_ptr)
	 */
	static std::shared_ptr<VertexShader> LoadVertexShader(const std::string& filePath);

	/**
	 * @brief 多重読み込みを防ぎつつピクセルシェーダーを読み込む
	 * @param filePath ピクセルシェーダー(.cso)へのファイルパス
	 * @return ピクセルシェーダーへのポインタ(shared_ptr)
	*/
	static std::shared_ptr<PixelShader> LoadPixelShader(const std::string& filePath);

	/**
	 * @brief 頂点シェーダーをセットする
	 * @param pVS 実際の頂点シェーダーへのポインタ
	 * @param pInputLayout 入力レイアウトへのポインタ
	 */
	static void SetVertexShader(ID3D11VertexShader* pVS, ID3D11InputLayout* pInputLayout);

	/**
	 * @brief ピクセルシェーダーをセットする
	 * @param pPixelShader 実際のピクセルシェーダーへのポインタ
	 */
	static void SetPixelShader(ID3D11PixelShader* pPS);

	/**
	 * @brief 全てのシェーダーを解放する
	 */
	static void Clear();

	/**
	 * @brief シェーダーの設定状態をリセットする
	 * @note このクラス以外からシェーダーが変更された場合に呼び出してください
	 */
	static void Refresh()
	{
		s_pCurrentVS = nullptr;
		s_pCurrentPS = nullptr;
	}

private:
	ShaderManager() = delete;

	/// 頂点シェーダーとファイルパスのマップ
	static std::unordered_map<std::string, std::shared_ptr<VertexShader>> s_pVertexShaders;

	/// ピクセルシェーダーとファイルパスのマップ
	static std::unordered_map<std::string, std::shared_ptr<PixelShader>> s_pPixelShaders;

	/// 現在セットされている頂点シェーダー
	static ID3D11VertexShader* s_pCurrentVS;

	/// 現在セットされているピクセルシェーダー
	static ID3D11PixelShader* s_pCurrentPS;
};
