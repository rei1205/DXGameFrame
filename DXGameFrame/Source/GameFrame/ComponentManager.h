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
	template <typename T>
	T* AddComponent();

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
inline T* ComponentManager::AddComponent()
{
    ComponentArray<T>* componentArray = GetComponentArray<T>();
    return componentArray->Add();
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
