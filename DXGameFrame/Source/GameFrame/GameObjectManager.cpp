// GameObjectManager.cpp
#include "GameObjectManager.h"
#include "Scene.h"
#include "Component/Transform.h"
#include "../Utility/VectorUtility.h"

GameObjectManager::GameObjectManager(Scene* pScene) :
    m_pScene(pScene)
{
}

GameObject* GameObjectManager::CreateGameObject(const std::string& name)
{
    // ゲームオブジェクトを生成
    auto gameObject = std::make_unique<GameObject>();
    GameObject* ptr = gameObject.get();
    m_gameObjects.push_back(std::move(gameObject));
    ptr->m_name = name;

    // Transformコンポーネントを生成
    Transform* transform = m_pScene->GetComponentManager().AddComponent<Transform>(ptr);
   
    // 各種ポインタをセット
    ptr->m_pScene = m_pScene;
    ptr->m_pTransform = transform;

    return ptr;
}

void GameObjectManager::RemoveGameObject(GameObject* pGameObject)
{
    // 削除対象を検索
    auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
        [pGameObject](std::unique_ptr<GameObject>& ptr)
        { return  pGameObject == ptr.get(); }
    );
    if (it == m_gameObjects.end())
        return;

    m_gameObjects.erase(it);
}

void GameObjectManager::ApplyDestroy()
{
    // 新規追加ゲームオブジェクトは処理対象外にする
    int count = (int)m_gameObjects.size();

    for (int i = 0; i < count; ++i)
    {
        GameObject* gameObject = m_gameObjects[i].get();
        if (!gameObject->IsDestroyed())
            continue;

        // ゲームオブジェクト削除時の処理
        gameObject->OnDestroy();

        // ゲームオブジェクトを削除し、インデックスを補正する
        m_gameObjects.erase(m_gameObjects.begin() + i);
        i--;
        count--;
    }
}

void GameObjectManager::Clear()
{
    m_gameObjects.clear();
}

bool GameObjectManager::GetElementIndex(GameObject* pGameObject, size_t* pIndex)
{
    // 対象のゲームオブジェクトを検索
    auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
        [pGameObject](auto& ptr) {return pGameObject == ptr.get(); });
    if (it == m_gameObjects.end())
        return false;

    *pIndex = std::distance(m_gameObjects.begin(), it);
    return true;
}

bool GameObjectManager::MoveElementIndex(GameObject* pGameObject, size_t index)
{
    // 対象のゲームオブジェクトを検索
    auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(),
        [pGameObject](auto& ptr) {return pGameObject == ptr.get(); });
    if (it == m_gameObjects.end())
        return false;
    size_t currentIndex = std::distance(m_gameObjects.begin(), it);

    VectorUtility::MoveElement<std::unique_ptr<GameObject>>(m_gameObjects, currentIndex, index);
    return true;
}
