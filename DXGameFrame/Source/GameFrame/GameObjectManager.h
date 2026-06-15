// GameObjectManager.h
#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>
#include <string>

/**
 * @brief ゲームオブジェクトオブジェクトを管理するクラス
 */
class GameObjectManager
{
public:
	GameObjectManager() = default;
	~GameObjectManager() = default;

	/**
	 * @brief 空のゲームオブジェクトを生成する
	 * @return 生成したゲームオブジェクトへのポインタ
	 */
	GameObject* CreateGameObject();

	/**
	 * @brief 削除予定ゲームオブジェクトを実際に削除する
	 */
	void ApplyDestroy();

	/**
	 * @brief 全てのゲームオブジェクトを削除する
	 */
	void Clear();

	/**
	 * @brief ゲームオブジェクト配列を取得する
	 * @return ゲームオブジェクト配列へのポインタ
	 */
	std::vector<std::unique_ptr<GameObject>>& GetGameObjects()
	{
		return m_gameObjects;
	}

private:
	/// ゲームオブジェクト配列
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};
