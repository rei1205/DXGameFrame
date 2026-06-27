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
