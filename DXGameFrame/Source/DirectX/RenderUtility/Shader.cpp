// Shader.cpp
#include "Shader.h"
#include "../../System/Debug.h"

void Shader::Load(const std::string& filePath)
{
	if (FAILED(LoadFromCSOFile(filePath)))
	{
		Debug::ErrorMessage(filePath + "の読み込みに失敗しました。\nプログラムを終了します。");
		exit(0);
	}

	Debug::ConsoleLog("Load Shader : " + filePath);
}