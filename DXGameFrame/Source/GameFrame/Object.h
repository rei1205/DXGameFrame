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

public:
	Object();
	virtual ~Object();

	// コピー禁止
	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;

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
};