// GameWindowGUI.h
#pragma once
#include "EditorWindow.h"

class GameWindowGUI : public EditorWindow
{
public:
	GameWindowGUI();
	~GameWindowGUI() = default;

private:
	/**
	 * @brief GUIの描画を行う
	 */
	void OnGUI() override;
};
