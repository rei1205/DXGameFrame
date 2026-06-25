// Model.h
#pragma once
#include "Mesh.h"
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

	bool Load(const std::string& filePath);

	/// モデル用メッシュ構造
	struct ModelMesh
	{
		std::shared_ptr<Mesh> mesh;				// メッシュ
		int materialID;							// マテリアルID
	};

	std::vector<ModelMesh> GetMeshes()
	{
		return m_meshes;
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

	/// ノード配列
	std::vector<Node> m_nodes;

	/// メッシュ配列
	std::vector<ModelMesh> m_meshes;

	void CreateNode(const aiScene* pScene);
	int CreateMesh(const aiScene* pScene);
};
