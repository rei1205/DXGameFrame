// ObjPtr.h
#pragma once
#include "Object.h"


/**
 * @brief オブジェクト専用のポインタ
 * @details ポインタ先削除時に、自動的に無効化される
 * @details 通常のポインタのように比較演算子や代入演算子、アロー演算子などが使用できる
 */
template <typename ObjectType>
class ObjPtr
{
	static_assert(std::is_base_of<Object, ObjectType>::value,
		"ObjPtrに無効なクラスが指定されました");

public:
	ObjPtr() = default;
	ObjPtr(ObjectType* pObject)
	{
		SetPtr(pObject);
	}
	ObjPtr(const ObjPtr& other)
	{
		m_pObject = nullptr;
		SetPtr(other.m_pObject);
	}
	ObjPtr(ObjPtr&& other)
	{
		m_pObject = nullptr;
		SetPtr(other.m_pObject);
	}
	~ObjPtr()
	{
		Reset();
	}

	// ポインタ先アクセス系演算子
	ObjectType& operator*()
	{
		return *m_pObject;
	}
	ObjectType* operator->()
	{
		return m_pObject;
	}
	const ObjectType& operator*() const
	{
		return *m_pObject;
	}
	const ObjectType* operator->() const
	{
		return m_pObject;
	}

	// 代入演算子
	ObjPtr& operator=(const ObjPtr& ObjPtr)
	{
		SetPtr(ObjPtr.m_pObject);
		return *this;
	}
	ObjPtr& operator=(ObjectType* pObject)
	{
		SetPtr(pObject);
		return *this;
	}
	ObjPtr& operator=(std::nullptr_t)
	{
		Reset();
		return *this;
	}

	// 比較演算子
	bool operator==(const ObjPtr& ObjPtr) const
	{
		return m_pObject == ObjPtr.m_pObject;
	}
	bool operator!=(const ObjPtr& ObjPtr) const
	{
		return m_pObject != ObjPtr.m_pObject;
	}
	bool operator==(std::nullptr_t) const
	{
		return m_pObject == nullptr;
	}
	bool operator!=(std::nullptr_t) const
	{
		return m_pObject != nullptr;
	}
	operator bool() const
	{
		return m_pObject != nullptr;
	}

	/**
	 * @brief ポインタの有効性を確認する
	 * @return ポインタがnullptrならtrueを返す
	 */
	bool IsNull() const
	{
		return m_pObject == nullptr;
	}

	/**
	 * @brief オブジェクトへの実際のポインタを取得する
	 * @return オブジェクトへの生ポインタ
	 */
	ObjectType* Get() const
	{
		return m_pObject;
	}

	/**
	 * @brief ポインタを無効化する
	 */
	void Reset()
	{
		if (m_pObject != nullptr)
		{
			// このポインタの登録を解除
			m_pObject->RemoveThisPtr(reinterpret_cast<Object**>(&m_pObject));
			m_pObject = nullptr;
		}
	}

	/**
	 * @brief ポインタをセットする
	 * @param pObject セットするオブジェクトのポインタ
	 */
	void SetPtr(ObjectType* pObject)
	{
		if (m_pObject == pObject)
			return;

		Reset();
		m_pObject = pObject;

		if (m_pObject != nullptr)
		{
			// このポインタを登録
			m_pObject->AddThisPtr(reinterpret_cast<Object**>(&m_pObject));
		}
	}

private:
	/// オブジェクトへの実際のポインタ
	ObjectType* m_pObject = nullptr;
};
