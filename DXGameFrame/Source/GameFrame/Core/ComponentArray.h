// ComponentArray.h
#pragma once
#include "Component.h"
#include "../Component/Renderer.h"
#include "ClassID.h"
#include <vector>
#include <memory>

/**
 * @brief コンポーネント配列の基底クラス
 */
class IComponentArray
{
public:
    IComponentArray() = default;
    virtual ~IComponentArray() = default;
    
    /**
     * @brief 保留中のAwake処理を呼び出す
     */
    virtual void InvokePendingAwake() = 0;

    /**
     * @brief 全てのコンポーネントの呼び出し可能な開始処理を呼び出す
     */
    virtual void StartAll() = 0;

    /**
     * @brief 全てのコンポーネントの呼び出し可能な更新処理を呼び出す
     */
    virtual void UpdateAll() = 0;

    /**
     * @brief 全てのコンポーネントの呼び出し可能な遅延更新処理を呼び出す
     */
    virtual void LateUpdateAll() = 0;

    /**
     * @brief 削除予定コンポーネントを実際に削除する
     */
    virtual void ApplyDestroy() = 0;

    /**
     * @brief コンポーネントを削除する
     * @param pComponent 削除するコンポーネントへのポインタ
     */
    virtual void Remove(Component* pComponent) = 0;

    /**
     * @brief 全てのコンポーネントを取得する
     * @return コンポーネント配列
     */
    virtual std::vector<Component*> GetComponents() = 0;
};

/**
 * @brief コンポーネントを管理する配列
 */
template<typename T>
class ComponentArray : public IComponentArray
{
    static_assert(std::is_base_of<Component, T>::value,
        "ComponentArrayに無効なクラスが指定されました");

public:
    ComponentArray() = default;
    virtual ~ComponentArray() = default;

    /**
     * @brief 保留中のAwake処理を呼び出す
     */
    void InvokePendingAwake() override;

    /**
     * @brief 全てのコンポーネントの呼び出し可能な開始処理を呼び出す
     */
    void StartAll() override;

    /**
     * @brief 全てのコンポーネントの呼び出し可能な更新処理を呼び出す
     */
    void UpdateAll() override;

    /**
     * @brief 全てのコンポーネントの呼び出し可能な遅延更新処理を呼び出す
     */
    void LateUpdateAll() override;

    /**
     * @brief 削除予定コンポーネントを実際に削除する
     */
    void ApplyDestroy() override;

    /**
     * @brief コンポーネントを生成する
     * @param pGameObject 親となるゲームオブジェクトへのポインタ
     * @return 生成したコンポーネントへのポインタ
     */
    T* Add(GameObject* pGameObject);

    /**
     * @brief Awake呼び出しを保留するコンポーネント生成
     * @param pGameObject 親となるゲームオブジェクトへのポインタ
     * @return 生成したコンポーネントへのポインタ
     */
    T* AddPendingAwake(GameObject* pGameObject);

    /**
     * @brief コンポーネントを削除する
     * @param pComponent 削除するコンポーネントへのポインタ
     */
    void Remove(Component* pComponent) override;

    /**
     * @brief 全てのコンポーネントを取得する
     * @return コンポーネント配列
     */
    std::vector<Component*> GetComponents() override;

private:
    /// コンポーネント配列
    std::vector<std::unique_ptr<T>> m_components;

    /// Awake呼び出し保留リスト
    std::vector<T*> m_pendingAwakeList;
};


template<typename T>
inline void ComponentArray<T>::InvokePendingAwake()
{
    // 呼ばれていないAwake処理呼び出し
    while (!m_pendingAwakeList.empty())
    {
        m_pendingAwakeList.back()->Awake();
		static_cast<Component*>(m_pendingAwakeList.back())->m_awakeCalled = true;
        m_pendingAwakeList.pop_back();
    }
}

