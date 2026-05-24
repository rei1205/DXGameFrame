// ComponentManager.h
#pragma once
#include "ComponentArray.h"
#include <unordered_map>
#include "ClassID.h"

class GameObject;
class Component;

/**
 * @brief コンポーネントの管理を行う
 */
class ComponentManager
{
public:
    /**
     * @brief コンポーネントを追加する
     * @param pGameObject 親ゲームオブジェクトへのポインタ
     * @return 追加したコンポーネントへのポインタ
     */
    template <typename T>
	T* AddComponent(GameObject* pGameObject);

    /**
     * @brief コンポーネントを削除する
     * @param pComponent 削除するコンポーネントへのポインタ
     */
	void RemoveComponent(Component* pComponent);

	/**
     * @brief 全てのコンポーネントの呼び出し可能な開始処理を呼び出す
     */
    void StartAll();

    /**
     * @brief 全てのコンポーネントの呼び出し可能な更新処理を呼び出す
     */
    void UpdateAll();

    /**
     * @brief 全てのコンポーネントの呼び出し可能な遅延更新処理を呼び出す
     */
    void LateUpdateAll();

    /**
     * @brief 削除予定コンポーネントを実際に削除する
     */
    void ApplyDestroy();

    /**
     * @brief 全てのコンポーネント配列を削除する
     */
    void ClearAll();

private:
	ComponentManager() = default;
	~ComponentManager() = default;

	using ComponentArrayMap = std::unordered_map<uint32_t, std::unique_ptr<IComponentArray>>;

	/// コンポーネント配列のマップ
	ComponentArrayMap m_componentArrayMap;

    /**
     * @brief 指定した型のコンポーネント配列を取得
     * @return コンポーネント配列へのポインタ
     */
    template <typename T>
    ComponentArray<T>* GetComponentArray();

public:
	static ComponentManager& Instance()
	{
		static ComponentManager s_instance;
		return s_instance;
	}
};


template<typename T>
inline T* ComponentManager::AddComponent(GameObject* pGameObject)
{
    ComponentArray<T>* componentArray = GetComponentArray<T>();
    return componentArray->Add(pGameObject);
}

template<typename T>
inline ComponentArray<T>* ComponentManager::GetComponentArray()
{
    uint32_t classID = ClassID<T>::GetID();

    auto it = m_componentArrayMap.find(classID);
    if (it == m_componentArrayMap.end())
    {
        // 新しくコンポーネント配列を生成
        m_componentArrayMap[classID] = std::make_unique<ComponentArray<T>>();
    }

    return static_cast<ComponentArray<T>*>(m_componentArrayMap[classID].get());
}
