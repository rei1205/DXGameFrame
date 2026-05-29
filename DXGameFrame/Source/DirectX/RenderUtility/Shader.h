// Shader.h
#pragma once
#include "../DirectXInclude.h"
#include <string>

/**
 * @brief シェーダーの基底クラス
 */
class Shader
{
public:
	Shader() = default;
	virtual ~Shader() = default;

	/**
	 * @brief シェーダーを読み込む
	 * @details 失敗した場合、プログラムを終了します
	 * @param filePath シェーダー(.cso)へのファイルパス
	 */
	void Load(const std::string& filePath);

private:
	/**
	 * @brief csoファイルからシェーダーデータを作成
	 * @param filePath シェーダー(.cso)へのファイルパス
	 * @return 成功したかを返す
	 */
	virtual HRESULT LoadFromCSOFile(const std::string& filePath) = 0;
};