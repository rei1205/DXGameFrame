// Mesh.h
#pragma once
#include <vector>
#include "../DirectXInclude.h"

/**
 * @brief メッシュ情報を扱う
 */
class Mesh
{
public:
	Mesh();
	~Mesh() = default;

	/// メッシュの種類
	enum class MeshType
	{
		MESH,
		SKIN_MESH
	};

	/// メッシュ頂点情報
	struct MeshVertex
	{
		DirectX::XMFLOAT3 pos;			// 座標
		DirectX::XMFLOAT3 normal;		// 法線
		DirectX::XMFLOAT2 uv;			// UV座標
		DirectX::XMFLOAT4 color;		// 頂点カラー
	};

	/// スキンメッシュ頂点情報
	struct SkinMeshVertex
	{
		DirectX::XMFLOAT3 pos;			// 座標
		DirectX::XMFLOAT3 normal;		// 法線
		DirectX::XMFLOAT2 uv;			// UV座標
		DirectX::XMFLOAT4 color;		// 頂点カラー
		float weight[4];				// ボーンへのウェイト
		UINT index[4];					// 対応するボーンへのインデックス
	};

	/// メッシュ情報
	struct Description
	{
		std::vector<UINT> idx;				// インデックス配列
		std::vector<UINT> boneIndexes;		// 対応ボーンインデックス配列
		bool isWrite;						// 動的な頂点の書き換え可能フラグ
		D3D11_PRIMITIVE_TOPOLOGY topology;	// トポロジー設定
	};

	/**
	 * @brief メッシュを作成する
	 * @param vtx 頂点配列
	 * @param desc メッシュ情報
	 * @return 成功したかを返す
	 */
	HRESULT CreateMesh(const std::vector<MeshVertex>& vtx, const Description& desc);

	/**
	 * @brief スキンメッシュを作成する
	 * @param vtx 頂点配列
	 * @param desc メッシュ情報
	 * @return 成功したかを返す
	 */
	HRESULT CreateSkinMesh(const std::vector<SkinMeshVertex>& vtx, const Description& desc);

	/**
	 * @brief メッシュを描画する
	 */
	void Draw();

private:
	/// メッシュの種類
	MeshType m_meshType;

	/// 頂点バッファ
	ComPtr<ID3D11Buffer> m_pVtxBuffer;

	/// インデックスバッファ
	ComPtr<ID3D11Buffer> m_pIdxBuffer;

	/// 頂点数
	UINT m_vertexCount;

	/// インデックス数
	UINT m_indexCount;

	/// 対応ボーンのインデックス配列
	std::vector<UINT> m_boneIndexes;

	/// 動的な頂点の書き換え可能フラグ
	bool m_isWrite;

	/// トポロジー設定
	D3D11_PRIMITIVE_TOPOLOGY m_topology;

	/**
	 * @brief 頂点バッファを作成する
	 * @param vtx 頂点配列の先頭ポインタ
	 * @param vtxSize 頂点配列のメモリサイズ
	 * @param isWrite 書き込み可能フラグ
	 * @return 成功したかを返す
	 */
	HRESULT CreateVertexBuffer(const void* vtx, UINT vtxSize, bool isWrite);

	/**
	 * @brief インデックスバッファを作成する
	 * @param pIdx インデックス配列
	 * @return 成功したかを返す
	 */
	HRESULT CreateIndexBuffer(const std::vector<UINT>& idx);
};
