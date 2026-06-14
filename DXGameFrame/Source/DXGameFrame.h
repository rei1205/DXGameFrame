// DXGameFrame.h
#pragma once
#include <Windows.h>
#include <string>

/// 初期化用設定
struct SetupConfig
{
	/// タイトル
	std::string title = "No Title";

	/// クライアント領域の幅
	UINT clientWidth = 1280;

	/// クライアント領域の高さ
	UINT clientHeight = 720;

	/// FPS
	UINT fps = 60;

	/// ウィンドウスタイル
	UINT windowStyle = 
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	/// フルスクリーン設定
	bool fullScreen = false;

	/// エディタモードで実行
	bool isEditorMode = false;
};

/**
 * @brief DXGameFrameの機能を使用する
 */
class DXGameFrame
{
public:
	/**
	 * @brief DXGameFrameの初期化を行う
	 * @param config 初期化用設定
	 * @param hInstance インスタンスハンドル
	 * @param nCmdShow ウィンドウ表示状態
	 * @return 成功したかを返す
	 */
	static bool Init(SetupConfig config, HINSTANCE hInstance, int nCmdShow);

	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief メイン処理を実行する
	 */
	static void Run();

	/**
	 * @brief メイン処理を終了する
	 */
	static void Exit();

private:
	/// 終了フラグ
	static bool s_isExit;
};
