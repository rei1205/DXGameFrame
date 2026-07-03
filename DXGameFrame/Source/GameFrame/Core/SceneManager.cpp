// SceneManager.cpp
#include "SceneManager.h"
#include "../../DirectX/Direct3D.h"
#include "../../System/Debug.h"
#include "../../System/ImGuiManager.h"
#include "../../Editor/Editor.h"
#include <fstream>

Scene* SceneManager::s_pActiveScene = nullptr;
Scene* SceneManager::s_pNextScene = nullptr;
std::vector<std::unique_ptr<Scene>> SceneManager::s_sceneList;

void SceneManager::Init()
{
	// 初期シーン登録
	auto scene = std::make_unique<Scene>();
	s_pActiveScene = scene.get();
	s_sceneList.push_back(std::move(scene));

	Debug::ConsoleLog("SceneManager : Initialized");
}

void SceneManager::Uninit()
{
	s_pActiveScene = nullptr;
	s_pNextScene = nullptr;
}

void SceneManager::Execute()
{
	if (s_pActiveScene == nullptr)
		return;

	// シーン更新
	ImGuiManager::BeginFrame();
	s_pActiveScene->Update();

	float clearColor[] = { 0.4f, 0.8f, 0.8f, 1.0f };
	Direct3D::BeginDraw(clearColor);

	Editor::SetTargetScene(s_pActiveScene);

	s_pActiveScene->ApplyDestroy();
	s_pActiveScene->Draw();

	// 描画対象RTVを設定
	auto rtv = Direct3D::GetBackBufferRTV();
	Direct3D::GetContext()->OMSetRenderTargets(1, &rtv, nullptr);
	ImGuiManager::EndFrame();
	Direct3D::EndDraw();
}

void SceneManager::ChangeScene(Scene* pNextScene)
{
}

Scene* SceneManager::GetActiveScene()
{
	return s_pActiveScene;
}

void SceneManager::SerializeScene(const std::string& filePath)
{
	nlohmann::json jsonData;
	jsonData["Scene"];
	s_pActiveScene->Serialize(jsonData["Scene"]);

	std::ofstream file(filePath.c_str());
	file << jsonData.dump(4);
}

void SceneManager::DeserializeScene(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file)return;

	nlohmann::json jsonData;
	file >> jsonData;

	s_pActiveScene = std::make_unique<Scene>().release();
	s_pActiveScene->Deserialize(jsonData["Scene"]);
}

void SceneManager::ApplyChangeScene()
{
}
