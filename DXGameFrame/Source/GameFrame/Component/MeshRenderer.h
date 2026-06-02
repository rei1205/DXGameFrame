// MeshRenderer.h
#pragma once
#include "Renderer.h"
#include "../../DirectX/RenderUtility/Mesh.h"
#include "../../DirectX/RenderUtility/Geometry.h"

class MeshRenderer : public Renderer
{
public:
	MeshRenderer();
	~MeshRenderer() = default;

	/**
	 * @brief メッシュの描画を行う
	 * @param materialIndex 描画に使用するマテリアルのインデックス
	 */
	void Draw(UINT materialIndex) override;

	/**
	 * @brief ジオメトリのメッシュをセットする
	 * @param geometryType ジオメトリタイプ
	 */
	void SetGeometry(Geometry::Type geometryType);

private:
	std::shared_ptr<Mesh> m_pMesh;
};
