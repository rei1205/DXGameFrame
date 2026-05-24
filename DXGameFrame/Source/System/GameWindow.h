// GameWindow.h
#pragma once
#include <Windows.h>
#include <string>

/**
 * @brief ウィンドウを作成・管理するクラス
 */
class GameWindow
{
public:
	/// ウィンドウのサイズ
	struct Size
	{
		UINT width;
		UINT height;
	};

	/**
	 * @brief ウィンドウを作成する
	 * @param hInstance インスタンスハンドル
	 * @param wndProc ウィンドウプロシージャ
	 * @param windowStyle ウィンドウスタイル
	 * @param title タイトル文字列
	 * @param clientWidth クライアント領域の幅
	 * @param clientHeight クライアント領域の高さ
	 * @return ウィンドウ作成結果
	 */
	static bool Create(HINSTANCE hInstance, WNDPROC wndProc, UINT windowStyle,
		const std::string& title, UINT clientWidth, UINT clientHeight);

	/**
	 * @brief ウィンドウを表示する
	 * @param cmdShow ウィンドウ表示状態
	 */
	static void Show(int cmdShow);

	/**
	 * @brief ウィンドウサイズを変更する
	 * @param clientWidth クライアント領域の幅
	 * @param clientHeight クライアント領域の高さ
	 */
	static void Resize(UINT clientWidth, UINT clientHeight);

	/**
	 * @brief ウィンドウハンドルを取得する
	 * @return 現在のウィンドウのウィンドウハンドル
	 */
	static HWND GetWindowHandle()
	{
		return s_hWnd;
	}

	/**
	 * @brief クライアント領域のサイズを取得する
	 * @return 現在のウィンドウのクライアント領域のサイズ
	 */
	static Size GetClientSize()
	{
		return s_clientSize;
	}

	/**
	 * @brief ウィンドウサイズを取得する
	 * @return 現在のウィンドウのサイズ
	 */
	static Size GetWindowSize()
	{
		return s_windowSize;
	}

private:
	/// ウィンドウハンドル
	static HWND s_hWnd;

	/// ウィンドウスタイル
	static UINT s_windowStyle;

	/// ウィンドウのサイズ
	static Size s_windowSize;

	/// クライアント領域のサイズ
	static Size s_clientSize;

	/**
	 * @brief クライアント領域のサイズから実際のウィンドウサイズを求める
	 * @param clientWidth クライアント領域の幅
	 * @param clientHeight クライアント領域の高さ
	 * @param windowStyle ウィンドウスタイル
	 * @return 実際のウィンドウサイズ
	 */
	static Size AdjustWindowSize(UINT clientWidth, UINT clientHeight, UINT windowStyle);
};
