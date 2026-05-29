// TestComponent.cpp
#include "TestComponent.h"
#include "GameFrame/GameObject.h"
#include "System/Debug.h"
#include "DirectX/Manager/ShaderManager.h"
#include "DirectX/Direct3D.h"
#include "DirectX/RenderUtility/Geometry.h"

void TestComponent::Awake()
{

}

void TestComponent::Start()
{
	auto vs = ShaderManager::LoadVertexShader("output/x64/Debug/VS_Test.cso");
	auto ps = ShaderManager::LoadPixelShader("output/x64/Debug/PS_Test.cso");
	ShaderManager::SetVertexShader(vs.get());
	ShaderManager::SetPixelShader(ps.get());

	DirectX::XMMATRIX wvp[3];
	wvp[0] = DirectX::XMMatrixTranslation(3.0f, 3.0f, 0.0f);
	wvp[1] = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	);
	wvp[2] = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f
	);

	for (int i = 0; i < 3; ++i)
	{
		wvp[i] = DirectX::XMMatrixTranspose(wvp[i]);
	}

	D3D11_BUFFER_DESC cbDesc = {};
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	static ComPtr<ID3D11Buffer> buffer;
	cbDesc.ByteWidth = sizeof(DirectX::XMMATRIX) * 3;
	Direct3D::GetDevice()->CreateBuffer(&cbDesc, nullptr, buffer.GetAddressOf());
	Direct3D::GetContext()->UpdateSubresource(buffer.Get(), 0, nullptr, wvp, 0, 0);
	Direct3D::GetContext()->VSSetConstantBuffers(0, 1, buffer.GetAddressOf());
	auto rtv = Direct3D::GetBackBufferRTV();
	Direct3D::GetContext()->OMSetRenderTargets(1, &rtv, nullptr);
	Geometry::Init();
}

void TestComponent::Update()
{
	float clearColor[] = { 0.4f, 0.8f, 0.8f, 1.0f };
	Direct3D::BeginDraw(clearColor);
	Geometry::GetModel(Geometry::Type::BOX)->Draw();
	Direct3D::EndDraw();
}

void TestComponent::LateUpdate()
{

}

void TestComponent::OnDestroy()
{

}