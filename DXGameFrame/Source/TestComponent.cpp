// TestComponent.cpp
#include "TestComponent.h"
#include "GameFrame/GameObject.h"
#include "System/Debug.h"
#include "DirectX/Direct3D.h"
#include "DirectX/RenderUtility/Geometry.h"
#include "DirectX/RenderUtility/Material.h"
#include "DirectX/RenderUtility/Model.h"
#include "Gameframe/Scene.h"
#include "GameFrame/Component/MeshRenderer.h"

void TestComponent::Awake()
{

}

void TestComponent::Start()
{
	Model model;
	model.Load("Assets/Tree/fbx/Tree.fbx");
	GetComponent<MeshRenderer>()->SetMesh(model.GetMeshes()[0].mesh);
}

void TestComponent::Update()
{
}

void TestComponent::LateUpdate()
{

}

void TestComponent::OnDestroy()
{

}