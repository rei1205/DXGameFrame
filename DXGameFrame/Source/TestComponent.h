// TestComponent.h
#pragma once
#include "GameFrame/Core/Component.h"
#include "GameFrame/Core/ComponentRegisterMeta.h"

REGISTER_COMPONENT(TestComponent);

class TestComponent : public Component
{
public:
	void Update() override;
};
