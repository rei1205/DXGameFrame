// TestScene.cpp
#include "TestScene.h"
#include "GameFrame/GameObject.h"
#include "TestComponent.h"

void TestScene::Init()
{
	for (int i = 0; i < 10000; ++i)
	{
		auto obj = GameObject::Create(this);
	}
}
