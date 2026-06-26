// EditorWindow.cpp
#include "EditorWindow.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_internal.h>

EditorWindow::EditorWindow(const std::string& windowName) :
	m_windowName(windowName),
	m_openFlag(true)
{
}

void EditorWindow::Update()
{
	if (!m_openFlag)
		return;

	// ドッキング中はウィンドウのXボタンを消す
	ImGuiWindowClass wc;
	wc.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoCloseButton;
	ImGui::SetNextWindowClass(&wc);

	ImGui::Begin(m_windowName.c_str(), &m_openFlag);
	OnGUI();
	ImGui::End();
}
