// GameObject.h
#pragma once
#include "Component.h"

/**
 * @brief コンポーネントの追加・取得・削除などを行う
 */
class GameObject : public Object
{
	friend class Component;

public:
	GameObject() = default;
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
};
