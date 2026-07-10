/// InspectorUtility.h
#include "InspectorUtility.h"

bool ImGui::DragVector2(const char* label, Vector2* pVector, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    float fVector[2];
    fVector[0] = pVector->x;
    fVector[1] = pVector->y;

    if (DragFloat2(label, fVector, v_speed, v_min, v_max, format, flags))
    {
        pVector->x = fVector[0];
        pVector->y = fVector[1];
        return true;
    }
    return false;
}

bool ImGui::DragVector3(const char* label, Vector3* pVector, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    float fVector[3];
    fVector[0] = pVector->x;
    fVector[1] = pVector->y;
    fVector[2] = pVector->z;

    if (DragFloat3(label, fVector, v_speed, v_min, v_max, format, flags))
    {
        pVector->x = fVector[0];
        pVector->y = fVector[1];
        pVector->z = fVector[2];
        return true;
    }
    return false;
}

bool ImGui::DragRotation(const char* label, Quaternion* pQuaternion, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    Vector3 euler = pQuaternion->ToEuler();
    if (DragVector3(label, &euler, v_speed, v_min, v_max, format, flags))
    {
        *pQuaternion = Quaternion::Euler(euler);
        return true;
    }
    return false;
}

bool ImGui::ColorPicker(const char* label, Color* pColor, ImGuiSliderFlags flags)
{
    float fColor[4] = { pColor->r, pColor->g, pColor->b, pColor->a };
    if (ImGui::ColorEdit4(label, fColor, flags))
    {
        pColor->r = fColor[0];
        pColor->g = fColor[1];
        pColor->b = fColor[2];
        pColor->a = fColor[3];
        return true;
    }
    return false;
}

bool ImGui::GetDragAssets(std::string* pOutPath)
{
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload =
            ImGui::AcceptDragDropPayload("ASSET_PATH"))
        {
            *pOutPath = (const char*)payload->Data;
        }

        ImGui::EndDragDropTarget();
        return true;
    }
    return false;
}
