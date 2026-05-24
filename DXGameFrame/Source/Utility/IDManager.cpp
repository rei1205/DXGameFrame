// IDManager.cpp
#include "IDManager.h"


IDManager::IDManager() :
	m_nextID(0)
{
}

uint32_t IDManager::GenerateID()
{
	uint32_t id;

	if (m_freeIDs.empty())
	{
		// IDを新規生成
		id = m_nextID;
		m_nextID++;
		return id;
	}

	// 生成済みIDを再利用
	id = m_freeIDs.back();
	m_freeIDs.pop_back();
	return id;
}

void IDManager::ReleaseID(uint32_t id)
{
	// 値チェック
	if (id < 0 || id >= m_nextID)
		return;

	// 既に解放済みかチェック
	auto it = std::find(m_freeIDs.begin(), m_freeIDs.end(), id);
	if (it == m_freeIDs.end())
		return;

	// IDを解放
	m_freeIDs.push_back(id);
}
