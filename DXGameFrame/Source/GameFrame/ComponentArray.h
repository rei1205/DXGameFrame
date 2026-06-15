// ComponentArray.h
#pragma once
#include "Component/Component.h"
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
     * @brief 生成時処理を即座に呼び出す
     * @param pComponent コンポーネントへのポインタ
     */
    virtual void CallAwake(Component* pComponent) = 0;

    /**
     * @brief 削除時処理を即座に呼び出す
     * @param pComponent コンポーネントへのポインタ
     */
    virtual void CallOnDestroy(Component* pComponent) = 0;

    /**
     * @brief コンポーネントを削除する
     * @param pComponent 削除するコンポーネントへのポインタ
     */
    virtual void Remove(Component* pComponent) = 0;

    /**
     * @brief 削除予定コンポーネントを実際に削除する
     */
    virtual void ApplyDestroy() = 0;
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
     * @brief 生成時処理を即座に呼び出す
     * @param pComponent コンポーネントへのポインタ
     */
    void CallAwake(Component* pComponent) override;

    /**
     * @brief 削除時処理を即座に呼び出す
     * @param pComponent コンポーネントへのポインタ
     */
    void CallOnDestroy(Component* pComponent) override;

    /**
     * @brief コンポーネントを追加する
     * @param pComponent 追加するコンポーネントへのポインタ (unique_ptr)
     * @param pendingAwake Awake呼び出し保留フラグ
     * @return 生成したコンポーネントへのポインタ
     */
    void Add(std::unique_ptr<T> pComponent, bool pendingAwake);

    /**
     * @brief コンポーネントを削除する
     * @param pComponent 削除するコンポーネントへのポインタ
     */
    void Remove(Component* pComponent) override;

    /**
     * @brief 削除予定コンポーネントを実際に削除する
     */
    void ApplyDestroy() override;

private:
    /// コンポーネント配列
    std::vector<std::unique_ptr<T>> m_components;

    /// Awake呼び出し保留リスト
    std::vector<T*> m_pendingAwakeList;

private:
    /// Awake関数所持判定
    static constexpr bool HasAwake =
        requires(T t)
    {
        t.Awake();
    };

    /// Start関数所持判定
    static constexpr bool HasStart =
        requires(T t)
    {
        t.Start();
    };

    /// Update関数所持判定
    static constexpr bool HasUpdate =
        requires(T t)
    {
        t.Update();
    };

    /// LateUpdate関数所持判定
    static constexpr bool HasLateUpdate =
        requires(T t)
    {
        t.LateUpdate();
    };

    /// OnDestroy関数所持判定
    static constexpr bool HasOnDestroy =
        requires(T t)
    {
        t.OnDestroy();
    };
};


template<typename T>
inline void ComponentArray<T>::InvokePendingAwake()
{
    if constexpr (HasAwake)
    {
        // 呼ばれていないAwake処理呼び出し
        while (!m_pendingAwakeList.empty())
        {
            m_pendingAwakeList.back()->Awake();
            m_pendingAwakeList.pop_back();
        }
    }
}

template<typename T>
inline void ComponentArray<T>::StartAll()
{
    if constexpr (HasStart)
    {
        // Start関数を呼び出す
        int count = (int)m_components.size();
        for (int i = 0; i < count; ++i)
        {
            T* component = m_components[i].get();
            if (component->IsActiveHierarchy() &&
                !component->IsStarted())
            {
                component->Start();
                component->MarkStartedFlag();
            }
        }
    }
    else
    {
        // Start呼び出し済みフラグの更新のみ行う
        int count = (int)m_components.size();
        for (int i = 0; i < count; ++i)
        {
            T* component = m_components[i].get();
            if (component->IsActiveHierarchy())
            {
                component->MarkStartedFlag();
            }
        }
    }
}

template<typename T>
inline void ComponentArray<T>::UpdateAll()
{
    if constexpr (HasUpdate)
    {
        // Update関数を呼び出す
        int count = (int)m_components.size();
        for (int i = 0; i < count; ++i)
        {
            T* component = m_components[i].get();
            if (component->IsActiveHierarchy() &&
                component->IsStarted())
            {
                component->Update();
            }
        }
    }
}

template<typename T>
inline void ComponentArray<T>::LateUpdateAll()
{
    if constexpr (HasLateUpdate)
    {
        // LateUpdate関数を呼び出す
        int count = (int)m_components.size();
        for (int i = 0; i < count; ++i)
        {
            T* component = m_components[i].get();
            if (component->IsActiveHierarchy() &&
                component->IsStarted())
            {
                component->LateUpdate();
            }
        }
    }
}

template<typename T>
inline void ComponentArray<T>::CallAwake(Component* pComponent)
{
    if constexpr (HasAwake)
        static_cast<T*>(pComponent)->Awake();
}

template<typename T>
inline void ComponentArray<T>::CallOnDestroy(Component* pComponent)
{
    if constexpr (HasOnDestroy)
        static_cast<T*>(pComponent)->OnDestroy();
}

template<typename T>
inline void ComponentArray<T>::Add(std::unique_ptr<T> pComponent, bool pendingAwake)
{
    // コンポーネントを追加
    T* ptr = pComponent.get();
    m_components.push_back(std::move(pComponent));

    // Awake処理を登録
    if constexpr (HasAwake)
    {
        if (pendingAwake)
            m_pendingAwakeList.push_back(ptr);
    }
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

    // Awake処理登録を削除
    if constexpr (HasAwake)
    {
        T* ptr = static_cast<T*>(pComponent);
        auto awakeIt = std::find(m_pendingAwakeList.begin(), m_pendingAwakeList.end(), ptr);
        if (awakeIt != m_pendingAwakeList.end())
            m_pendingAwakeList.erase(awakeIt);
    }
    m_components.erase(it);
}

template<typename T>
inline void ComponentArray<T>::ApplyDestroy()
{
    // 新規追加コンポーネントは処理対象外にする
    int count = (int)m_components.size();

    for (int i = 0; i < count; ++i)
    {
        T* component = m_components[i].get();
        if (!component->IsDestroyed())
            continue;

        // コンポーネント削除時の処理
        if constexpr (HasOnDestroy)
        {
            component->OnDestroy();
        }

        // コンポーネントを削除し、インデックスを補正する
        m_components.erase(m_components.begin() + i);
        i--;
        count--;
    }
}
