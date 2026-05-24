// GameObject.cpp
#include "GameObject.h"
#include "GameObjectManager.h"

GameObject::GameObject():
	m_pTransform(nullptr),
	m_isActive(true)
{
}

void GameObject::OnDestroy()
{
	while (m_components.empty())
	{
		Component* component = m_components.back();
		ComponentManager::Instance().RemoveComponent(component);
	}

}

void GameObject::RegisterComponent(Component* pComponent)
{
	m_components.push_back(pComponent);
}

void GameObject::UnregisterComponent(Component* pComponent)
{
	auto it = std::find(m_components.begin(), m_components.end(), pComponent);
	if (it != m_components.end())
		m_components.erase(it);
}

GameObject* GameObject::Create()
{
	return GameObjectManager::Instance().CreateGameObject();
}
