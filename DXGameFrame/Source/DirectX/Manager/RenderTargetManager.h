// RenderTargetManager.h
#pragma once
#include "../RenderUtility/Texture.h"
#include <memory>
#include <array>

/// レンダーターゲットの種類
enum class RTVType : UINT
{
	SCENE,				// シーンカラー
	EDITOR_SCENE,		// シーンビュー用
	COUNT
};

/// 深度ステンシルビューの種類
enum class DSVType : UINT
{
	SCENE,				// シーン深度
	EDITOR_SCENE,		// シーンビュー用
	COUNT
};

/**
 * @brief レンダーターゲットを管理するクラス
 */
class RenderTargetManager
{
public:
	/**
	 * @brief レンダーターゲットの初期化を行う
	 * @param width 画面の幅
	 * @param height 画面の高さ
	 * @return 成功したかを返す
	 */
	static HRESULT Init(UINT width, UINT height);

	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief ウィンドウサイズ変更時の処理
	 * @param width 画面の幅
	 * @param height 画面の高さ
	 * @return 成功したかを返す
	 */
	static HRESULT ReSize(UINT width, UINT height);

	/**
	 * @brief レンダーターゲットを全てクリアする
	 */
	static void ClearAllRenderTarget();

	/**
	 * @brief 深度ステンシルを全てクリアする
	 */
	static void ClearAllDepthStencil();

	/**
	 * @brief レンダーターゲットのテクスチャを取得する
	 * @param type レンダーターゲットの種類
	 * @return レンダーターゲットのテクスチャへのポインタ
	 */
	static Texture* GetRTVTexture(RTVType type);

	/**
	 * @brief 深度ステンシルのテクスチャを取得する
	 * @param type 深度ステンシルの種類
	 * @return 深度ステンシルのテクスチャへのポインタ
	 */
	static Texture* GetDSVTexture(DSVType type);

	/**
	 * @brief 全てのレンダーターゲットのテクスチャを作成する
	 * @param width 画面の幅
	 * @param height 画面の高さ
	 * @return 成功したかを返す
	 */
	static HRESULT CreateAllRenderTargetTexture(UINT width, UINT height);

	/**
	 * @brief 全ての深度ステンシルのテクスチャを作成する
	 * @param width 画面の幅
	 * @param height 画面の高さ
	 * @return 成功したかを返す
	 */
	static HRESULT CreateAllDepthStencilTexture(UINT width, UINT height);

private:
	RenderTargetManager() = delete;

	/// レンダーターゲットビューのテクスチャ
	static std::array<std::unique_ptr<Texture>, (UINT)RTVType::COUNT> s_RTVTextures;

	/// 深度ステンシルビューのテクスチャ
	static std::array<std::unique_ptr<Texture>, (UINT)DSVType::COUNT> s_DSVTextures;

	/// レンダーターゲットビューのテクスチャ生成情報
	static std::array<TextureDesc, (UINT)RTVType::COUNT> s_RTVTextureDescs;

	/// 深度ステンシルビューのテクスチャ生成情報
	static std::array<TextureDesc, (UINT)DSVType::COUNT> s_DSVTextureDescs;
};
