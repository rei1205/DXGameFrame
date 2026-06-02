// RenderSystem.h
#pragma once
#include "RenderPass/RenderPass.h"
#include <vector>
#include <memory>

/**
 * @brief シーンの描画を行う
 */
class RenderSystem
{
public:
	RenderSystem() = default;
	~RenderSystem() = default;

	/**
	 * @brief 終了処理
	 */
	void Uninit();

	/**
	 * @brief 全ての描画パスの描画を行う
	 */
	void DrawAll();

	/**
	 * @brief 描画パスを登録する
	 * @param pRenderPass 描画パスへのポインタ (shared_ptr)
	 */
	void AddRenderPass(std::shared_ptr<RenderPass> pRenderPass);

	/**
	 * @brief レンダラーコンポーネントを登録する
	 * @param pRenderer レンダラーコンポーネントへのポインタ
	 */
	void RegisterRenderer(Renderer* pRenderer);

	/**
	 * @brief レンダラーコンポーネントの登録を削除
	 * @param pRenderer レンダラーコンポーネントへのポインタ
	 */
	void UnregisterRenderer(Renderer* pRenderer);

	/**
	 * @brief カメラコンポーネントを登録する
	 * @param pCamera カメラコンポーネントへのポインタ
	 */
	void RegisterCamera(Camera* pCamera);

	/**
	 * @brief カメラコンポーネントの登録を削除
	 * @param pCamera カメラコンポーネントへのポインタ
	 */
	void UnregisterCamera(Camera* pCamera);

	/**
	 * @brief カメラのソートフラグをセットする
	 */
	void SetCameraSortDirty()
	{
		m_cateraSortDirty = true;
	}

	/**
	 * @brief アクティブかつ最も描画優先度が高いカメラを取得する
	 * @return メインカメラへのポインタ
	 */
	Camera* GetMainCamera();

	/**
	 * @brief メインライトを設定する
	 * @param pMainLight メインライトへのポインタ
	 */
	void SetMainLight(DirectionalLight* pMainLight)
	{
		m_pMainLight = pMainLight;
	}

	/**
	 * @brief メインライトを取得する
	 * @return メインライトへのポインタ
	 */
	DirectionalLight* GetMainLight()
	{
		return m_pMainLight;
	}

private:
	/// レンダーパス配列
	std::vector<std::shared_ptr<RenderPass>> m_renderPasses;

	/// 描画対象コンポーネント配列
	std::vector<Renderer*> m_pRenderers;

	/// カメラコンポーネント配列
	std::vector<Camera*> m_pCameras;

	/// メインライト
	DirectionalLight* m_pMainLight;

	/// カメラソートの必要フラグ
	bool m_cateraSortDirty;

	/**
	 * @brief カメラを描画優先度でソートする
	 */
	void CameraSort();
};
