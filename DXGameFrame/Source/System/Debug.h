// Debug.h
#pragma once
#include <string>

/**
 * @brief デバッグ用機能を扱うクラス
 */
class Debug
{
public:
	/**
	 * @brief エラーメッセージを画面に表示する
	 * @param message エラーメッセージ
	 */
	static void ErrorMessage(const std::string& message);

	/**
	 * @brief ログ出力用コンソールウィンドウを作成する
	 */
	static void CreateConsoleWindow();

	/**
	 * @brief コンソールにログを出力する
	 * @param message 出力するメッセージ
	 */
	static void ConsoleLog(const std::string& message);
};
