// main.cpp
#include "main.h"
#include <Windows.h>
#include <iostream>
#include <string>

#include "System/GameWindow.h"
#include "System/Debug.h"


constexpr int DefaultClientWidth = 1280;
constexpr int DefaultClientHeight = 720;

static bool g_isGameExit = false;


// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	Debug::CreateConsoleWindow();

	MSG message = {};

	// ウィンドウの作成
	DWORD windowStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	if (!GameWindow::Create(hInstance, WndProc, windowStyle,
		"Title", DefaultClientWidth, DefaultClientHeight))
	{
		return 0;
	}

	// ウィンドウの表示
	GameWindow::Show(nCmdShow);


	// メッセージループ
	while (message.message != WM_QUIT && !g_isGameExit)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			// メイン処理
		}
	}


	// 終了処理
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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

void ExitGame()
{
	g_isGameExit = true;
}
