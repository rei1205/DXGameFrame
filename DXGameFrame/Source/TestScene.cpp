// TestScene.cpp
#include "TestScene.h"
#include "GameFrame/GameObject.h"
#include "TestComponent.h"

void TestScene::Init()
{
	auto obj = GameObject::Create();
	obj->AddComponent<TestComponent>();
}
