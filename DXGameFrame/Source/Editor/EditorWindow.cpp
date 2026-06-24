// EditorWindow.cpp
#include "EditorWindow.h"
#include <ImGui/imgui.h>

EditorWindow::EditorWindow(const std::string& windowName) :
	m_windowName(windowName),
	m_openFlag(true)
{
}

void EditorWindow::Update()
{
	if (!m_openFlag)
		return;

	ImGui::Begin(m_windowName.c_str(), &m_openFlag);
	OnGUI();
	ImGui::End();
}
