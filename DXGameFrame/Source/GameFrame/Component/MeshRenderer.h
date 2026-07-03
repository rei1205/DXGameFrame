// MeshRenderer.h
#pragma once
#include "Renderer.h"
#include "../Core/ComponentRegisterMeta.h"
#include "../../DirectX/RenderUtility/Model.h"

REGISTER_COMPONENT(MeshRenderer);

class MeshRenderer : public Renderer
{
public:
	MeshRenderer();
	~MeshRenderer() = default;

	/**
	 * @brief 描画を行う
	 */
	void Draw() override;

	/**
	 * @brief モデルデータを読み込む
	 * @param filePath モデルファイルへのファイルパス
	 */
	void LoadModel(const std::string filePath);

	/**
	 * @brief マテリアル配列を取得する
	 * @return マテリアル配列へのポインタ
	 */
	std::vector<Material>& GetMaterials()
	{
		return m_materials;
	}

	/**
	 * @brief インスペクターでの表示
	 */
	virtual void OnInspectorGUI() override;

	/**
	 * @brief コンポーネントをシリアライズする
	 * @param jsonData 書き込み先jsonデータへの参照
	 */
	void Serialize(nlohmann::json& jsonData) override;

	/**
	 * @brief コンポーネントをデシリアライズする
	 * @param jsonData 読み込み先jsonデータへの参照
	 */
	void Deserialize(nlohmann::json& jsonData) override;

private:
	/// モデルへのポインタ
	std::shared_ptr<Model> m_pModel;

	/// マテリアル配列
	std::vector<Material> m_materials;

	/// 現在の入力中ファイルパス
	std::string m_filePath;
};
