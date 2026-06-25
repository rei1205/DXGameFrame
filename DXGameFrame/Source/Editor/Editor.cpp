// Editor.cpp
#include "Editor.h"
#include "HierarchyGUI.h"
#include "InspectorGUI.h"
#include "../DirectX/Direct3D.h"
#include "../GameFrame/Core/SceneManager.h"
#include "../System/ImGuiManager.h"

Scene* Editor::s_pTargetScene = nullptr;
ObjPtr<GameObject> Editor::s_pTargetGameObject = nullptr;
std::vector<std::unique_ptr<EditorWindow>> Editor::s_editorWindows;
bool Editor::s_initialized = false;

void Editor::Init()
{
	if (s_initialized)
		return;

	s_editorWindows.push_back(std::make_unique<HierarchyGUI>());
	s_editorWindows.push_back(std::make_unique<InspectorGUI>());
	s_initialized = true;
}

void Editor::Uninit()
{
	if (!s_initialized)
		return;

	s_editorWindows.clear();
	s_initialized = false;
}

void Editor::Execute()
{
	if (!s_initialized)
		return;

	Scene* pScene = SceneManager::GetActiveScene();
	if (pScene == nullptr)
		return;
	Editor::SetTargetScene(pScene);

	ImGuiManager::BeginFrame();

	float clearColor[] = { 0.4f, 0.8f, 0.8f, 1.0f };
	Direct3D::BeginDraw(clearColor);

	// エディタウィンドウ更新
	auto rtv = Direct3D::GetBackBufferRTV();
	Direct3D::GetContext()->OMSetRenderTargets(1, &rtv, nullptr);
	for (auto& window : s_editorWindows)
	{
		window->Update();
	}

	// シーンの処理
	pScene->ApplyDestroy();
	pScene->Draw();

	ImGuiManager::EndFrame();
	Direct3D::EndDraw();
}
