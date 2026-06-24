// InspectorUtility.h
#pragma once
#include <ImGui/imgui.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace ImGui
{
	bool DragVector2(const char* label, Vector2* pVector,
		float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	bool DragVector3(const char* label, Vector3* pVector,
		float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	bool DragRotation(const char* label, Quaternion* pQuaternion,
		float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0);
}
