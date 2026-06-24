// ImGuiManager.cpp
#include "ImGuiManager.h"
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
    ImGui::StyleColorsDark();

    // バックエンド初期化
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(pDevice, pContext);

    // スタイル変更
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.50f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.35f, 0.35f, 0.40f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.45f, 0.45f, 0.45f, 0.60f);
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

    DrawDockSpace();
}

void ImGuiManager::EndFrame()
{
    if (!m_isInitialized)
        return;
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::DrawDockSpace()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("DockSpaceRoot", nullptr, windowFlags);

    ImGuiID dockspaceID = ImGui::GetID("MainDockSpace");
    ImGui::DockSpace(dockspaceID);

    ImGui::End();
}