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
	RootWindowGUI();
	for (auto& window : s_editorWindows)
	{
		window->Update();
	}

	// シーンの処理
	pScene->ApplyDestroy();
	pScene->Draw();

	auto rtv = Direct3D::GetBackBufferRTV();
	Direct3D::GetContext()->OMSetRenderTargets(1, &rtv, nullptr);
	ImGuiManager::EndFrame();
	Direct3D::EndDraw();
}

void Editor::RootWindowGUI()
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGuiStyle& style = ImGui::GetStyle();

	// スタイル設定
	ImGui::PushStyleColor(ImGuiCol_WindowBg, style.Colors[ImGuiCol_DockingEmptyBg]);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));

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
		ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_MenuBar;

	// ルートウィンドウ作成
	ImGui::Begin("DockSpaceRoot", nullptr, windowFlags);

	// メニューバー
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("ウィンドウ"))
		{
			for (auto& window : s_editorWindows)
			{
				bool isOpen = window->IsOpen();
				if (ImGui::MenuItem(window->GetWindowName().c_str(), nullptr, isOpen))
				{
					isOpen ? window->CloseWindow() : window->OpenWindow();
				}
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGuiID dockspaceID = ImGui::GetID("MainDockSpace");
	ImGui::DockSpace(dockspaceID);

	ImGui::End();

	ImGui::PopStyleVar(3);
	ImGui::PopStyleColor();
}
