// RenderPass.h
#pragma once
#include <Windows.h>
#include <vector>
#include <string>

class Renderer;

/// 描画オブジェクト
struct RenderObject
{
	Renderer* pRenderer;		// 描画コンポーネントへのポインタ
	UINT materialIndex;			// 描画に使用するマテリアルのインデックス
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
	 */
	virtual void Render(const std::vector<RenderObject>& renderObjects) = 0;

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
