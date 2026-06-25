// ImGuiManager.cpp
#include "ImGuiManager.h"
#include "ImGuiStyleSetting.h"
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

bool ImGuiManager::m_isInitialized = false;

void ImGuiManager::Init(HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
    if (m_isInitialized)
        return;

    // ImGuiコンテキスト作成
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // フォント追加
    io.Fonts->AddFontFromFileTTF(
        "Assets/keinanmaru_pop.ttf",
        14.0f,
        nullptr,
        io.Fonts->GetGlyphRangesJapanese()
    );

    // スタイル設定
    ImGuiColorSetting();
    ImGuiSizeSetting();

    // バックエンド初期化
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(pDevice, pContext);

    m_isInitialized = true;
}

void ImGuiManager::Uninit()
{
    if (!m_isInitialized)
        return;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    m_isInitialized = false;
}

void ImGuiManager::BeginFrame()
{
    if (!m_isInitialized)
        return;

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::EndFrame()
{
    if (!m_isInitialized)
        return;
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}