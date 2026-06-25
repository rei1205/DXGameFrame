// EditorWindow.h
#pragma once
#include <string>

/**
 * @brief エディタウィンドウの基底クラス
 */
class EditorWindow
{
public:
	EditorWindow(const std::string& windowName);
	~EditorWindow() = default;
	
	/**
	 * @brief 更新処理
	 */
	void Update();

	/**
	 * @brief ウィンドウの開閉状態を取得する
	 * @return ウィンドウが開いている場合trueを返す
	 */
	bool IsOpen()
	{
		return m_openFlag;
	}

	/**
	 * @brief ウィンドウを開く
	 */
	void OpenWindow()
	{
		m_openFlag = true;
	}

	/**
	 * @brief ウィンドウ閉じる
	 */
	void CloseWindow()
	{
		m_openFlag = false;
	}

	/**
	 * @brief ウィンドウ名を取得する
	 * @return ウィンドウ名
	 */
	std::string GetWindowName()
	{
		return m_windowName;
	}

private:
	/// ウィンドウ名
	std::string m_windowName;

	/// ウィンドウオープンフラグ
	bool m_openFlag;

	/**
	 * @brief GUIの描画を行う
	 */
	virtual void OnGUI() = 0;
};
