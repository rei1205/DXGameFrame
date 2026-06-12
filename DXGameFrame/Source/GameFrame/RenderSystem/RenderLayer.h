// RenderLayer.h
#pragma once
#include "../../System/IDManager.h"
#include <unordered_map>
#include <string>

/// デフォルトのレイヤー名
namespace RenderLayerName
{
	constexpr const char* DefaultLayer = "Default";		// デフォルトレイヤー
	constexpr const char* ShadowLayer = "Shadow";		// シャドウレイヤー
}

/**
 * @brief 描画レイヤーを扱うクラス
 */
class RenderLayer
{
public:
	/// 無効なレイヤーID
	static constexpr int LayerID_None = -1;

	/**
	 * @brief 描画レイヤーの初期化
	 */
	static void Init();

	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief 描画レイヤーを追加する
	 * @param layerName 描画レイヤー名
	 */
	static void AddLayer(const std::string& layerName);

	/**
	 * @brief レイヤーIDを取得する
	 * @param layerName レイヤー名
	 * @return レイヤーID (存在しないレイヤー名の場合は-1を返す)
	 */
	static int GetLayerID(const std::string& layerName);

	/**
	 * @brief レイヤー名を取得する
	 * @param layerID レイヤーID
	 * @return レイヤー名
	 */
	static std::string GetLayerName(int layerID);

private:
	RenderLayer() = delete;

	/// 描画レイヤー名とレイヤーIDのマップ
	static std::unordered_map<std::string, int> s_renderLayerMap;

	/// ID生成機能
	static IDManager s_idManager;
};
