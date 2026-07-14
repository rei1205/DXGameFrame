// DXGameFrame.h
#pragma once
#include <Windows.h>

/**
 * @brief DXGameFrameの機能を使用する
 */
class DXGameFrame
{
public:
	/**
	 * @brief DXGameFrameのゲーム用初期化を行う
	 * @param hInstance インスタンスハンドル
	 * @param nCmdShow ウィンドウ表示状態
	 * @return 成功したかを返す
	 */
	static bool InitGame(HINSTANCE hInstance, int nCmdShow);

	/**
	 * @brief DXGameFrameのエディタ用初期化を行う
	 * @param hInstance インスタンスハンドル
	 * @param nCmdShow ウィンドウ表示状態
	 * @return 成功したかを返す
	 */
	static bool InitEditor(HINSTANCE hInstance, int nCmdShow);

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
	/// 初期化済みフラグ
	static bool s_isInitialized;

	/// 終了フラグ
	static bool s_isExit;

	/// エディタモードフラグ
	static bool s_isEditorMode;
};
