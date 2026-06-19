// GameObjectManager.h
#pragma once
#include "GameObject.h"
#include <memory>
#include <string>

/**
 * @brief ゲームオブジェクトオブジェクトを管理するクラス
 */
class GameObjectManager
{
public:
	GameObjectManager(Scene* pScene);
	~GameObjectManager() = default;

	/**
	 * @brief 空のゲームオブジェクトを生成する
	 * @param name ゲームオブジェクト名
	 * @return 生成したゲームオブジェクトへのポインタ
	 */
	GameObject* CreateGameObject(const std::string& name);

	/**
	 * @brief ゲームオブジェクトを削除する
	 * @param pGameObject 削除するゲームオブジェクトへのポインタ
	 */
	void RemoveGameObject(GameObject* pGameObject);

	/**
	 * @brief 削除予定ゲームオブジェクトを実際に削除する
	 */
	void ApplyDestroy();

	/**
	 * @brief 全てのゲームオブジェクトを削除する
	 */
	void Clear();

	/**
	 * @brief ゲームオブジェクトのインデックスを取得する
	 * @param pGameObject ゲームオブジェクトへのポインタ
	 * @param pIndex インデックス格納先のポインタ
	 * @return 指定したゲームオブジェクトが存在しない場合falseを返す
	 */
	bool GetElementIndex(GameObject* pGameObject, size_t* pIndex);

	/**
	 * @brief ゲームオブジェクトを配列上で移動させる
	 * @param pGameObject 移動させるゲームオブジェクトへのポインタ
	 * @param index 移動先インデックス
	 * @return 指定したゲームオブジェクトが存在しない場合falseを返す
	 */
	bool MoveElementIndex(GameObject* pGameObject, size_t index);

	/**
	 * @brief ゲームオブジェクト配列を取得する
	 * @return ゲームオブジェクト配列への参照
	 */
	const std::vector<std::unique_ptr<GameObject>>& GetGameObjects()
	{
		return m_gameObjects;
	}

private:
	/// ゲームオブジェクト配列
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;

	/// 親シーンへのポインタ
	Scene* m_pScene;
};
