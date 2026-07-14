// DXGameFrame.cpp
#include "DXGameFrame.h"
#include "System/Debug.h"
#include "System/ProjectData.h"
#include "System/GameWindow.h"
#include "DirectX/Direct3D.h"
#include "System/ImGuiManager.h"
#include "GameFrame/Core/SceneManager.h"
#include "Editor/Editor.h"
#include "System/GameTime.h"
#include "Utility/Input.h"
#include <Windows.h>

bool DXGameFrame::s_isInitialized = false;
bool DXGameFrame::s_isExit = false;
bool DXGameFrame::s_isEditorMode = false;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_CLOSE:
		break;

	case WM_SIZE:
	{
		// リサイズ処理
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		Direct3D::OnResize(width, height);
		ImGuiManager::OnResize(width, height);
		break;
	}

	case WM_DESTROY:
		// スレッドの終了をシステムに伝える
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool DXGameFrame::InitGame(HINSTANCE hInstance, int nCmdShow)
{
	if (s_isInitialized)
		return false;

	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	// プロジェクトデータの読み込み
	if (!ProjectData::Load())
	{
		Debug::ConsoleLog("Failed : Load Project Data.");
	}

	// ウィンドゥスタイル設定
	UINT windowStyle;
	if (ProjectData::IsFullScreen())
	{
		// フルスクリーン
		windowStyle =
			WS_OVERLAPPED;
	}
	else
	{
		// ウィンドウ
		windowStyle =
			WS_OVERLAPPED |
			WS_CAPTION |
			WS_SYSMENU |
			WS_MINIMIZEBOX;
	}

	// ウィンドウの作成
	if (!GameWindow::Create(hInstance, WndProc, windowStyle,
		ProjectData::GetProjectName(), ProjectData::GetScreenWidth(), ProjectData::GetScreenHeight()))
	{
		return false;
	}
	HWND hWnd = GameWindow::GetWindowHandle();

	// Direct3Dの初期化
	if (FAILED(Direct3D::Init(hWnd, 
		ProjectData::GetScreenWidth(), ProjectData::GetScreenHeight(), ProjectData::IsFullScreen())))
	{
		return false;
	}

	// ImGuiの初期化
	ImGuiManager::Init(hWnd, Direct3D::GetDevice(), Direct3D::GetContext());

	// シーンマネージャーの初期化
	SceneManager::Init();

	// 入力初期化
	Input::Init();

	// FPS設定
	GameTime::Init(ProjectData::GetFPS());

	s_isInitialized = true;
	s_isEditorMode = false;

	// 初期化後の処理
	GameWindow::Show(nCmdShow);
	SceneManager::DeserializeScene(ProjectData::GetStartScenePath());

	return true;
}

bool DXGameFrame::InitEditor(HINSTANCE hInstance, int nCmdShow)
{
	if (s_isInitialized)
		return false;

	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	// デバッグ用コンソールウィンドウの作成
	Debug::CreateConsoleWindow();

	// プロジェクトデータの読み込み
	if (!ProjectData::Load())
	{
		Debug::ConsoleLog("Failed : Load Project Data.");
	}

	// ウィンドゥスタイル設定
	UINT windowStyle =
		WS_OVERLAPPED |
		WS_CAPTION |
		WS_SYSMENU |
		WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX;

	// ウィンドウの作成
	if (!GameWindow::Create(hInstance, WndProc, windowStyle,
		"DXGameFrame " + ProjectData::GetProjectName(), 
		ProjectData::GetScreenWidth(), ProjectData::GetScreenHeight()))
	{
		return false;
	}
	HWND hWnd = GameWindow::GetWindowHandle();

	// Direct3Dの初期化
	if (FAILED(Direct3D::Init(hWnd,
		ProjectData::GetScreenWidth(), ProjectData::GetScreenHeight(), ProjectData::IsFullScreen())))
	{
		return false;
	}

	// ImGuiの初期化
	ImGuiManager::Init(hWnd, Direct3D::GetDevice(), Direct3D::GetContext());

	// シーンマネージャーの初期化
	SceneManager::Init();

	// エディタの初期化
	Editor::Init();

	// 入力初期化
	Input::Init();

	// FPS設定
	GameTime::Init(ProjectData::GetFPS());

	s_isInitialized = true;
	s_isEditorMode = true;

	// 初期化後の処理
	GameWindow::Show(SW_MAXIMIZE);
	SceneManager::DeserializeScene(ProjectData::GetEditorScenePath());

	return true;
}

void DXGameFrame::Uninit()
{
	if (!s_isInitialized)
		return;

	Editor::Uninit();
	SceneManager::Uninit();
	ImGuiManager::Uninit();
	Direct3D::Uninit();

	ProjectData::Save();

	s_isInitialized = false;
}

void DXGameFrame::Run()
{
	if (!s_isInitialized)
		return;

	// メッセージループ
	MSG message = {};

	while (message.message != WM_QUIT && !s_isExit)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			// メイン処理
			Input::Update();
			GameTime::Update();
			if (s_isEditorMode)
			{
				Editor::Execute();
			}
			else
			{
				SceneManager::Execute();
			}
		}
	}
}

void DXGameFrame::Exit()
{
	if (!s_isInitialized)
		return;

	s_isExit = true;
}
