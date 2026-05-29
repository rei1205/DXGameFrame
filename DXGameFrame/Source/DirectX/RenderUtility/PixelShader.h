// PixelShader.h
#pragma once
#include "Shader.h"

/**
 * @brief ピクセルシェーダーを扱う
 */
class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader() = default;

	/**
	 * @brief Direct3Dのピクセルシェーダーを取得する
	 * @return ピクセルシェーダーへのポインタ
	 */
	ID3D11PixelShader* GetPixelShader()
	{
		return m_pPS.Get();
	}

private:
	/// ピクセルシェーダー
	ComPtr<ID3D11PixelShader> m_pPS;

	/**
	 * @brief csoファイルからシェーダーデータを作成
	 * @param filePath ピクセルシェーダー(.cso)へのファイルパス
	 * @return 成功したかを返す
	 */
	HRESULT LoadFromCSOFile(const std::string& filePath) override;

	/**
	 * @brief ピクセルシェーダーを作成する
	 * @param data ピクセルシェーダーのコンパイル済みデータ
	 * @param dataSize ピクセルシェーダーデータのサイズ
	 * @return 成功したかを返す
	 */
	HRESULT CreatePixelShader(const char* data, int dataSize);
};