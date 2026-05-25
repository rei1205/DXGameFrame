// Scene.h
#pragma once
#include "GameObjectManager.h"
#include "ComponentManager.h"

/**
 * @brief シーンの基底クラス
 */
class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	virtual void Init() {}
	virtual void Uninit() {}

	/**
	 * @brief シーンの更新を行う
	 */
	void Update();

	/**
	 * @brief シーンの描画を行う
	 */
	void Draw();

	/**
	 * @brief ゲームオブジェクトマネージャーを取得する
	 * @return ゲームオブジェクトマネージャーへの参照
	 */
	GameObjectManager& GetGameObjectManager()
	{
		return m_gameObjectManager;
	}

	/**
	 * @brief コンポーネントマネージャーを取得する
	 * @return コンポーネントマネージャーへの参照
	 */
	ComponentManager& GetComponentManager()
	{
		return m_componentManager;
	}

private:
	/// ゲームオブジェクト管理機能
	GameObjectManager m_gameObjectManager;

	/// コンポーネント管理機能
	ComponentManager m_componentManager;
};
