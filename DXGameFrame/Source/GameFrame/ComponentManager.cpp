// ComponentManager.cpp
#include "ComponentManager.h"

void ComponentManager::StartAll()
{
	for (auto& componentArray : m_componentArrayMap)
	{
		componentArray.second->StartAll();
	}
}

void ComponentManager::UpdateAll()
{
	for (auto& componentArray : m_componentArrayMap)
	{
		componentArray.second->UpdateAll();
	}
}

void ComponentManager::LateUpdateAll()
{
	for (auto& componentArray : m_componentArrayMap)
	{
		componentArray.second->LateUpdateAll();
	}
}

void ComponentManager::ApplyDestroy()
{
	for (auto& componentArray : m_componentArrayMap)
	{
		componentArray.second->ApplyDestroy();
	}
}
