// Scene.cpp
#include "Scene.h"

Scene::~Scene()
{
	m_componentManager.ClearAll();
	m_gameObjectManager.Clear();
}

void Scene::Update()
{
	// コンポーネントの更新
	m_componentManager.StartAll();
	m_componentManager.UpdateAll();
	m_componentManager.LateUpdateAll();

	// 削除を適用
	m_componentManager.ApplyDestroy();
	m_gameObjectManager.ApplyDestroy();
}

void Scene::Draw()
{
}
