// Component.h
#pragma once
#include "Object.h"

class GameObject;
class Transform;

/**
 * @brief コンポーネントの基底クラス
 */
class Component : public Object
{
public:
	Component();
	virtual ~Component() = default;

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
	bool IsActiveHierarchy();

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
	 * @brief 開始処理の呼び出し状態を取得する
	 * @return 開始処理呼び出し済みフラグ
	 */
	bool IsStarted()
	{
		return m_isStarted;
	}

	/**
	 * @brief 開始処理呼び出し済みフラグをオンにする
	 */
	void MarkStartedFlag()
	{
		m_isStarted = true;
	}

private:
	/// 親ゲームオブジェクトへのポインタ
	GameObject* m_pGameObject;

	/// Transformコンポーネントへのポインタ
	Transform* m_pTransform;

	/// このコンポーネントの有効状態
	bool m_isEnabled;

	/// 開始処理呼び出し済みフラグ
	bool m_isStarted;

	/**
	 * @brief コンポーネントの初期化を行う
	 * @param pGameObject 親ゲームオブジェクトへのポインタ
	 * @param pTransform Transformコンポーネントへのポインタ
	 */
	void Init(GameObject* pGameObject, Transform* pTransform);
};