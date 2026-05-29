// Mesh.cpp
#include "Mesh.h"
#include "../Direct3D.h"

Mesh::Mesh() :
	m_meshType(MeshType::MESH),
	m_pVtxBuffer(nullptr),
	m_pIdxBuffer(nullptr),
	m_vertexCount(0),
	m_indexCount(0),
	m_isWrite(false),
	m_topology{}
{
}

HRESULT Mesh::CreateMesh(const std::vector<MeshVertex>& vtx, const Description& desc)
{
	HRESULT hr = S_OK;

	// 頂点バッファ作成
	hr = CreateVertexBuffer(vtx.data(), sizeof(MeshVertex) * vtx.size(), desc.isWrite);
	if (FAILED(hr)) { return hr; }

	// インデックスバッファ作成
	if (!desc.idx.empty())
	{
		hr = CreateIndexBuffer(desc.idx);
		if (FAILED(hr)) { return hr; }
	}

	// 頂点・インデックス数を保持
	m_vertexCount = (UINT)vtx.size();
	m_indexCount = (UINT)desc.idx.size();

	// メッシュ情報の設定
	m_meshType = MeshType::MESH;
	m_boneIndexes = desc.boneIndexes;
	m_isWrite = desc.isWrite;
	m_topology = desc.topology;

	return hr;
}

HRESULT Mesh::CreateSkinMesh(const std::vector<SkinMeshVertex>& vtx, const Description& desc)
{
	HRESULT hr = S_OK;

	// 頂点バッファ作成
	hr = CreateVertexBuffer(vtx.data(), sizeof(SkinMeshVertex) * vtx.size(), desc.isWrite);
	if (FAILED(hr)) { return hr; }

	// インデックスバッファ作成
	if (!desc.idx.empty())
	{
		hr = CreateIndexBuffer(desc.idx);
		if (FAILED(hr)) { return hr; }
	}

	// 頂点・インデックス数を保持
	m_vertexCount = (UINT)vtx.size();
	m_indexCount = (UINT)desc.idx.size();

	// メッシュ情報の設定
	m_meshType = MeshType::SKIN_MESH;
	m_boneIndexes = desc.boneIndexes;
	m_isWrite = desc.isWrite;
	m_topology = desc.topology;

	return hr;
}

void Mesh::Draw()
{
	ID3D11DeviceContext* pContext = Direct3D::GetContext();
	UINT stride = 0;
	UINT offset = 0;
	switch (m_meshType)
	{
	case Mesh::MeshType::MESH:
		stride = sizeof(MeshVertex);
		break;

	case Mesh::MeshType::SKIN_MESH:
		stride = sizeof(SkinMeshVertex);
		break;
	}

	// 描画用情報をセット
	pContext->IASetPrimitiveTopology(m_topology);
	pContext->IASetVertexBuffers(0, 1, m_pVtxBuffer.GetAddressOf(), &stride, &offset);

	// 描画
	if (m_indexCount == 0)
	{
		// 頂点バッファのみで描画
		pContext->Draw(m_vertexCount, 0);
	}
	else
	{
		// インデックスバッファを使用して描画
		DXGI_FORMAT format = {};
		switch (sizeof(UINT))
		{
		case 2: format = DXGI_FORMAT_R16_UINT;
			break;
		case 4: format = DXGI_FORMAT_R32_UINT;
			break;
		}
		pContext->IASetIndexBuffer(m_pIdxBuffer.Get(), format, 0);
		pContext->DrawIndexed(m_indexCount, 0, 0);
	}
}

HRESULT Mesh::CreateVertexBuffer(const void* vtx, UINT vtxSize, bool isWrite)
{
	HRESULT hr = S_OK;

	// 頂点バッファの設定
	D3D11_BUFFER_DESC bufDesc = {};		// 頂点バッファ設定情報
	bufDesc.ByteWidth = vtxSize;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	// 初期化用データ設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = vtx;

	// 頂点バッファの作成
	ID3D11Device* pDevice = Direct3D::GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, m_pVtxBuffer.GetAddressOf());
	if (FAILED(hr)) { return hr; }

	return hr;
}

HRESULT Mesh::CreateIndexBuffer(const std::vector<UINT>& idx)
{
	HRESULT hr = S_OK;

	// インデックスバッファの設定
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = sizeof(UINT) * (UINT)idx.size();
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// 初期化用データ設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = idx.data();

	// インデックスバッファの作成
	ID3D11Device* pDevice = Direct3D::GetDevice();
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, m_pIdxBuffer.GetAddressOf());

	return hr;
}