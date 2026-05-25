// TestComponent.cpp
#pragma once
#include "GameFrame/Component.h"

class TestComponent : public Component
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void OnDestroy();
};
