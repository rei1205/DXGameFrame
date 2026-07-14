// main.cpp
#include <iostream>
#include "DXGameFrame.h"
#include "System/GameTime.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (!DXGameFrame::InitEditor(hInstance, nCmdShow))
		return 0;

	GameTime::SetShowProssingTime(true);
	DXGameFrame::Run();
	DXGameFrame::Uninit();

	return 0;
}
