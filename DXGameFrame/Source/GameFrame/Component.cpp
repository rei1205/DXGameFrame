// Component.cpp
#include "Component.h"
#include "GameObject.h"

Component::Component():
	m_pGameObject(nullptr),
	m_pTransform(nullptr),
	m_isEnabled(false),
	m_isStarted(false),
	m_classID(0)
{
}

bool Component::IsActiveHierarchy() const
{
	return false;
}

void Component::Init(GameObject* pGameObject, uint32_t classID)
{
	m_pGameObject = pGameObject;
	m_pTransform = pGameObject->GetTransform();
	m_classID = classID;

	pGameObject->RegisterComponent(this);
}

void Component::Uninit()
{
	m_pGameObject->UnregisterComponent(this);

	m_pGameObject = nullptr;
	m_pTransform = nullptr;
}
