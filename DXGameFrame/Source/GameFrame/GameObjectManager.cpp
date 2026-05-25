// GameObjectManager.cpp
#include "GameObjectManager.h"
#include "GameObject.h"

// 不完全な型のスマートポインタを持つためにcppで定義
GameObjectManager::GameObjectManager() = default;
GameObjectManager::~GameObjectManager() = default;

GameObject* GameObjectManager::CreateGameObject()
{
    // ゲームオブジェクトを生成
    auto gameObject = std::make_unique<GameObject>();
    GameObject* ptr = gameObject.get();
    m_gameObjects.push_back(std::move(gameObject));

    return ptr;
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
