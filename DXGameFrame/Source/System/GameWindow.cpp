// GameWindow.cpp
#include "GameWindow.h"
#include "Debug.h"

HWND GameWindow::s_hWnd = nullptr;
UINT GameWindow::s_windowStyle;
GameWindow::Size GameWindow::s_clientSize;
GameWindow::Size GameWindow::s_windowSize;

bool GameWindow::Create(HINSTANCE hInstance, WNDPROC wndProc, UINT windowStyle,
	const std::string& title, UINT clientWidth, UINT clientHeight)
{
	// ウィンドウクラス情報を設定
	WNDCLASSEX wcex = {};
	wcex.hInstance = hInstance;									// インスタンスハンドル
	wcex.lpszClassName = "Class Name";							// ウィンドウクラス名
	wcex.lpfnWndProc = wndProc;									// ウィンドウプロシージャへのポインタ
	wcex.style = CS_HREDRAW | CS_VREDRAW;						// ウィンドウの挙動
	wcex.cbSize = sizeof(WNDCLASSEX);							// 構造体のサイズ
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// アプリアイコン
	wcex.hIconSm = wcex.hIcon;									// アプリアイコン(小)
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);					// カーソルアイコン
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 背景の色

	// ウィンドウクラス情報の登録
	if (!RegisterClassEx(&wcex))
	{
		Debug::ErrorMessage("ウィンドウクラスの登録に失敗しました");
		return false;
	}

	// ウィンドウサイズを求める
	s_clientSize.width = clientWidth;
	s_clientSize.height = clientHeight;
	s_windowStyle = windowStyle;
	s_windowSize = AdjustWindowSize(clientWidth, clientHeight, windowStyle);

	// ウィンドウの作成
	s_hWnd = CreateWindowExA(
		WS_EX_OVERLAPPEDWINDOW,						// ウィンドウの見た目 (Exからの追加スタイル)
		wcex.lpszClassName,							// ウィンドウクラス名
		title.c_str(),								// ウィンドウのタイトル
		windowStyle,								// ウィンドウの見た目 (スタイル)
		CW_USEDEFAULT, CW_USEDEFAULT,				// ウィンドウの位置
		s_windowSize.width, s_windowSize.height,	// ウィンドウのサイズ
		HWND_DESKTOP,								// 親ウィンドウ
		NULL,										// 子ウィンドウ又はメニュー
		hInstance, NULL
	);

	// エラーチェック
	if (s_hWnd == NULL) {
		Debug::ErrorMessage("ウィンドウの生成に失敗しました");
		return 0;
	}

	return true;
}

void GameWindow::Show(int cmdShow)
{
	if (s_hWnd == NULL)
		return;

	ShowWindow(s_hWnd, cmdShow);
	UpdateWindow(s_hWnd);
}

void GameWindow::Resize(UINT clientWidth, UINT clientHeight)
{
	if (s_hWnd == NULL)
		return;

	if (clientWidth == 0 || clientHeight == 0)
		return;

	s_clientSize.width = clientWidth;
	s_clientSize.height = clientHeight;
	s_windowSize = AdjustWindowSize(clientWidth, clientHeight, s_windowStyle);

	SetWindowPos(s_hWnd, nullptr, 0, 0,
		s_windowSize.width, s_windowSize.height, SWP_NOMOVE | SWP_NOZORDER);
}

GameWindow::Size GameWindow::AdjustWindowSize(UINT clientWidth, UINT clientHeight, UINT windowStyle)
{
	// クライアント領域からウィンドウ領域を求める
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = clientWidth;
	rect.bottom = clientHeight;
	AdjustWindowRect(&rect, windowStyle, false);

	// サイズに変換
	Size result;
	result.width = rect.right - rect.left;
	result.height = rect.bottom - rect.top;

	return result;
}
