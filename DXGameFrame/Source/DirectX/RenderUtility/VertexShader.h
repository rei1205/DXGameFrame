// VertexShader.h
#pragma once
#include "Shader.h"

/**
 * @brief 頂点シェーダーを扱う
 */
class VertexShader : public Shader
{
public:
	VertexShader();
	~VertexShader() = default;

	/**
	 * @brief Direct3Dの頂点シェーダーを取得する
	 * @return 頂点シェーダーへのポインタ
	 */
	ID3D11VertexShader* GetVertexShader()
	{
		return m_pVS.Get();
	}

	/**
	 * @brief 頂点入力レイアウトを取得する
	 * @return 頂点入力レイアウトへのポインタ
	 */
	ID3D11InputLayout* GetInputLayout()
	{
		return m_pInputLayout.Get();
	}

private:
	/// 頂点シェーダー
	ComPtr<ID3D11VertexShader> m_pVS;

	/// 頂点入力レイアウト
	ComPtr<ID3D11InputLayout> m_pInputLayout;

	/**
	 * @brief csoファイルからシェーダーデータを作成
	 * @param filePath 頂点シェーダー(.cso)へのファイルパス
	 * @return 成功したかを返す
	 */
	HRESULT LoadFromCSOFile(const std::string& filePath) override;

	/**
	 * @brief 頂点シェーダーを作成する
	 * @param data 頂点シェーダーのコンパイル済みデータ
	 * @param dataSize 頂点シェーダーデータのサイズ
	 * @return 成功したかを返す
	 */
	HRESULT CreateVertexShader(const char* data, int dataSize);

	/**
	 * @brief 頂点入力レイアウトを作成する
	 * @param data 頂点シェーダーのコンパイル済みデータ
	 * @param dataSize 頂点シェーダーデータのサイズ
	 * @return 成功したかを返す
	 */
	HRESULT CreateInputLayout(const char* data, int dataSize);
};