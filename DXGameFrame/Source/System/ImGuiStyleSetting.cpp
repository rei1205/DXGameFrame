// ImGuiStyleSetting.cpp
#include "ImGuiStyleSetting.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

#define IMGUI_NONCOLOR (Col255(0, 0, 0, 0))
#define IMGUI_BACKGROUND (Col255(50, 50, 50))
#define IMGUI_BLACK (Col255(44, 54, 63))
#define IMGUI_DARKGRAY (Col255(71, 87, 102))
#define IMGUI_LIGHTGRAY (Col255(180, 180, 180))
#define IMGUI_WHITE (Col255(240, 240, 240))

#define IMGUI_RED (Col255(214, 40, 57))
#define IMGUI_BLUE (Col255(40, 175, 176))
#define IMGUI_GREEN (Col255(6, 167, 125))

#define IMGUI_MAINAREA (Alpha255(IMGUI_WHITE, 40))
#define IMGUI_ACTIVE (Alpha255(IMGUI_WHITE, 120))
#define IMGUI_HOVERED (Alpha255(IMGUI_WHITE, 80))

#define IMGUI_ERROR (Col255(255, 0, 255))

ImVec4 Col255(int r, int g, int b, int a = 255)
{
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

ImVec4 Alpha255(ImVec4 color, int a)
{
    return ImVec4(color.x, color.y, color.z, a / 255.0f);
}

void ImGuiColorSetting()
{
    ImGuiStyle& style = ImGui::GetStyle();
    for (int i = 0; i < ImGuiCol_COUNT; ++i)
    {
        style.Colors[i] = IMGUI_ERROR;
    }

    // テキスト
    style.Colors[ImGuiCol_Text] = IMGUI_WHITE;
    style.Colors[ImGuiCol_TextDisabled] = IMGUI_LIGHTGRAY;
    
    // ウィンドウ
    style.Colors[ImGuiCol_WindowBg] = IMGUI_BLACK;
    style.Colors[ImGuiCol_ChildBg] = IMGUI_NONCOLOR;
    style.Colors[ImGuiCol_PopupBg] = IMGUI_DARKGRAY;
    style.Colors[ImGuiCol_Border] = IMGUI_LIGHTGRAY;
    style.Colors[ImGuiCol_BorderShadow] = IMGUI_DARKGRAY;

    // フレーム
    style.Colors[ImGuiCol_FrameBg] = IMGUI_MAINAREA;
    style.Colors[ImGuiCol_FrameBgHovered] = IMGUI_HOVERED;
    style.Colors[ImGuiCol_FrameBgActive] = IMGUI_ACTIVE;

    // タイトル
    style.Colors[ImGuiCol_TitleBg] = IMGUI_BLACK;
    style.Colors[ImGuiCol_TitleBgActive] = IMGUI_DARKGRAY;
    style.Colors[ImGuiCol_TitleBgCollapsed] = IMGUI_BLACK;

    // メニューバー
    style.Colors[ImGuiCol_MenuBarBg] = IMGUI_DARKGRAY;

    // スクロールバー
    style.Colors[ImGuiCol_ScrollbarBg] = ImLerp(IMGUI_BLACK, IMGUI_DARKGRAY, 0.5f);
    style.Colors[ImGuiCol_ScrollbarGrab] = IMGUI_MAINAREA;
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = IMGUI_HOVERED;
    style.Colors[ImGuiCol_ScrollbarGrabActive] = IMGUI_ACTIVE;

    // チェックマーク
    //style.Colors[ImGuiCol_CheckMark] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_CheckboxSelectedBg] = IMGUI_ACTIVE;

    // スライダー
    //style.Colors[ImGuiCol_SliderGrab] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_SliderGrabActive] = IMGUI_ACTIVE;

    // ボタン
    style.Colors[ImGuiCol_Button] = IMGUI_MAINAREA;
    style.Colors[ImGuiCol_ButtonHovered] = IMGUI_HOVERED;
    style.Colors[ImGuiCol_ButtonActive] = IMGUI_ACTIVE;

    // ヘッダー
    style.Colors[ImGuiCol_Header] = IMGUI_MAINAREA;
    style.Colors[ImGuiCol_HeaderHovered] = IMGUI_HOVERED;
    style.Colors[ImGuiCol_HeaderActive] = IMGUI_ACTIVE;

    // 区切り線
    style.Colors[ImGuiCol_Separator] = IMGUI_BLUE;
    style.Colors[ImGuiCol_SeparatorHovered] = IMGUI_BLUE;
    style.Colors[ImGuiCol_SeparatorActive] = IMGUI_BLUE;
    
    // リサイズグリップ
    style.Colors[ImGuiCol_ResizeGrip] = IMGUI_BLUE;
    style.Colors[ImGuiCol_ResizeGripHovered] = IMGUI_BLUE;
    style.Colors[ImGuiCol_ResizeGripActive] = IMGUI_BLUE;

    // 入力カーソル
    style.Colors[ImGuiCol_InputTextCursor] = IMGUI_WHITE;

    // タブ
    style.Colors[ImGuiCol_TabHovered] = IMGUI_BLUE;
    style.Colors[ImGuiCol_Tab] = IMGUI_MAINAREA;
    style.Colors[ImGuiCol_TabSelected] = IMGUI_GREEN;
    style.Colors[ImGuiCol_TabSelectedOverline] = IMGUI_ACTIVE;
    style.Colors[ImGuiCol_TabDimmed] = IMGUI_MAINAREA;
    style.Colors[ImGuiCol_TabDimmedSelected] = IMGUI_HOVERED;
    style.Colors[ImGuiCol_TabDimmedSelectedOverline] = IMGUI_ACTIVE;

    // ドッキング
    style.Colors[ImGuiCol_DockingPreview] = IMGUI_ACTIVE;
    style.Colors[ImGuiCol_DockingEmptyBg] = IMGUI_BACKGROUND;

    //style.Colors[ImGuiCol_PlotLines] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_PlotLinesHovered] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_PlotHistogram] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_PlotHistogramHovered] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_TableHeaderBg] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_TableBorderStrong] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_TableBorderLight] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_TableRowBg] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_TableRowBgAlt] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_TextLink] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_TextSelectedBg] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_TreeLines] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_DragDropTarget] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_DragDropTargetBg] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_UnsavedMarker] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_NavCursor] = IMGUI_ACTIVE;
    style.Colors[ImGuiCol_NavWindowingHighlight] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_NavWindowingDimBg] = IMGUI_ACTIVE;
    //style.Colors[ImGuiCol_ModalWindowDimBg] = IMGUI_ACTIVE;
}

void ImGuiSizeSetting()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // 角丸め
    style.WindowRounding = 0.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.ChildRounding = 4.0f;

    // 枠の幅
    style.WindowBorderSize = 1.0f;
    style.DockingSeparatorSize = 1.0f;
    style.FrameBorderSize = 0.0f;
}
