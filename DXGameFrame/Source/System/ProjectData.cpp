// ProjectData.cpp
#include "ProjectData.h"
#include <fstream>
#include <nlohmann/json.hpp>

std::string ProjectData::s_projectName = "";
int ProjectData::s_screenWidth = 1280;
int ProjectData::s_screenHeight  = 720;
bool ProjectData::s_isFullScreen = false;
int ProjectData::s_fps = 60;
std::string ProjectData::s_startScenePath = "";
std::string ProjectData::s_editorScenePath = "";
const std::string ProjectData::s_assetsFolderPath = "Assets/";
const std::string ProjectData::s_editorFolderPath = "Assets/EngineData/";

void ProjectData::Save()
{
	// フォルダを自動生成
	std::filesystem::create_directories(s_editorFolderPath);

	// ファイルを作成して保存
	std::ofstream file(s_editorFolderPath + "ProjectData.proj", std::ios::binary);
	if (!file)
		return;

	// プロジェクトデータを保存する
	nlohmann::json jsonData;
	jsonData["ProjectName"] = s_projectName;
	jsonData["ScreenWidth"] = s_screenWidth;
	jsonData["ScreenHeight"] = s_screenHeight;
	jsonData["FPS"] = s_fps;
	jsonData["IsFullScreen"] = s_isFullScreen;
	jsonData["StartScenePath"] = s_startScenePath;
	jsonData["EditorScenePath"] = s_editorScenePath;
	file << jsonData.dump(4);
}

bool ProjectData::Load()
{
	std::ifstream file(s_editorFolderPath + "ProjectData.proj", std::ios::binary);
	if (!file)
		return false;

	nlohmann::json jsonData;
	file >> jsonData;

	// プロジェクトデータを読み込む
	s_projectName = jsonData.value("ProjectName", s_projectName);
	s_screenWidth = jsonData.value("ScreenWidth", s_screenWidth);
	s_screenHeight = jsonData.value("ScreenHeight", s_screenHeight);
	s_isFullScreen = jsonData.value("IsFullScreen", s_isFullScreen);
	s_fps = jsonData.value("FPS", s_fps);
	s_startScenePath = jsonData.value("StartScenePath", s_startScenePath);
	s_editorScenePath = jsonData.value("EditorScenePath", s_editorScenePath);

	return true;
}
