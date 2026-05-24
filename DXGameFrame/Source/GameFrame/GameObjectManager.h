// GameObjectManager.h
#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>
#include <string>

class GameObject;

/**
 * @brief ゲームオブジェクトオブジェクトを管理するクラス
 */
class GameObjectManager
{
public:
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

private:
	GameObjectManager() = default;
	~GameObjectManager() = default;

	/// ゲームオブジェクト配列
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;

public:
	static GameObjectManager& Instance()
	{
		static GameObjectManager s_instance;
		return s_instance;
	}
};
