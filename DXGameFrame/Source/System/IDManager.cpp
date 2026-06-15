// IDManager.cpp
#include "IDManager.h"

IDManager::IDManager(bool useZero):
	m_useZero(useZero)
{
	m_nextID = useZero ? 0 : 1;
}

uint32_t IDManager::GenerateID()
{
	uint32_t id;

	if (!m_freeIDs.empty())
	{
		// 生成済みIDを再利用
		id = m_freeIDs.back();
		m_freeIDs.pop_back();
		return id;
	}

	// 新規生成IDを取得
	while (m_generatedIDs.contains(m_nextID))
	{
		m_nextID++;
	}

	// IDを新規生成
	id = m_nextID;
	m_generatedIDs.insert(id);
	m_nextID++;
	return id;
}

bool IDManager::RegisterID(uint32_t id)
{
	// 解放済みIDから検索
	auto it = std::find(m_freeIDs.begin(), m_freeIDs.end(), id);
	if (it != m_freeIDs.end())
	{
		m_freeIDs.erase(it);
		return true;
	}

	// 使用済みIDか調べる
	if (m_generatedIDs.contains(id))
		return false;

	// 新規IDとして生成
	m_generatedIDs.insert(id);
	return true;
}

void IDManager::ReleaseID(uint32_t id)
{
	// 生成済みIDかチェック
	if (!m_generatedIDs.contains(id))
		return;

	// 既に解放済みかチェック
	auto it = std::find(m_freeIDs.begin(), m_freeIDs.end(), id);
	if (it != m_freeIDs.end())
		return;

	// IDを解放
	m_freeIDs.push_back(id);
}

void IDManager::Clear()
{
	m_freeIDs.clear();
	m_generatedIDs.clear();
	m_nextID = m_useZero ? 0 : 1;
}
