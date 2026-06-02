// TestComponent.cpp
#include "TestComponent.h"
#include "GameFrame/GameObject.h"
#include "System/Debug.h"
#include "DirectX/Direct3D.h"
#include "DirectX/RenderUtility/Geometry.h"
#include "DirectX/RenderUtility/Material.h"

void TestComponent::Awake()
{

}

void TestComponent::Start()
{
	//ConstantBufferManager::Init();

	//DirectX::XMMATRIX world = DirectX::XMMatrixTranslation(3.0f, -3.0f, 0.0f);
	//DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(
	//	DirectX::XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f),
	//	DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
	//	DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	//);
	//DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(
	//	DirectX::XMConvertToRadians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f
	//);

	//DirectionalLightCB lightCB = {};
	//lightCB.lightDir = { 0.0f, -1.0f, 0.5f };
	//ConstantBufferManager::SetLight(lightCB);

	//ConstantBufferManager::ShaderSetBuffer();
	//ConstantBufferManager::SetWorld(world);
	//ConstantBufferManager::SetView(view);
	//ConstantBufferManager::SetProjection(projection);
	//ConstantBufferManager::UpdateFrameCB();

	//Material material;
	//material.SetTexture("Assets/TestImage.png", TextureSlot::Main);
	//material.SetVertexShader("output/x64/Debug/VS_Test.cso");
	//material.SetPixelShader("output/x64/Debug/PS_Test.cso");
	//material.Bind();

	//auto rtv = Direct3D::GetBackBufferRTV();
	//Direct3D::GetContext()->OMSetRenderTargets(1, &rtv, nullptr);
}

void TestComponent::Update()
{
	//float clearColor[] = { 0.4f, 0.8f, 0.8f, 1.0f };
	//Direct3D::BeginDraw(clearColor);
	//Geometry::GetModel(Geometry::Type::PLANE)->Draw();
	//Direct3D::EndDraw();
}

void TestComponent::LateUpdate()
{

}

void TestComponent::OnDestroy()
{

}