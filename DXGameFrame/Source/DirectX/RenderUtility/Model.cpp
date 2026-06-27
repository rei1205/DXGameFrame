// Model.cpp
#include "Model.h"
#include "../../System/Debug.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <functional>

#ifdef _DEBUG
#pragma comment(lib, "assimp/lib/Debug/assimp-vc143-mtd.lib")
#else
#pragma comment(lib, "assimp/lib/Release/assimp-vc143-mt.lib")
#endif

DirectX::XMMATRIX GetMatrixFromAssimpMatrix(aiMatrix4x4 M);

Model::Model() :
	m_sumVertex(0)
{
}

bool Model::Load(const std::string& filePath)
{
	// assimpシーン読み込み
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(
		filePath,
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices
	);
	if (pScene == nullptr)
	{
		Debug::ErrorMessage(filePath + "の読み込みに失敗しました。");
		return false;
	}

	// ディレクトリの読み取り
	std::string directory = filePath;
	auto strIt = directory.begin();
	while (strIt != directory.end()) {
		if (*strIt == '/')
			*strIt = '\\';
		++strIt;
	}
	directory = directory.substr(0, directory.find_last_of('\\') + 1);

	// モデルデータ読み込み
	if (!CreateModelData(pScene, directory))
	{
		Debug::ErrorMessage(filePath + "のモデルデータ作成に失敗しました。");
		return false;
	}

	int nodeCount = (int)m_nodes.size();
	int meshCount = (int)m_meshes.size();
	int materialCount = (int)m_materials.size();
	Debug::ConsoleLog("Load Model : " + filePath);
	Debug::ConsoleLog("- Node : " + std::to_string(nodeCount));
	Debug::ConsoleLog("- Mesh : " + std::to_string(meshCount));
	Debug::ConsoleLog("- Vertex : " + std::to_string(m_sumVertex));
	Debug::ConsoleLog("- Material : " + std::to_string(materialCount));
	return true;
}

void Model::Draw(const std::vector<Material>& materials)
{
	for (auto& mesh : m_meshes)
	{
		m_materials[mesh.materialID].Bind();
		mesh.mesh->Draw();
	}
}

bool Model::CreateModelData(const aiScene* pScene, const std::string& directory)
{
	HRESULT hr = S_OK;

	// 親子階層作成
	CreateNode(pScene);

	// メッシュ作成
	hr = CreateMesh(pScene, &m_sumVertex);
	if (FAILED(hr)) return false;

	// マテリアル作成
	CreateMaterial(pScene, directory);

	return true;
}

void Model::CreateNode(const aiScene* pScene)
{
	// 再帰処理でAssimpのノード情報を読み取り
	using FuncRecurciveMakeNodes = std::function<NodeIndex(aiNode*, NodeIndex, DirectX::XMMATRIX)>;
	FuncRecurciveMakeNodes func = [&func, this](aiNode* assimpNode, NodeIndex parent, DirectX::XMMATRIX mat)
		{
			// assimp側で階層情報が細かく分割されている場合の処理
			std::string name = assimpNode->mName.data;
			if (name.find("$AssimpFbx") != std::string::npos)
			{
				// 分割前のノードに到達するまで、各行列を掛け合わせていく
				DirectX::XMMATRIX transform = GetMatrixFromAssimpMatrix(assimpNode->mTransformation);
				mat = transform * mat;
				return func(assimpNode->mChildren[0], parent, mat);
			}

			// Assimpのノード情報を格納
			Node bone;
			bone.name = name;
			bone.parentID = parent;
			bone.childrenIDs.resize(assimpNode->mNumChildren);
			bone.worldMatrix = mat;

			// ノードの一覧に追加
			m_nodes.push_back(bone);
			NodeIndex nodeIndex = static_cast<NodeIndex>(m_nodes.size() - 1);

			// 子要素の情報を追加
			for (UINT i = 0; i < assimpNode->mNumChildren; ++i)
			{
				m_nodes[nodeIndex].childrenIDs[i] =
					func(assimpNode->mChildren[i], nodeIndex, DirectX::XMMatrixIdentity());
			}

			return nodeIndex;
		};

	// ノード作成
	func(pScene->mRootNode, NODE_NONE, DirectX::XMMatrixIdentity());
}

