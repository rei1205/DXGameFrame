// TestScene.cpp
#include "TestScene.h"
#include "GameFrame/GameObject.h"
#include "TestComponent.h"
#include "GameFrame/RenderSystem/DefaultRenderPass.h"
#include "GameFrame/RenderSystem/RenderLayer.h"
#include "DirectX/RenderUtility/Geometry.h"
#include "GameFrame/Component/MeshRenderer.h"
#include "GameFrame/Component/Camera.h"
#include "GameFrame/Component/DirectionalLight.h"
#include "GameFrame/Component/Transform.h"

void TestScene::Init()
{
	Geometry::Init();
	ConstantBufferManager::Init();
	RenderLayer::Init();
	GetRenderSystem().AddRenderPass(std::make_shared<DefaultRenderPass>());

	{
		auto obj = GameObject::Create(this);
		obj->AddComponent<Camera>();
		obj->GetTransform()->SetPosition(2.0f, 3.0f, -10.0f);
		obj->GetTransform()->SetEulerAngle(0.0f, 0.0f, 0.0f);
	}

	{
		auto obj = GameObject::Create(this);
		obj->AddComponent<DirectionalLight>();
		obj->GetTransform()->SetEulerAngle(50.0f,-15.0f, 0.0f);
	}

	{
		auto obj = GameObject::Create(this);
		obj->AddComponent<TestComponent>();
		obj->AddComponent<MeshRenderer>();
	}
}
