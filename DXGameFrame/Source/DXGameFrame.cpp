// DXGameFrame.cpp
#include "DXGameFrame.h"
#include "System/Debug.h"
#include "System/GameWindow.h"
#include "DirectX/Direct3D.h"
#include "System/ImGuiManager.h"
#include "GameFrame/SceneManager.h"
#include "System/GameTime.h"

#include "TestScene.h"

bool DXGameFrame::s_isExit = false;

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

	case WM_DESTROY:
		// スレッドの終了をシステムに伝える
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


bool DXGameFrame::Init(SetupConfig config, HINSTANCE hInstance, int nCmdShow)
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	// コンソールウィンドウ作成
	Debug::CreateConsoleWindow();

	// ウィンドウの作成
	if (!GameWindow::Create(hInstance, WndProc, config.windowStyle,
		config.title, config.clientWidth, config.clientHeight))
	{
		return false;
	}
	HWND hWnd = GameWindow::GetWindowHandle();

	// ウィンドウの表示
	GameWindow::Show(nCmdShow);

	// Direct3Dの初期化
	if (FAILED(Direct3D::Init(
		hWnd, config.clientWidth, config.clientHeight, config.fullScreen)))
	{
		return false;
	}

	// シーンマネージャーの初期化
	SceneManager::Init(std::make_unique<TestScene>());

	// ImGuiの初期化
	ImGuiManager::Init(hWnd, Direct3D::GetDevice(), Direct3D::GetContext());

	// FPS設定
	GameTime::Init(config.fps);

	return true;
}

void DXGameFrame::Uninit()
{
	ImGuiManager::Uninit();
	SceneManager::Uninit();
	Direct3D::Uninit();
}

void DXGameFrame::Run()
{
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
			GameTime::Update();
			SceneManager::Execute();
		}
	}
}

void DXGameFrame::Exit()
{
	ImGuiManager::Uninit();
	SceneManager::Uninit();
	Direct3D::Uninit();
}
