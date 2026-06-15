// Editor.cpp
#include "Editor.h"
#include "HierarchyGUI.h"

Scene* Editor::s_pTargetScene = nullptr;
ObjPtr<GameObject> Editor::s_pTargetGameObject = nullptr;
std::vector<std::unique_ptr<EditorWindow>> Editor::s_editorWindows;
bool Editor::s_initialized = false;

void Editor::Init()
{
	if (s_initialized)
		return;

	s_editorWindows.push_back(std::make_unique<HierarchyGUI>());
	s_initialized = true;
}

void Editor::Uninit()
{
	if (!s_initialized)
		return;

	s_editorWindows.clear();
	s_initialized = false;
}

void Editor::Draw()
{
	if (!s_initialized)
		return;

	for (auto& window : s_editorWindows)
	{
		window->DrawWindow();
	}
}
