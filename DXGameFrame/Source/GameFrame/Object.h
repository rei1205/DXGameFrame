// Object.h
#pragma once
#include <vector>

/**
 * @brief ゲーム内オブジェクトの基底クラス
 */
class Object
{
	template<typename ObjectType>
	friend class ObjPtr;

	friend class ObjectSerializer;

public:
	Object();
	virtual ~Object();

	// コピー禁止
	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

	/**
	 * @brief このオブジェクトを削除する
	 */
	void Destroy()
	{
		m_isDestroyed = true;
	}

	/**
	 * @brief このオブジェクトの削除フラグを取得する
	 * @return 削除フラグ
	 */
	bool IsDestroyed() const
	{
		return m_isDestroyed;
	}

private:
	/**
	 * @brief インスタンスIDを設定する
	 * @param instanceID インスタンスID
	 */
	void SetInstanceID(uint32_t instanceID)
	{
		m_instanceID = instanceID;
	}

	/**
	 * @brief インスタンスIDを取得する
	 * @return インスタンスID
	 */
	uint32_t GetInstanceID() const
	{
		return m_instanceID;
	}

	/**
	 * @brief 自身を指すポインタを登録する
	 * @param ppObject 登録するポインタへのポインタ
	 */
	void AddThisPtr(Object** ppObject);

	/**
	 * @brief 自身を指すポインタの登録を削除する
	 * @param ppObject 登録を削除するポインタへのポインタ
	 */
	void RemoveThisPtr(Object** ppObject);

	/**
	 * @brief 自身を指すポインタを全て無効にする
	 */
	void InvalidateThisPtr();

	/// オブジェクトが持つ一意なID
	uint32_t m_instanceID;

	/// 削除フラグ
	bool m_isDestroyed;

	/// 自身を指すポインタへのポインタを格納するコンテナ
	std::vector<Object**> m_thisPtrs;
};