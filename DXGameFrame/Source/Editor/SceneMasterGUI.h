// SceneMasterGUI.h
#pragma once
#include "EditorWindow.h"

/**
 * @brief シーン設定のGUI
 */
class SceneMasterGUI : public EditorWindow
{
public:
	SceneMasterGUI();
	~SceneMasterGUI() = default;

private:
	/**
	 * @brief GUIの描画を行う
	 */
	void OnGUI() override;

	// 現在入力中のシーンファイルへのパス
	std::string m_inputScenePath;
};