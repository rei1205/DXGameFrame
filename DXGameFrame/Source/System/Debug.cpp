// Debug.cpp
#include "Debug.h"
#include <Windows.h>


void Debug::ErrorMessage(const std::string& message)
{
    MessageBox(NULL, message.c_str(), "エラー", MB_OK | MB_ICONERROR);
}

void Debug::CreateConsoleWindow()
{
#ifdef _DEBUG
    // コンソールを作成する
    AllocConsole();

    // 標準入出力に割り当てる
    FILE* fp = NULL;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);
#endif
}

void Debug::ConsoleLog(const std::string& message)
{
#ifdef _DEBUG
    printf((message + "\n").c_str());
#endif
}
