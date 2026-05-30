// ConstantBufferManager.cpp
#include "ConstantBufferManager.h"
#include "../Direct3D.h"

ConstantBufferManager::FrameCB ConstantBufferManager::s_frameCB;
ComPtr<ID3D11Buffer> ConstantBufferManager::s_pWorldBuffer = nullptr;
ComPtr<ID3D11Buffer> ConstantBufferManager::s_pFrameBuffer = nullptr;
ComPtr<ID3D11Buffer> ConstantBufferManager::s_pBoneBuffer = nullptr;
ComPtr<ID3D11Buffer> ConstantBufferManager::s_pCustomBuffer = nullptr;

HRESULT ConstantBufferManager::Init()
{
	HRESULT hr = S_OK;

	DirectX::XMFLOAT4X4 identity;	// 行列初期値
	DirectX::XMStoreFloat4x4(
		&identity,
		DirectX::XMMatrixIdentity()
	);

	// 行列の初期化
	s_frameCB.view = identity;
	s_frameCB.projection = identity;

	s_frameCB.time = 0.0f;
	s_frameCB.cameraPos = { 0.0f, 0.0f, 0.0f };
	s_frameCB.lightCB = {};

	// 定数バッファを作成
	hr = CreateAllBuffer();
	if (FAILED(hr)) { return hr; }

	return hr;
}

void ConstantBufferManager::Uninit()
{
	s_pWorldBuffer.Reset();
	s_pFrameBuffer.Reset();
	s_pBoneBuffer.Reset();
	s_pCustomBuffer.Reset();
}

void ConstantBufferManager::ShaderSetBuffer()
{
	Direct3D::GetContext()->VSSetConstantBuffers((UINT)SlotNum::WORLD, 1, s_pWorldBuffer.GetAddressOf());
	Direct3D::GetContext()->PSSetConstantBuffers((UINT)SlotNum::WORLD, 1, s_pWorldBuffer.GetAddressOf());
	Direct3D::GetContext()->VSSetConstantBuffers((UINT)SlotNum::FRAME, 1, s_pFrameBuffer.GetAddressOf());
	Direct3D::GetContext()->PSSetConstantBuffers((UINT)SlotNum::FRAME, 1, s_pFrameBuffer.GetAddressOf());
	Direct3D::GetContext()->VSSetConstantBuffers((UINT)SlotNum::BONE, 1, s_pBoneBuffer.GetAddressOf());
	Direct3D::GetContext()->PSSetConstantBuffers((UINT)SlotNum::BONE, 1, s_pBoneBuffer.GetAddressOf());
	Direct3D::GetContext()->VSSetConstantBuffers((UINT)SlotNum::CUSTOM, 1, s_pCustomBuffer.GetAddressOf());
	Direct3D::GetContext()->PSSetConstantBuffers((UINT)SlotNum::CUSTOM, 1, s_pCustomBuffer.GetAddressOf());
}

void ConstantBufferManager::SetWorld(const DirectX::XMMATRIX& world)
{
	WorldCB worldCB;					// 転送用データ
	DirectX::XMMATRIX worldMat;			// 計算用ワールド行列
	DirectX::XMMATRIX invWorldMat;		// 計算用ワールド逆行列

	// ワールド行列をセット
	worldMat = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&worldCB.world, worldMat);

	// ワールド逆行列をセット
	invWorldMat = DirectX::XMMatrixInverse(nullptr, world);
	invWorldMat = DirectX::XMMatrixTranspose(invWorldMat);
	DirectX::XMStoreFloat4x4(&worldCB.invWorld, invWorldMat);

	// 定数バッファを更新
	Direct3D::GetContext()->UpdateSubresource(s_pWorldBuffer.Get(), 0, nullptr, &worldCB, 0, 0);
}

