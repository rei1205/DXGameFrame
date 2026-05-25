// Scene.cpp
#include "Scene.h"
#include "ComponentManager.h"
#include "GameObjectManager.h"

void Scene::Update()
{
	ComponentManager& componentManager = ComponentManager::Instance();
	componentManager.StartAll();
	componentManager.UpdateAll();
	componentManager.LateUpdateAll();
	componentManager.ApplyDestroy();
	GameObjectManager::Instance().ApplyDestroy();
}

void Scene::Draw()
{
}
