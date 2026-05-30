// TextureManager.h
#pragma once
#include "../RenderUtility/Texture.h"
#include <unordered_map>
#include <memory>

/// テクスチャのスロット番号
namespace TextureSlot
{
	constexpr UINT MaterialSlotCount = 8;		// マテリアルの使用可能スロット数
	constexpr UINT Main = 0;					// メインテクスチャ
}

/**
 * @brief テクスチャを管理する
 */
class TextureManager
{
public:
	/**
	 * @brief 多重読み込みを防ぎつつテクスチャを読み込む
	 * @param filePath テクスチャ画像へのファイルパス
	 * @return テクスチャへのポインタ(shared_ptr)
	 */
	static std::shared_ptr<Texture> LoadTexture(const std::string& filePath);

	/**
	 * @brief テクスチャをセットする
	 * @param pTexture テクスチャへのポインタ
	 * @param slot セットするスロット番号
	 */
	static void SetTexture(Texture* pTexture, UINT slot = TextureSlot::Main);

	/**
	 * @brief 使用していないアセットを解放する
	 */
	static void CollectGarbage();

	/**
	 * @brief 全てのテクスチャを解放する
	 */
	static void Clear();

private:
	TextureManager() = delete;

	/// テクスチャとファイルパスのマップ
	static std::unordered_map<std::string, std::shared_ptr<Texture>> s_textures;
};