void ConstantBufferManager::SetView(const DirectX::XMMATRIX& view)
{
	DirectX::XMMATRIX viewMat;			// 計算用ビュー行列
	DirectX::XMMATRIX invViewMat;		// 計算用ビュー逆行列

	// ビュー行列をセット
	viewMat = DirectX::XMMatrixTranspose(view);
	DirectX::XMStoreFloat4x4(&s_frameCB.view, viewMat);

	// カメラ座標をセット
	invViewMat = DirectX::XMMatrixInverse(nullptr, view);
	s_frameCB.cameraPos.x = DirectX::XMVectorGetX(invViewMat.r[3]);
	s_frameCB.cameraPos.y = DirectX::XMVectorGetY(invViewMat.r[3]);
	s_frameCB.cameraPos.z = DirectX::XMVectorGetZ(invViewMat.r[3]);
}

void ConstantBufferManager::SetProjection(const DirectX::XMMATRIX& projection)
{
	// プロジェクション行列をセット
	DirectX::XMStoreFloat4x4(
		&s_frameCB.projection,
		DirectX::XMMatrixTranspose(projection)
	);
}

void ConstantBufferManager::SetLight(const DirectionalLightCB& light)
{
	// ライト定数バッファをセット
	s_frameCB.lightCB = light;
}

void ConstantBufferManager::SetTime(float time)
{
	s_frameCB.time = time;
}

void ConstantBufferManager::SetBone(DirectX::XMFLOAT4X4 bones[MaxBone])
{
	// ボーン定数バッファの更新
	Direct3D::GetContext()->UpdateSubresource(s_pBoneBuffer.Get(), 0, nullptr, bones, 0, 0);
}

void ConstantBufferManager::SetCustomData(const std::vector<BYTE>& data)
{
	if (data.size() == 0 || data.size() > CustomCBSize)
		return;

	// 固定長配列にデータコピー
	BYTE customData[CustomCBSize] = {};
	size_t dataSize = (size_t)(sizeof(BYTE) * data.size());
	memcpy(customData, data.data(), dataSize);

	// カスタム定数バッファの更新
	Direct3D::GetContext()->UpdateSubresource(s_pCustomBuffer.Get(), 0, nullptr, customData, 0, 0);
}

void ConstantBufferManager::UpdateFrameCB()
{
	// フレーム更新定数バッファの更新
	Direct3D::GetContext()->UpdateSubresource(s_pFrameBuffer.Get(), 0, nullptr, &s_frameCB, 0, 0);
}

HRESULT ConstantBufferManager::CreateAllBuffer()
{
	HRESULT hr = S_OK;

	for (int i = 0; i < (UINT)SlotNum::COUNT; ++i)
	{
		// 定数バッファの設定
		D3D11_BUFFER_DESC cbDesc = {};
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;

		// 定数バッファを作成する
		switch ((SlotNum)i)
		{
		case ConstantBufferManager::SlotNum::WORLD:
			// WVP定数バッファの作成
			cbDesc.ByteWidth = sizeof(WorldCB);
			hr = Direct3D::GetDevice()->CreateBuffer(&cbDesc, nullptr, s_pWorldBuffer.GetAddressOf());
			break;

		case ConstantBufferManager::SlotNum::FRAME:
			// フレーム更新定数バッファの作成
			cbDesc.ByteWidth = sizeof(FrameCB);
			hr = Direct3D::GetDevice()->CreateBuffer(&cbDesc, nullptr, s_pFrameBuffer.GetAddressOf());
			break;

		case ConstantBufferManager::SlotNum::BONE:
			// ボーン定数バッファの作成
			cbDesc.ByteWidth = sizeof(BoneCB);
			hr = Direct3D::GetDevice()->CreateBuffer(&cbDesc, nullptr, s_pBoneBuffer.GetAddressOf());
			break;

		case ConstantBufferManager::SlotNum::CUSTOM:
			// カスタム定数バッファの作成
			cbDesc.ByteWidth = sizeof(CustomCB);
			hr = Direct3D::GetDevice()->CreateBuffer(&cbDesc, nullptr, s_pCustomBuffer.GetAddressOf());
			break;
		}
		if (FAILED(hr)) { return hr; }
	}

	return hr;
}
