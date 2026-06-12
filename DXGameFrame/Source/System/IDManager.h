// IDManager.h
#pragma once
#include <vector>

/**
 * @brief 一意なIDの生成・管理を行う
 */
class IDManager
{
public:
	IDManager();
	~IDManager() = default;

	/**
	 * @brief 一意なIDを生成する
	 * @return 生成したID
	 */
	uint32_t GenerateID();

	/**
	 * @brief IDを解放する
	 * @param id 解放するID
	 */
	void ReleaseID(uint32_t id);

	/**
	 * @brief 全てのIDを解放する
	 */
	void Clear();

private:
	/// 次に新規生成するID
	uint32_t m_nextID;

	/// 生成済みで現在使用されていないID
	std::vector<uint32_t> m_freeIDs;
};
