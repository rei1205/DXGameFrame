// Scene.cpp
#include "Scene.h"

Scene::Scene():
	m_gameObjectManager(this)
{
	m_renderSystem.Init(this);
}

Scene::~Scene()
{
	m_renderSystem.Uninit();
	m_gameObjectManager.Clear();
}

void Scene::Update()
{
	// コンポーネントの更新
	m_componentManager.StartAll();
	m_componentManager.UpdateAll();
	m_componentManager.LateUpdateAll();
}

void Scene::ApplyDestroy()
{
	// 削除を適用
	m_componentManager.ApplyDestroy();
	m_gameObjectManager.ApplyDestroy();
}

void Scene::Draw()
{
	m_renderSystem.DrawAll();
}

void Scene::Serialize(nlohmann::json& jsonData)
{
	for(auto& gameObject : m_gameObjectManager.GetGameObjects())
	{
		nlohmann::json gameObjectJson;
		gameObject->Serialize(gameObjectJson);
		gameObject->SerializeComponents(gameObjectJson);
		jsonData["GameObjects"].push_back(gameObjectJson);
	}
}

void Scene::Deserialize(nlohmann::json& jsonData)
{
	for (auto& gameObjectJson : jsonData["GameObjects"])
	{
		GameObject* gameObject = m_gameObjectManager.CreateGameObject();
		gameObject->Deserialize(gameObjectJson);
	}

	auto& gameObjects = m_gameObjectManager.GetGameObjects();
	int index = 0;
	for (auto& gameObjectJson : jsonData["GameObjects"])
	{
		gameObjects[index]->DeserializeComponents(gameObjectJson);
		index++;
	}
}
