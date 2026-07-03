// ComponentManager.cpp
#include "ComponentManager.h"
#include "../Component/Renderer.h"
#include "../Component/Camera.h"
#include "../Component/DirectionalLight.h"

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

std::vector<Renderer*> ComponentManager::GetRenderers()
{
	std::vector<Renderer*> result;

	for (auto& array : m_rendererComponentArrays)
	{
		// コンポーネントをリストに追加
		auto components = array->GetComponents();
		for (auto& ptr : components)
		{
			if (!ptr->IsActiveHierarchy())
				continue;

			result.push_back(static_cast<Renderer*>(ptr));
		}
	}

	return result;
}

std::vector<Camera*> ComponentManager::GetCameras()
{
	std::vector<Camera*> result;

	auto components = GetComponentArray<Camera>()->GetComponents();
	for (auto& ptr : components)
	{
		if (!ptr->IsActiveHierarchy())
			continue;

		result.push_back(static_cast<Camera*>(ptr));
	}

	return result;
}

std::vector<DirectionalLight*> ComponentManager::GetDirectionalLights()
{
	std::vector<DirectionalLight*> result;

	auto components = GetComponentArray<DirectionalLight>()->GetComponents();
	for (auto& ptr : components)
	{
		if (!ptr->IsActiveHierarchy())
			continue;

		result.push_back(static_cast<DirectionalLight*>(ptr));
	}

	return result;
}

IComponentArray* ComponentManager::GetComponentArrayByClassID(uint32_t classID)
{
	auto it = m_componentArrayMap.find(classID);
	if (it == m_componentArrayMap.end())
	{
		return nullptr;
	}

	return it->second.get();
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
