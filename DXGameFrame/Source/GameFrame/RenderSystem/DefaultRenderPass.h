// DefaultRenderPass.h
#pragma once
#include "RenderPass.h"

class DefaultRenderPass : public RenderPass
{
public:
	DefaultRenderPass();
	~DefaultRenderPass() = default;

	/**
	 * @brief 描画を行う
	 * @param renderObjects 描画オブジェクト配列
	 * @param renderContext 描画関連データ
	 */
	void Render(const std::vector<RenderObject>& renderObjects, 
		const RenderContext& renderContext) override;

private:
	/**
	 * @brief フレーム定数バッファを更新する
	 */
	void UpdateFrameCB(const RenderContext& renderContext);
};