template<typename T>
inline void ComponentArray<T>::StartAll()
{
    int count = (int)m_components.size();
    for (int i = 0; i < count; ++i)
    {
        T* component = m_components[i].get();
        if (component->IsActiveHierarchy() &&
            !component->IsStartCalled())
        {
            // Start関数を呼び出す
            component->Start();
            static_cast<Component*>(component)->m_startCalled = true;
        }
    }
}

template<typename T>
inline void ComponentArray<T>::UpdateAll()
{
    // Update関数を呼び出す
    int count = (int)m_components.size();
    for (int i = 0; i < count; ++i)
    {
        T* component = m_components[i].get();
        if (component->IsActiveHierarchy() &&
            component->IsStartCalled())
        {
            component->Update();
        }
    }
}

template<typename T>
inline void ComponentArray<T>::LateUpdateAll()
{
    // LateUpdate関数を呼び出す
    int count = (int)m_components.size();
    for (int i = 0; i < count; ++i)
    {
        T* component = m_components[i].get();
        if (component->IsActiveHierarchy() &&
            component->IsStartCalled())
        {
            component->LateUpdate();
        }
    }
}

template<typename T>
inline void ComponentArray<T>::ApplyDestroy()
{
    // この時点で存在するコンポーネントのみ処理対象にする
    int count = (int)m_components.size();

    for (int i = 0; i < count; ++i)
    {
        T* component = m_components[i].get();
        if (!component->IsDestroyed())
            continue;

        // コンポーネント削除時の処理
        if (component->IsAwakeCalled())
            component->OnDestroy();

        component->Uninit();

        // Awake処理登録を削除
        auto awakeIt = std::find(m_pendingAwakeList.begin(), m_pendingAwakeList.end(), component);
        if (awakeIt != m_pendingAwakeList.end())
            m_pendingAwakeList.erase(awakeIt);

        // コンポーネントを削除し、インデックスを補正する
        m_components.erase(m_components.begin() + i);
        i--;
        count--;
    }
}

template<typename T>
inline T* ComponentArray<T>::Add(GameObject* pGameObject)
{
    // コンポーネントを追加
    auto component = std::make_unique<T>();
    T* ptr = component.get();
    m_components.push_back(std::move(component));

    // コンポーネント生成時の処理
    ptr->Init(pGameObject, ClassID<T>::GetID());
    ptr->Awake();
	static_cast<Component*>(ptr)->m_awakeCalled = true;

    return ptr;
}

template<typename T>
inline T* ComponentArray<T>::AddPendingAwake(GameObject* pGameObject)
{
    // コンポーネントを追加
    auto component = std::make_unique<T>();
    T* ptr = component.get();
    m_components.push_back(std::move(component));

    // コンポーネント生成時の処理
    ptr->Init(pGameObject, ClassID<T>::GetID());

    // Awake呼び出しを保留
    m_pendingAwakeList.push_back(ptr);

    return ptr;
}

template<typename T>
inline void ComponentArray<T>::Remove(Component* pComponent)
{
    // 削除対象を検索
    auto it = std::find_if(m_components.begin(), m_components.end(),
        [pComponent](std::unique_ptr<T>& ptr)
        { return  pComponent == ptr.get(); }
    );
    if (it == m_components.end())
        return;

    // コンポーネント削除時の処理
    T* component = static_cast<T*>(pComponent);
    if (component->IsAwakeCalled())
        component->OnDestroy();

    component->Uninit();

    // Awake処理登録を削除
    auto awakeIt = std::find(m_pendingAwakeList.begin(), m_pendingAwakeList.end(), component);
    if (awakeIt != m_pendingAwakeList.end())
        m_pendingAwakeList.erase(awakeIt);

    m_components.erase(it);
}


template<typename T>
inline std::vector<Component*> ComponentArray<T>::GetComponents()
{
    std::vector<Component*> result;
    for (auto& component : m_components)
    {
        result.push_back(static_cast<Component*>(component.get()));
    }
    return result;
}
