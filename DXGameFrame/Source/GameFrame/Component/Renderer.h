// Renderer.h
#pragma once
#include "Component.h"
#include "../../DirectX/RenderUtility/Material.h"
#include "../RenderSystem/RenderLayer.h"

/**
 * @brief 描画コンポーネントの基底クラス
 */
class Renderer : public Component
{
public:
	Renderer();
	virtual ~Renderer() = default;

	/**
	 * @brief 描画を行う
	 * @param materialIndex 描画に使用するマテリアルのインデックス
	 */
	virtual void Draw(UINT materialIndex) = 0;

	virtual void Awake();
	virtual void OnDestroy();

	/**
	 * @brief マテリアル配列を取得する
	 * @return マテリアル配列への参照
	 */
	std::vector<Material>& GetMaterials()
	{
		return m_materials;
	}

	/**
	 * @brief 描画レイヤーを設定する
	 * @param layerName 描画レイヤー名
	 */
	void SetRenderLayer(const std::string& layerName);

	/**
	 * @brief 描画レイヤーIDを取得する
	 * @return 描画レイヤーID
	 */
	int GetRenderLayerID() const
	{
		return m_renderLayerID;
	}

private:
	/// 描画レイヤーID
	int m_renderLayerID;

	/// マテリアル配列
	std::vector<Material> m_materials;
};
