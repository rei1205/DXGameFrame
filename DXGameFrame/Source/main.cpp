// main.cpp
#include "main.h"
#include <Windows.h>
#include <iostream>
#include <string>

#include "System/GameWindow.h"
#include "System/Debug.h"
#include "System/GameTime.h"


constexpr int DefaultClientWidth = 1280;
constexpr int DefaultClientHeight = 720;
constexpr int DefaultFPS = 60;

static bool g_isGameExit = false;


// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void ShowProssingTime();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	// コンソールウィンドウ作成
	Debug::CreateConsoleWindow();

	// ウィンドウの作成
	DWORD windowStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	if (!GameWindow::Create(hInstance, WndProc, windowStyle,
		"Title", DefaultClientWidth, DefaultClientHeight))
	{
		return 0;
	}

	// ウィンドウの表示
	GameWindow::Show(nCmdShow);

	// FPS設定
	GameTime::Init(DefaultFPS);


	// メッセージループ
	MSG message = {};
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

			// FPS固定
			GameTime::Update();

			ShowProssingTime();
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

void ShowProssingTime()
{
	const int showIntervalFrame = 180;
	static int frameCount = 0;
	static float sumProssingTime = 0.0f;

	frameCount++;
	sumProssingTime += GameTime::GetProssingTime() * 1000.0f;

	if (frameCount >= showIntervalFrame)
	{
		float avgTime = sumProssingTime / (float)showIntervalFrame;
		Debug::ConsoleLog(std::to_string(avgTime) + "ms");

		frameCount = 0;
		sumProssingTime = 0.0f;
	}
}

void ExitGame()
{
	g_isGameExit = true;
}
