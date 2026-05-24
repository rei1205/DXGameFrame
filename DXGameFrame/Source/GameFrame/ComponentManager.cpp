// ComponentManager.cpp
#include "ComponentManager.h"
#include "Component.h"

void ComponentManager::RemoveComponent(Component* pComponent)
{
	auto it = m_componentArrayMap.find(pComponent->GetClassID());
	if (it != m_componentArrayMap.end())
		it->second->Remove(pComponent);
}

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

void ComponentManager::ClearAll()
{
	m_componentArrayMap.clear();
}
