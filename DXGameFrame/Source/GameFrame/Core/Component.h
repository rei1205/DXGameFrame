// Component.h
#pragma once
#include "Object.h"
#include "ClassID.h"

class Scene;
class GameObject;

/**
 * @brief コンポーネントの基底クラス
 */
class Component : public Object
{
	template <typename T>
	friend class ComponentArray;

	friend class Transform;
	
public:
	Component();
	virtual ~Component() = default;

	/**
	 * @brief 所属するシーンを取得する
	 * @return シーンへのポインタ
	 */
	Scene* GetScene();

	/**
	 * @brief 親ゲームオブジェクトを取得する
	 * @return 親ゲームオブジェクトへのポインタ
	 */
	GameObject* GetGameObject()
	{
		return m_pGameObject;
	}

	/**
	 * @brief Transformコンポーネントを取得する
	 * @return Transformコンポーネントへのポインタ
	 */
	Transform* GetTransform()
	{
		return m_pTransform;
	}

	/**
	 * @brief 親子関係を考慮した有効状態を取得する
	 * @return ヒエラルキー上の有効状態
	 */
	bool IsActiveHierarchy() const;

	/**
	 * @brief このコンポーネントの有効状態を取得する
	 * @return このコンポーネントの有効状態
	 */
	bool IsEnabled() const
	{
		return m_isEnabled;
	}

	/**
	 * @brief このコンポーネントの有効状態を設定する
	 * @param isEnabled 設定する有効状態
	 */
	void SetEnabled(bool isEnabled)
	{
		m_isEnabled = isEnabled;
	}

	/**
	 * @brief Awake処理の呼び出し状態を取得する
	 * @return Awake処理呼び出し済みフラグ
	 */
	bool IsAwakeCalled() const
	{
		return m_awakeCalled;
	}

	/**
	 * @brief 開始処理の呼び出し状態を取得する
	 * @return 開始処理呼び出し済みフラグ
	 */
	bool IsStartCalled() const
	{
		return m_startCalled;
	}

	/**
	 * @brief このコンポーネントを削除する
	 */
	void Destroy()
	{
		m_isDestroyed = true;
	}

	/**
	 * @brief このコンポーネントの削除フラグを取得する
	 * @return 削除フラグ
	 */
	bool IsDestroyed() const
	{
		return m_isDestroyed;
	}

	/**
	 * @brief クラス識別用IDを取得する
	 * @return クラスID
	 */
	uint32_t GetClassID() const
	{
		return m_classID;
	}

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
	 * @brief 生成時処理
	 */
	virtual void Awake() {}

	/**
	 * @brief 開始処理
	 */
	virtual void Start() {}

	/**
	 * @brief 更新処理
	 */
	virtual void Update() {}

	/**
	 * @brief 遅延更新処理
	 */
	virtual void LateUpdate() {}

	/**
	 * @brief 削除時処理
	 */
	virtual void OnDestroy() {}

	/**
	 * @brief インスペクターでの表示
	 */
	virtual void OnInspector() {}

private:
	/// 親ゲームオブジェクトへのポインタ
	GameObject* m_pGameObject;

	/// Transformコンポーネントへのポインタ
	Transform* m_pTransform;

	/// このコンポーネントの有効状態
	bool m_isEnabled;

	/// Awake呼び出し済みフラグ
	bool m_awakeCalled;

	/// Start呼び出し済みフラグ
	bool m_startCalled;

	/// 削除フラグ
	bool m_isDestroyed;

	/// クラス識別用ID
	uint32_t m_classID;

	/**
	 * @brief コンポーネントの初期化を行う
	 * @param pGameObject 親ゲームオブジェクトへのポインタ
	 * @param classID クラス識別用ID
	 */
	void Init(GameObject* pGameObject, uint32_t classID);

	/**
	 * @brief コンポーネントの終了処理
	 */
	void Uninit();
};