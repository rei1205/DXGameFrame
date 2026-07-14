// SceneManager.cpp
#include "SceneManager.h"
#include "../../DirectX/Direct3D.h"
#include "../../System/Debug.h"
#include "../../System/ImGuiManager.h"
#include <fstream>

std::unique_ptr<Scene> SceneManager::s_pActiveScene = nullptr;
bool SceneManager::s_sceneChangeFlag = false;
std::string SceneManager::s_currentSceneFilePath;
std::string SceneManager::s_nextSceneFilePath;

void SceneManager::Init()
{
	// 初期シーン作成
	s_pActiveScene  = std::make_unique<Scene>();

	Debug::ConsoleLog("Initialized : SceneManager");
}

void SceneManager::Uninit()
{
	s_pActiveScene = nullptr;
	s_sceneChangeFlag = false;
	s_nextSceneFilePath.clear();

	Debug::ConsoleLog("Uninitialized : SceneManager");
}

void SceneManager::Execute()
{
	if (s_pActiveScene == nullptr)
		return;

	// シーン更新
	ImGuiManager::BeginFrame();
	s_pActiveScene->Update();
	s_pActiveScene->ApplyDestroy();

	// シーン描画
	float clearColor[] = { 0.4f, 0.8f, 0.8f, 1.0f };
	Direct3D::BeginDraw(clearColor);
	s_pActiveScene->Draw();
	ImGuiManager::EndFrame();
	Direct3D::EndDraw();

	ApplyChangeScene();
}

void SceneManager::ChangeScene(const std::string& filePath)
{
	if (s_sceneChangeFlag)
		return;

	s_sceneChangeFlag = true;
	s_nextSceneFilePath = filePath;
}

std::string SceneManager::GetCurrentSceneName()
{
	std::filesystem::path path = s_currentSceneFilePath;
	std::string fileName = path.stem().string();
	return fileName;
}

void SceneManager::SerializeScene(const std::string& filePath)
{
	// シーンシリアライズ
	nlohmann::json jsonData;
	jsonData["Scene"];
	s_pActiveScene->Serialize(jsonData["Scene"]);

	// ファイルに保存
	std::ofstream file(filePath.c_str());
	file << jsonData.dump(4);
}

bool SceneManager::DeserializeScene(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file) return false;

	nlohmann::json jsonData;
	file >> jsonData;

	// シーンデシリアライズ
	s_pActiveScene = std::make_unique<Scene>();
	s_pActiveScene->Deserialize(jsonData["Scene"]);

	s_currentSceneFilePath = filePath;
	return true;
}

void SceneManager::ApplyChangeScene()
{
	if (s_sceneChangeFlag)
	{
		s_sceneChangeFlag = false;
		DeserializeScene(s_nextSceneFilePath);
		s_pActiveScene->GetComponentManager().InvokePendingAwake();
	}
}
