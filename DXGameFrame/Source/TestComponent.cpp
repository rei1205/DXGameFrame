// TestComponent.cpp
#include "TestComponent.h"
#include "GameFrame/GameObject.h"
#include "System/Debug.h"
#include "DirectX/Manager/ShaderManager.h"
#include "DirectX/Direct3D.h"
#include "DirectX/RenderUtility/Geometry.h"
#include "DirectX/Manager/ConstantBufferManager.h"
#include "DirectX/Manager/TextureManager.h"

void TestComponent::Awake()
{

}

void TestComponent::Start()
{
	auto tex = TextureManager::LoadTexture("Assets/TestImage.png");

	auto vs = ShaderManager::LoadVertexShader("output/x64/Debug/VS_Test.cso");
	auto ps = ShaderManager::LoadPixelShader("output/x64/Debug/PS_Test.cso");
	ShaderManager::SetVertexShader(vs.get());
	ShaderManager::SetPixelShader(ps.get());

	ConstantBufferManager::Init();

	DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(3.0f, -3.0f, 0.0f);
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	);
	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f
	);

	DirectionalLightCB lightCB = {};
	lightCB.lightDir = { 0.0f, -1.0f, 0.5f };
	ConstantBufferManager::SetLight(lightCB);

	ConstantBufferManager::ShaderSetBuffer();
	ConstantBufferManager::SetWorld(world);
	ConstantBufferManager::SetView(view);
	ConstantBufferManager::SetProjection(projection);
	ConstantBufferManager::UpdateFrameCB();

	D3D11_BUFFER_DESC cbDesc = {};
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

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