// Component_inl.h
#pragma once

// GameObject.hに依存するコンポーネントのテンプレート関数の実装
template<typename T>
inline T* Component::GetComponent()
{
	return 	m_pGameObject->GetComponent<T>();
}

template<typename T>
inline T* Component::AddComponent()
{
	return 	m_pGameObject->AddComponent<T>();
}

template<typename T>
inline void Component::RemoveComponent()
{
	m_pGameObject->RemoveComponent<T>();
}
