// Geometry.cpp
#include "Geometry.h"

HRESULT Geometry::Init()
{
	HRESULT hr = S_OK;

	// ジオメトリ図形を作成
	hr = CreateBox();
	if (FAILED(hr)) { return hr; }
	hr = CreateCylinder();
	if (FAILED(hr)) { return hr; }
	hr = CreateSphere();
	if (FAILED(hr)) { return hr; }
	hr = CreatePlane();
	if (FAILED(hr)) { return hr; }

	return hr;
}

void Geometry::Uninit()
{
	for (int i = 0; i < Type::COUNT; ++i)
	{
		m_pMeshs[i] = nullptr;
	}
}

std::shared_ptr<Mesh> Geometry::GetModel(Type geometryType)
{
	return m_pMeshs[geometryType];
}

HRESULT Geometry::CreateBox()
{
	HRESULT hr = S_OK;

	const UINT face_count = 6;		// 面の数
	const UINT faceVtx_count = 4;	// 面の頂点数
	const UINT faceIdx_count = 6;	// 面のインデックス数
	const float h = 0.5f;			// 半分のサイズ

	struct Face
	{
		DirectX::XMFLOAT3 vtxPos[faceVtx_count];	// 頂点座標
		DirectX::XMFLOAT3 normal;					// 法線方向
	};

	//面データの作成
	Face face[face_count] = {
		{{{-h, h,-h},{ h, h,-h},{-h,-h,-h},{ h,-h,-h}},{ 0.0f, 0.0f,-1.0f}},		//-Z面
		{{{ h, h, h},{-h, h, h},{ h,-h, h},{-h,-h, h}},{ 0.0f, 0.0f, 1.0f}},		// Z面
		{{{-h, h, h},{-h, h,-h},{-h,-h, h},{-h,-h,-h}},{-1.0f, 0.0f, 0.0f}},		//-X面
		{{{ h, h,-h},{ h, h, h},{ h,-h,-h},{ h,-h, h}},{ 1.0f, 0.0f, 0.0f}},		// X面
		{{{ h,-h, h},{-h,-h, h},{ h,-h,-h},{-h,-h,-h}},{ 0.0f,-1.0f, 0.0f}},		//-Y面
		{{{-h, h, h},{ h, h, h},{-h, h,-h},{ h, h,-h}},{ 0.0f, 1.0f, 0.0f}}			// Y面
	};

	//面共通のUV座標
	DirectX::XMFLOAT2 uv[4] = {
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{0.0f, 1.0f},
		{1.0f, 1.0f},
	};

	// バッファの作成
	std::vector<Mesh::MeshVertex> meshVtx;
	Mesh::Description desc = {};
	
	//頂点データを作成
	meshVtx.resize(face_count * faceVtx_count);
	for (UINT i = 0; i < face_count; i++)
	{
		for (UINT j = 0; j < faceVtx_count; j++)
		{
			UINT index = i * faceVtx_count + j;		//配列上の位置
			meshVtx[index].pos = face[i].vtxPos[j];
			meshVtx[index].normal = face[i].normal;
			meshVtx[index].uv = uv[j];
			meshVtx[index].color = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}

	//インデックスデータを作成
	desc.idx.resize(face_count * faceIdx_count);
	for (UINT i = 0; i < face_count; i++)
	{
		UINT index = i * faceIdx_count;		//配列上の位置
		UINT offset = i * faceVtx_count;	//面ごとのインデックス番号のずれ

		desc.idx[index++] = offset;
		desc.idx[index++] = offset + 1;
		desc.idx[index++] = offset + 2;
		desc.idx[index++] = offset + 1;
		desc.idx[index++] = offset + 3;
		desc.idx[index++] = offset + 2;
	}

	//その他のデータを設定
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// メッシュを作成
	auto mesh = std::make_shared<Mesh>();
	hr = mesh->CreateMesh(meshVtx, desc);
	if (FAILED(hr)) { return hr; }

	m_pMeshs[Type::BOX] = mesh;

	return hr;
}

HRESULT Geometry::CreateCylinder()
{
	return E_NOTIMPL;
}

HRESULT Geometry::CreateSphere()
{
	return E_NOTIMPL;
}

HRESULT Geometry::CreatePlane()
{
	HRESULT hr = S_OK;

	struct Vtx
	{
		DirectX::XMFLOAT3 pos;			// 頂点座標
		DirectX::XMFLOAT2 uv;			// UV座標
	};

	Vtx vtx[4]
	{
		{{-0.5f, 0.0f,-0.5f}, {0.0f,0.0f} },
		{{-0.5f, 0.0f, 0.5f}, {0.0f,1.0f} },
		{{ 0.5f, 0.0f,-0.5f}, {1.0f,0.0f} },
		{{ 0.5f, 0.0f, 0.5f}, {1.0f,1.0f} }
	};

	int idx[6] = { 0,1,2,1,3,2 };

	// バッファの作成
	std::vector<Mesh::MeshVertex> meshVtx;
	Mesh::Description desc = {};

	//頂点データを作成
	meshVtx.resize(4);
	for (UINT i = 0; i < 4; i++)
	{
		meshVtx[i].pos = vtx[i].pos;
		meshVtx[i].normal = { 0.0f, 1.0f, 0.0f };
		meshVtx[i].uv = vtx[i].uv;
		meshVtx[i].color = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	//インデックスデータを作成
	desc.idx.resize(6);
	for (UINT i = 0; i < 6; i++)
	{
		desc.idx[i] = idx[i];
	}

	//その他のデータを設定
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// メッシュを作成
	auto mesh = std::make_shared<Mesh>();
	hr = mesh->CreateMesh(meshVtx, desc);
	if (FAILED(hr)) { return hr; }

	m_pMeshs[Type::PLANE] = mesh;

	return hr;
}
