// TestComponent.cpp
#include "TestComponent.h"
#include "GameFrame/GameObject.h"
#include "System/Debug.h"

void TestComponent::Awake()
{
	Debug::ConsoleLog("TestComponent : Awake");
}

void TestComponent::Start()
{
	Debug::ConsoleLog("TestComponent : Start");
}

void TestComponent::Update()
{
	Debug::ConsoleLog("TestComponent : Update");

	static int updateCount = 0;
	if (updateCount > 3)
	{
		GetGameObject()->Destroy();
	}
	updateCount++;
}

void TestComponent::LateUpdate()
{
	Debug::ConsoleLog("TestComponent : LateUpdate");
}

void TestComponent::OnDestroy()
{
	Debug::ConsoleLog("TestComponent : OnDestroy");
}