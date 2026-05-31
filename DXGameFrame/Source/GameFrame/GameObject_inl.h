// GameObject_inl.h
#pragma once

// Scene.hに依存するゲームオブジェクトのテンプレート関数の実装
template<typename T>
inline T* GameObject::GetComponent()
{
	static_assert(std::is_base_of<Component, T>::value,
		"GetComponentに無効なクラスが指定されました");

	for (auto& component : m_components)
	{
		// 型キャスト可能か調べる
		if (auto ptr = dynamic_cast<T*>(component))
		{
			return ptr;
		}
	}
	return nullptr;
}

template<typename T>
inline T* GameObject::AddComponent()
{
	static_assert(std::is_base_of<Component, T>::value,
		"AddComponentに無効なクラスが指定されました");

	// コンポーネント追加
	auto& a = m_pScene->GetComponentManager();
	T* ptr = a.AddComponent<T>(this);
	m_components.push_back(ptr);
	return ptr;
}

template<typename T>
inline void GameObject::RemoveComponent()
{
	static_assert(std::is_base_of<Component, T>::value,
		"GetComponentに無効なクラスが指定されました");

	for (auto& component : m_components)
	{
		// 型キャスト可能か調べる
		if (auto ptr = dynamic_cast<T*>(component))
		{
			ptr->Destroy();
			return;
		}
	}
}
