// GameObject.cpp
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Component/Transform.h"

GameObject::GameObject():
	m_pTransform(nullptr),
	m_isActive(true)
{
}

bool GameObject::IsActiveHierarchy() const
{
	// 親がないまたは非アクティブの場合再帰処理を終了
	Transform* pParent = m_pTransform->GetParent();
	if (pParent == nullptr || m_isActive == false || IsDestroyed())
		return m_isActive;

	// 再帰的に有効状態を求める
	return pParent->GetGameObject()->IsActiveHierarchy();
}

void GameObject::OnDestroy()
{
	while (m_components.empty())
	{
		Component* component = m_components.back();
		m_components.pop_back();
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
	// ゲームオブジェクトとTransformコンポーネントを生成
	GameObject* gameobject = GameObjectManager::Instance().CreateGameObject();
	Transform* transform = ComponentManager::Instance().AddComponent<Transform>(gameobject);

	// Transformコンポーネントのポインタをセット
	gameobject->m_pTransform = transform;
	static_cast<Component*>(transform)->m_pTransform = transform;

	return gameobject;
}
