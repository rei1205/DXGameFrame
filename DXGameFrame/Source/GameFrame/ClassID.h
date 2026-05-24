// ClassID.h
#pragma once
#include "../Utility/IDManager.h"

/**
 * @brief クラス固有ID管理の基底クラス
 */
class IClassID
{
protected:
	// ID管理機能取得
	static IDManager& GetIDManager()
	{
		static IDManager s_idManager;
		return s_idManager;
	}

private:
	IClassID() = delete;
};

/**
 * @brief クラス固有IDを設定するクラス
 */
template <typename T>
class ClassID : public IClassID
{
public:
	/**
	 * @brief クラス固有IDを取得する
	 * @return クラスごとに一意なID
	 */
	static uint32_t GetID()
	{
		static bool s_isfirst = true;
		static uint32_t s_classID;
		if (s_isfirst)
		{
			// IDを生成
			s_classID = GetIDManager().GenerateID();
			s_isfirst = false;
		}

		return s_classID;
	}

private:
	ClassID() = delete;
};