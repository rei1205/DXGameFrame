// main.cpp
#include <iostream>
#include "DXGameFrame.h"
#include "System/GameTime.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// èâä˙âªópê›íË
	SetupConfig config;
	config.clientWidth = 1280;
	config.clientHeight = 720;
	config.fps = 60;
	config.title = "Title";
	config.fullScreen = false;
	config.isEditorMode = true;

	DXGameFrame::Init(config, hInstance, nCmdShow);
	GameTime::SetShowProssingTime(true);
	DXGameFrame::Run();
	DXGameFrame::Uninit();

	return 0;
}
