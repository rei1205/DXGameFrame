// Model.h
#pragma once
#include "Mesh.h"
#include "Material.h"
#include <assimp/scene.h>
#include <string>
#include <memory>

/**
 * @brief モデルデータを扱う
 */
class Model
{
public:
	Model();
	~Model() = default;

	/**
	 * @brief モデルファイルを読み込む
	 * @param filePath モデルファイルへのファイルパス
	 * @return 成功したかを返す
	 */
	bool Load(const std::string& filePath);

	/**
	 * @brief モデルの描画を行う
	 * @param materials 描画に使用するマテリアル配列への参照
	 */
	void Draw(const std::vector<Material>& materials);

	/**
	 * @brief モデルのマテリアルを取得する
	 * @return マテリアル配列
	 */
	std::vector<Material> GetMaterials()
	{
		return m_materials;
	}

private:
	using NodeIndex = int;
	static constexpr NodeIndex NODE_NONE = -1;

	/// ノード構造
	struct Node
	{
		std::string name;						// ノード名
		NodeIndex parentID;						// 親ノードID
		std::vector<NodeIndex> childrenIDs;		// 子ノードID
		DirectX::XMMATRIX worldMatrix;			// ワールド変換行列
	};

	/// モデル用メッシュ構造
	struct ModelMesh
	{
		std::shared_ptr<Mesh> mesh;				// メッシュ
		int materialID;							// マテリアルID
	};

	/// ノード配列
	std::vector<Node> m_nodes;

	/// メッシュ配列
	std::vector<ModelMesh> m_meshes;

	/// マテリアル配列
	std::vector<Material> m_materials;

	/// 総頂点数
	int m_sumVertex;

	/**
	 * @brief モデルデータを作成する
	 * @param pScene assimpシーンへのポインタ
	 * @param directory ディレクトリパス
	 * @return 成功したかを返す
	 */
	bool CreateModelData(const aiScene* pScene, const std::string& directory);

	/**
	 * @brief ノードの親子階層を作成する
	 * @param pScene assimpシーンへのポインタ
	 */
	void CreateNode(const aiScene* pScene);

	/**
	 * @brief メッシュを作成する
	 * @param pScene assimpシーンへのポインタ
	 * @param sumVertex 総頂点数格納先のポインタ
	 * @return 成功したかを返す
	 */
	HRESULT CreateMesh(const aiScene* pScene, int* sumVertex);

	/**
	 * @brief マテリアルを作成する
	 * @directory ディレクトリパス
	 * @param pScene assimpシーンへのポインタ
	 */
	void CreateMaterial(const aiScene* pScene, const std::string& directory);
};