HRESULT Model::CreateMesh(const aiScene* pScene, int* sumVertex)
{
	HRESULT hr = S_OK;

	// 事前準備
	aiVector3D zero3(0.0f, 0.0f, 0.0f);
	aiColor4D one4(1.0f, 1.0f, 1.0f, 1.0f);
	UINT meshCount = pScene->mNumMeshes;	// メッシュ数
	*sumVertex = 0;

	// メッシュ配列のサイズ設定
	m_meshes.resize(meshCount);

	// メッシュの作成
	for (UINT i = 0; i < meshCount; ++i)
	{
		std::vector<Mesh::MeshVertex> vtx;
		Mesh::Description desc;

		// メッシュ読み込み準備
		aiMesh* pMesh = pScene->mMeshes[i];
		UINT vtxCount = pMesh->mNumVertices;
		UINT faceCount = pMesh->mNumFaces;
		*sumVertex += vtxCount;

		// 頂点・インデックス配列のサイズ設定
		vtx.resize(vtxCount);
		desc.idx.resize(faceCount * 3);		// 1ポリゴンで3インデックス

		// 頂点データの書き込み
		for (UINT j = 0; j < vtxCount; ++j)
		{
			// モデルデータから値の取得
			aiVector3D pos = pMesh->mVertices[j];
			aiVector3D normal = pMesh->HasNormals() ? pMesh->mNormals[j] : zero3;
			aiVector3D uv = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][j] : zero3;
			aiVector3D tangent = pMesh->HasTangentsAndBitangents() ? pMesh->mTangents[j] : zero3;
			aiColor4D color = pMesh->HasVertexColors(0) ? pMesh->mColors[0][j] : one4;

			// 値を設定
			vtx[j].pos = DirectX::XMFLOAT3(pos.x, pos.y, pos.z);
			vtx[j].normal = DirectX::XMFLOAT3(normal.x, normal.y, normal.z);
			vtx[j].uv = DirectX::XMFLOAT2(uv.x, uv.y);
			vtx[j].tangent = DirectX::XMFLOAT3(tangent.x, tangent.y, tangent.z);
			vtx[j].color = DirectX::XMFLOAT4(color.r, color.g, color.b, color.a);
		}

		// インデックスの書き込み
		for (UINT j = 0; j < faceCount; ++j)
		{
			// モデルデータから値の取得
			aiFace face = pScene->mMeshes[i]->mFaces[j];

			// 値を設定
			UINT idxOffset = j * 3;
			desc.idx[idxOffset + 0] = face.mIndices[0];
			desc.idx[idxOffset + 1] = face.mIndices[1];
			desc.idx[idxOffset + 2] = face.mIndices[2];
		}

		// その他の設定
		desc.isWrite = false;
		desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		// メッシュ作成
		auto mesh = std::make_shared<Mesh>();
		hr = mesh->CreateMesh(vtx, desc);
		if (FAILED(hr)) { return hr; }

		m_meshes[i].mesh = mesh;
		m_meshes[i].materialID = pMesh->mMaterialIndex;
	}

	return hr;
}

void Model::CreateMaterial(const aiScene* pScene, const std::string& directory)
{
	// マテリアル数取得
	UINT materialCount;
	materialCount = pScene->mNumMaterials;

	// マテリアル配列の初期化
	m_materials.clear();
	m_materials.resize(materialCount);

	// マテリアルパラメータの設定
	for (UINT i = 0; i < materialCount; ++i)
	{
		// テクスチャ読み込み処理
		aiString path;

		// テクスチャのパス情報を読み込み
		if (pScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) != AI_SUCCESS)
			continue;

		// テクスチャの読み込み
		m_materials[i].SetTexture(directory + path.C_Str());
	}
}

DirectX::XMMATRIX GetMatrixFromAssimpMatrix(aiMatrix4x4 M)
{
	return DirectX::XMMatrixSet(
		M.a1, M.b1, M.c1, M.d1,
		M.a2, M.b2, M.c2, M.d2,
		M.a3, M.b3, M.c3, M.d3,
		M.a4, M.b4, M.c4, M.d4
	);
}
