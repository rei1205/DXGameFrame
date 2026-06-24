// Component.cpp
#include "Component.h"
#include "GameObject.h"

Component::Component():
	m_pGameObject(nullptr),
	m_pTransform(nullptr),
	m_isEnabled(true),
	m_awakeCalled(false),
	m_startCalled(false),
	m_isDestroyed(false),
	m_classID(0)
{
}

Scene* Component::GetScene()
{
	return m_pGameObject->GetScene();
}

bool Component::IsActiveHierarchy() const
{
	return m_isEnabled && !IsDestroyed() &&
		m_pGameObject->IsActiveHierarchy();
}

void Component::Init(GameObject* pGameObject, uint32_t classID)
{
	if (pGameObject == nullptr)
		return;

	m_pGameObject = pGameObject;
	m_pTransform = pGameObject->GetTransform();
	m_classID = classID;

	pGameObject->RegisterComponent(this);
}

void Component::Uninit()
{
	if (m_pGameObject == nullptr)
		return;

	m_pGameObject->UnregisterComponent(this);

	m_pGameObject = nullptr;
	m_pTransform = nullptr;
}
