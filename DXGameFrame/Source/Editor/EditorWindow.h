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
