// Renderer.h
#pragma once
#include "Component.h"
#include "../../DirectX/RenderUtility/Material.h"

/**
 * @brief 描画コンポーネントの基底クラス
 */
class Renderer : public Component
{
public:
	Renderer() = default;
	~Renderer() = default;

	/**
	 * @brief 描画を行う
	 */
	virtual void Draw();

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

private:
	/// マテリアル配列
	std::vector<Material> m_materials;
};
