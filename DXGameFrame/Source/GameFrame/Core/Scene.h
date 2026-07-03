// Scene.h
#pragma once
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "../RenderSystem/RenderSystem.h"

/**
 * @brief シーン情報を持つクラス
 */
class Scene
{
public:
	Scene();
	~Scene();

	/**
	 * @brief シーンの更新を行う
	 */
	void Update();

	/**
	 * @brief ゲームオブジェクトとコンポーネントの削除を適用する
	 */
	void ApplyDestroy();

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

	/**
	 * @brief レンダーシステムを取得する
	 * @return レンダーシステムへの参照
	 */
	RenderSystem& GetRenderSystem()
	{
		return m_renderSystem;
	}

	/**
	 * @brief シーンをシリアライズする
	 * @param jsonData 書き込み先jsonデータへの参照
	 */
	void Serialize(nlohmann::json& jsonData);

	/**
	 * @brief シーンをデシリアライズする
	 * @param jsonData 読み込み先jsonデータへの参照
	 */
	void Deserialize(nlohmann::json& jsonData);

private:
	/// ゲームオブジェクト管理機能
	GameObjectManager m_gameObjectManager;

	/// コンポーネント管理機能
	ComponentManager m_componentManager;

	/// シーン描画機能
	RenderSystem m_renderSystem;
};

// Scene.hに依存するゲームオブジェクトのテンプレート関数の実装
#include "GameObject_inl.h"
