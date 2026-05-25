// SceneManager.cpp
#include "SceneManager.h"


std::unique_ptr<Scene> SceneManager::s_activeScene = nullptr;
std::unique_ptr<Scene> SceneManager::s_nextScene = nullptr;


void SceneManager::Init(std::unique_ptr<Scene> startScene)
{
	// 初期シーン登録
	s_activeScene = std::move(startScene);
	s_activeScene->Init();
}

void SceneManager::Uninit()
{
	s_activeScene->Uninit();
	s_activeScene = nullptr;
	s_nextScene = nullptr;
}

void SceneManager::Execute()
{
	if (s_activeScene == nullptr)
		return;

	// シーン更新
	s_activeScene->Update();
	s_activeScene->Draw();
	ApplyChangeScene();
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> nextScene)
{
	// 最初にセットされたものが有効
	if (s_nextScene == nullptr)
		s_nextScene = std::move(nextScene);
}

Scene* SceneManager::GetActiveScene()
{
	return s_activeScene.get();
}

void SceneManager::ApplyChangeScene()
{
	if (s_nextScene == nullptr)
		return;

	if (s_activeScene != nullptr)
	{
		s_activeScene->Uninit();
	}

	// シーンの変更
	s_activeScene = std::move(s_nextScene);
	s_nextScene = nullptr;
	s_activeScene->Init();
}
