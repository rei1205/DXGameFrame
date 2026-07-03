// Debug.cpp
#include "Debug.h"
#include <Windows.h>

void MessageBoxUTF8(const std::string& message, const std::string& title, UINT type)
{
	// stringをUTF-8からUTF-16に変換するためのラムダ関数
    auto ToWide = [](const std::string& s)
        {
            int size = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
            std::wstring ws(size, L'\0');

            MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, ws.data(), size);
            ws.pop_back();   // 終端文字を除く
            return ws;
        };

    MessageBoxW(NULL, ToWide(message).c_str(), ToWide(title).c_str(), type);
}

void Debug::ErrorMessage(const std::string& message)
{
    MessageBoxUTF8(message, "エラー", MB_OK | MB_ICONERROR);
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
