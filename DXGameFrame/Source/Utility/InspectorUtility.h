// InspectorUtility.h
#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Color.h"
#include <string>
#include <ImGui/imgui.h>

namespace ImGui
{
	/**
	 * @brief Vector2のドラッグGUI
	 */
	bool DragVector2(const char* label, Vector2* pVector,
		float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	/**
	 * @brief Vector3のドラッグGUI
	 */
	bool DragVector3(const char* label, Vector3* pVector,
		float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	/**
	 * @brief RotationのドラッグGUI
	 */
	bool DragRotation(const char* label, Quaternion* pQuaternion,
		float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0);

	/**
	 * @brief カラーピッカーGUI
	 */
	bool ColorPicker(const char* label, Color* pColor, ImGuiSliderFlags flags = 0);

	bool GetDragAssets(std::string* pOutPath);
}
