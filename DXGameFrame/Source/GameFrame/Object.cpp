// Object.cpp
#include "Object.h"


Object::Object() :
	m_isDestroyed(false)
{
}

Object::~Object()
{
	// 自身を指すポインタを全て無効にする
	InvalidateThisPtr();
}

void Object::AddThisPtr(Object** ppObject)
{
	m_thisPtrs.emplace_back(ppObject);
}

void Object::RemoveThisPtr(Object** ppObject)
{
	auto it = std::find(m_thisPtrs.begin(), m_thisPtrs.end(), ppObject);
	if (it != m_thisPtrs.end())
	{
		// 末尾と入れ替えて削除
		*it = m_thisPtrs.back();
		m_thisPtrs.pop_back();
	}
}

void Object::InvalidateThisPtr()
{
	// 自身を指す全てのポインタにnullptrをセット
	for (auto thisPtr : m_thisPtrs)
	{
		*thisPtr = nullptr;
	}

	m_thisPtrs.clear();
}
