// RenderPass.h
#pragma once
#include "../Component/Renderer.h"
#include "../Component/Camera.h"

/// 描画オブジェクト
struct RenderObject
{
	Renderer* pRenderer;		// 描画コンポーネントへのポインタ
	UINT materialIndex;			// 描画に使用するマテリアルのインデックス
};

/// 描画関連データ
struct RenderContext
{
	Camera* pCamera;			// 描画に使用するカメラへのポインタ
};

/**
 * @brief 描画パスの基底クラス
 */
class RenderPass
{
public:
	RenderPass();
	~RenderPass() = default;

	/**
	 * @brief 描画を行う
	 * @param renderObjects 描画オブジェクト配列
	 * @param renderContext 描画関連データ
	 */
	virtual void Render(const std::vector<RenderObject>& renderObjects,
		const RenderContext& renderContext) = 0;

	/**
	 * @brief レンダーパスの初期化
	 */
	virtual void Init() {}

	/**
	 * @brief 終了処理
	 */
	virtual void Uninit() {}

	/**
	 * @brief 描画対象レイヤーを設定する
	 * @param layerName レイヤー名
	 */
	void SetTargetRenderLayer(const std::string& layerName);

	/**
	 * @brief 描画対象レイヤーIDを取得する
	 * @return レイヤーID
	 */
	int GetTargetRenderLayerID()
	{
		return m_targetRenderLayerID;
	}

private:
	/// 描画対象のレイヤーID
	int m_targetRenderLayerID;
};
