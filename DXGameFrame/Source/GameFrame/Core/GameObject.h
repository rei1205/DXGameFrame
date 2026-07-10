// GameObject.h
#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include <objbase.h>

class Scene;

/**
 * @brief コンポーネントの追加・取得・削除などを行う
 */
class GameObject : public Object
{
	friend class GameObjectManager;
	friend class Component;
	
public:
	GameObject();
	~GameObject() = default;

	/**
	 * @brief コンポーネントを取得する
	 * @return コンポーネントへのポインタ
	 */
	template <typename T>
	T* GetComponent();

	/**
	 * @brief コンポーネントを追加する
	 * @return 追加したコンポーネントへのポインタ
	 */
	template <typename T>
	T* AddComponent();

	/**
	 * @brief コンポーネントを削除する
	 */
	template <typename T>
	void RemoveComponent();

	/**
	 * @brief ゲームオブジェクト名を取得する
	 * @return ゲームオブジェクト名
	 */
	std::string GetName()
	{
		return m_name;
	}

	/**
	 * @brief ゲームオブジェクト名を設定する
	 * @param name ゲームオブジェクト名
	 */
	void SetName(const std::string& name)
	{
		m_name = name;
	}

	/**
	 * @brief 所属するシーンを取得する
	 * @return シーンへのポインタ
	 */
	Scene* GetScene()
	{
		return m_pScene;
	}

	/**
	 * @brief Transformコンポーネントを取得する
	 * @return Transformコンポーネントへのポインタ
	 */
	Transform* GetTransform() const
	{
		return m_pTransform;
	}

	/**
	 * @brief GUIDを取得する
	 * @return このゲームオブジェクトのGUID
	 */
	GUID GetGUID() const
	{
		return m_guid;
	}

	/**
	 * @brief 親子関係を考慮した有効状態を取得する
	 * @return ヒエラルキー上の有効状態
	 */
	bool IsActiveHierarchy() const;

	/**
	 * @brief このゲームオブジェクト自身の有効状態を取得する
	 * @return このゲームオブジェクトの有効状態
	 */
	bool IsActiveSelf() const
	{
		return m_isActive;
	}

	/**
	 * @brief このゲームオブジェクトの有効状態を設定する
	 * @param isActive 設定する有効状態
	 */
	void SetActive(bool isActive)
	{
		m_isActive = isActive;
	}

	/**
	 * @brief このゲームオブジェクトを削除する
	 */
	void Destroy();

	/**
	 * @brief このゲームオブジェクトの削除フラグを取得する
	 * @return 削除フラグ
	 */
	bool IsDestroyed() const
	{
		return m_isDestroyed;
	}

	/**
	 * @brief ゲームオブジェクト削除時の処理
	 */
	void OnDestroy();

	/**
	 * @brief コンポーネント配列を取得する
	 * @return コンポーネント配列
	 */
	std::vector<Component*> GetComponents()
	{
		return m_components;
	}

	/**
	 * @brief ゲームオブジェクトをシリアライズする
	 * @param jsonData 書き込み先jsonデータへの参照
	 */
	void Serialize(nlohmann::json& jsonData) override;

	/**
	 * @brief ゲームオブジェクトをデシリアライズする
	 * @param jsonData 読み込み先jsonデータへの参照
	 */
	void Deserialize(const nlohmann::json& jsonData) override;

	/**
	 * @brief ゲームオブジェクトが持つコンポーネントをシリアライズする
	 * @param jsonData 書き込み先jsonデータへの参照
	 */
	void SerializeComponents(nlohmann::json& jsonData);

	/**
	 * @brief ゲームオブジェクトが持つコンポーネントをデシリアライズする
	 * @param jsonData 読み込み先jsonデータへの参照
	 */
	void DeserializeComponents(const nlohmann::json& jsonData);

private:
	/// ゲームオブジェクト名
	std::string m_name;

	/// このゲームオブジェクトが持つコンポーネントのリスト
	std::vector<Component*> m_components;
	
	/// 所属するシーンへのポインタ
	Scene* m_pScene;

	/// Transformコンポーネントへのポインタ
	Transform* m_pTransform;

	/// ゲームオブジェクトのGUID
	GUID m_guid;

	/// このゲームオブジェクトの有効状態
	bool m_isActive;

	/// 削除フラグ
	bool m_isDestroyed;

	/**
	 * @brief コンポーネントを登録する
	 * @param pComponent 登録するコンポーネントへのポインタ
	 */
	void RegisterComponent(Component* pComponent);

	/**
	 * @brief コンポーネントの登録を解除する
	 * @param pComponent 登録解除するコンポーネントへのポインタ
	 */
	void UnregisterComponent(Component* pComponent);
};

// GameObject.hに依存するコンポーネントのテンプレート関数の実装
#include "Component_inl.h"
