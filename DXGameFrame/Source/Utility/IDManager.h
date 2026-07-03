// IDManager.h
#pragma once
#include <unordered_set>

/**
 * @brief 一意なIDの生成・管理を行う
 */
class IDManager
{
public:
	IDManager(bool useZero = true);
	~IDManager() = default;

	/**
	 * @brief 一意なIDを生成する
	 * @return 生成したID
	 */
	uint32_t GenerateID();
	
	/**
	 * @brief 任意のIDを登録する
	 * @param id 登録するID
	 * @return 既にIDが使用されていた場合falseを返す
	 */
	bool RegisterID(uint32_t id);

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

	/// 生成済みID
	std::unordered_set<uint32_t> m_generatedIDs;

	/// 生成済みで現在使用されていないID
	std::vector<uint32_t> m_freeIDs;

	/// IDの0番を使用するかの設定
	bool m_useZero = false;
};
