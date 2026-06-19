// ComponentManager.cpp
#include "ComponentManager.h"
#include "Component/Component.h"

void ComponentManager::RemoveComponent(Component* pComponent)
{
	IComponentArray* componentArray = GetComponentArrayByClassID(pComponent->GetClassID());
	componentArray->Remove(pComponent);
}

void ComponentManager::InvokePendingAwake()
{
	auto componentArrays = GetAllComponentArrays();
	for (auto& array : componentArrays)
	{
		array->InvokePendingAwake();
	}
}

void ComponentManager::StartAll()
{
	auto componentArrays = GetAllComponentArrays();
	for (auto& array : componentArrays)
	{
		array->StartAll();
	}
}

void ComponentManager::UpdateAll()
{
	auto componentArrays = GetAllComponentArrays();
	for (auto& array : componentArrays)
	{
		array->UpdateAll();
	}
}

void ComponentManager::LateUpdateAll()
{
	auto componentArrays = GetAllComponentArrays();
	for (auto& array : componentArrays)
	{
		array->LateUpdateAll();
	}
}

void ComponentManager::ApplyDestroy()
{
	auto componentArrays = GetAllComponentArrays();
	for (auto& array : componentArrays)
	{
		array->ApplyDestroy();
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

std::vector<IComponentArray*> ComponentManager::GetAllComponentArrays()
{
	std::vector<IComponentArray*> componentArrays;
	for (auto& pair : m_componentArrayMap)
	{
		componentArrays.push_back(pair.second.get());
	}
	return componentArrays;
}
