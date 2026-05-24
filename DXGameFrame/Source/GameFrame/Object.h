// Object.h
#pragma once
#include <vector>

template<typename ObjectType>
class ObjPtr;

/**
 * @brief ゲーム内オブジェクトの基底クラス
 */
class Object
{
	template<typename ObjectType>
	friend class ObjPtr;

public:
	Object();
	virtual ~Object();

	// コピー禁止
	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

	/**
	 * @brief このオブジェクトを削除する
	 */
	virtual void Destroy()
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

	/// 自身を指すポインタへのポインタを格納するコンテナ
	std::vector<Object**> m_thisPtrs;

	/// 削除フラグ
	bool m_isDestroyed;
};