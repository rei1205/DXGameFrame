// GameObject.h
#pragma once
#include "Component.h"
#include "ComponentManager.h"

/**
 * @brief コンポーネントの追加・取得・削除などを行う
 */
class GameObject : public Object
{
	friend class Component;

public:
	GameObject();
	~GameObject() = default;

	/**
	 * @brief コンポーネントを取得する
	 * @return コンポーネントへのポインタ
	 */
	template <typename T>
	T* GetComponent();

	/**
	 * @brief コンポーネントを追加する
	 * @return 追加したコンポーネントへのポインタ
	 */
	template <typename T>
	T* AddComponent();

	/**
	 * @brief コンポーネントを削除する
	 */
	template <typename T>
	void RemoveComponent();

	/**
	 * @brief Transformコンポーネントを取得する
	 * @return Transformコンポーネントへのポインタ
	 */
	Transform* GetTransform()
	{
		return m_pTransform;
	}

	/**
	 * @brief 親子関係を考慮した有効状態を取得する
	 * @return ヒエラルキー上の有効状態
	 */
	bool IsActiveHierarchy() const;

	/**
	 * @brief このゲームオブジェクト自身の有効状態を取得する
	 * @return このゲームオブジェクトの有効状態
	 */
	bool IsActiveSelf() const
	{
		return m_isActive;
	}

	/**
	 * @brief このゲームオブジェクトの有効状態を設定する
	 * @param isActive 設定する有効状態
	 */
	void SetActive(bool isActive)
	{
		m_isActive = isActive;
	}

	/**
	 * @brief ゲームオブジェクト削除時の処理
	 */
	void OnDestroy();

private:
	/// このゲームオブジェクトが持つコンポーネントのリスト
	std::vector<Component*> m_components;
	
	/// Transformコンポーネントへのポインタ
	Transform* m_pTransform;

	/// このゲームオブジェクトの有効状態
	bool m_isActive;

	/**
	 * @brief コンポーネントを登録する
	 * @param pComponent 登録するコンポーネントへのポインタ
	 */
	void RegisterComponent(Component* pComponent);

	/**
	 * @brief コンポーネントの登録を解除する
	 * @param pComponent 登録解除するコンポーネントへのポインタ
	 */
	void UnregisterComponent(Component* pComponent);

public:
	/**
	 * @brief ゲームオブジェクトを作成する
	 * @return 作成したゲームオブジェクトへのポインタ
	 */
	static GameObject* Create();
};

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
	T* ptr = ComponentManager::Instance().AddComponent<T>(this);
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
