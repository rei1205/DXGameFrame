// ComponentManager.cpp
#include "ComponentManager.h"
#include "Component/Component.h"

void ComponentManager::RemoveComponent(Component* pComponent)
{
	IComponentArray* componentArray = GetComponentArrayByClassID(pComponent->GetClassID());
	componentArray->Remove(pComponent);
}

void ComponentManager::RemoveComponentInternal(Component* pComponent)
{
	IComponentArray* componentArray = GetComponentArrayByClassID(pComponent->GetClassID());
	componentArray->RemoveInternal(pComponent);
}

void ComponentManager::InvokePendingAwake()
{
	for (auto& componentArray : m_componentArrayMap)
	{
		componentArray.second->InvokePendingAwake();
	}
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

IComponentArray* ComponentManager::GetComponentArrayByClassID(uint32_t classID)
{
	auto it = m_componentArrayMap.find(classID);
	if (it == m_componentArrayMap.end())
	{
		return nullptr;
	}

	return m_componentArrayMap[classID].get();
}
