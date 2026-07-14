// TestComponent.cpp
#include "TestComponent.h"
#include "GameFrame/Component/Transform.h"
#include "System/GameTime.h"
#include "Utility/Input.h"

void TestComponent::Update()
{
	Vector2 input = Input::GetLeftStick();
	if (Input::GetKeyHold(KeyCode::A))
	{
		input.x -= 1.0f;
	}
	if (Input::GetKeyHold(KeyCode::D))
	{
		input.x += 1.0f;
	}
	if (Input::GetKeyHold(KeyCode::S))
	{
		input.y -= 1.0f;
	}
	if (Input::GetKeyHold(KeyCode::W))
	{
		input.y += 1.0f;
	}

	Vector3 move = Vector3(input.x, 0.0f, input.y);
	GetTransform()->Translate(move * 3.0f * GameTime::GetDeltaTime());
}
