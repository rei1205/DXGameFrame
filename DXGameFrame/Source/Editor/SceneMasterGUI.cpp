// SceneMasterGUI.cpp
#include "SceneMasterGUI.h"
#include "Editor.h"
#include "../GameFrame/Core/SceneManager.h"
#include "../Utility/InspectorUtility.h"
#include "../System/ProjectData.h"
#include <ImGui/imgui.h>

SceneMasterGUI::SceneMasterGUI():
	EditorWindow("シーン設定")
{
}

void SceneMasterGUI::OnGUI()
{
	ImGui::Text("CurrentScene");
	ImGui::Text(SceneManager::GetCurrentSceneFilePath().c_str());
	if (ImGui::Button("Save Scene"))
	{
		Editor::SceneSerialize(SceneManager::GetCurrentSceneFilePath());
	}
	ImGui::Dummy(ImVec2(0.0f, 5.0f));

	// シーンパス入力欄
	static char buffer[256] = {};
	strncpy_s(buffer, sizeof(buffer), m_inputScenePath.c_str(), _TRUNCATE);
	ImGui::InputTextWithHint("FilePath", "path...", buffer, sizeof(buffer));
	m_inputScenePath = buffer;
	ImGui::GetDragAssets(&m_inputScenePath);
	if (ImGui::Button("Load Scene"))
	{
		Editor::SceneDeserialize(m_inputScenePath);
	}
}
