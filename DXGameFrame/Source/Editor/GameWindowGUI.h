// GameWindowGUI.h
#pragma once
#include "EditorWindow.h"

class GameWindowGUI : public EditorWindow
{
public:
	GameWindowGUI();
	~GameWindowGUI() = default;

private:
	/// 画面サイズ
	int m_screenSize[2];

	/**
	 * @brief GUIの描画を行う
	 */
	void OnGUI() override;
};
