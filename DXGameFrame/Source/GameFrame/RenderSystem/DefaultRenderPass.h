// DefaultRenderPass.h
#pragma once
#include "RenderPass.h"

class DefaultRenderPass : public RenderPass
{
public:
	DefaultRenderPass() = default;
	~DefaultRenderPass() = default;

	/**
	 * @brief 描画を行う
	 * @param renderObjects 描画コンポーネント配列
	 * @param renderContext 描画関連データ
	 */
	void Render(const std::vector<Renderer*>& renderers,
		const RenderContext& renderContext) override;

private:
	/**
	 * @brief レンダーターゲットを設定する
	 * @param renderContext	描画関連データ
	 */
	void SetRenderTarget(const RenderContext& renderContext);

	/**
	 * @brief フレーム定数バッファを更新する
	 * 	 * @param renderContext	描画関連データ
	 */
	void UpdateFrameCB(const RenderContext& renderContext);
};
