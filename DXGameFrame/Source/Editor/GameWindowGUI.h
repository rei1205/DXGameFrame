// GameWindowGUI.h
#pragma once
#include "EditorWindow.h"

class GameWindowGUI : public EditorWindow
{
public:
	GameWindowGUI();
	~GameWindowGUI() = default;

private:
	void OnGUI() override;
};
