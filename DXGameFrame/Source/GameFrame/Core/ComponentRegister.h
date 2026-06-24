// ComponentRegister.h
#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

class ComponentManager;
class GameObject;

/**
 * @brief コンポーネント登録情報の管理を行う
 */
class ComponentRegister
{
public:
	/**
	 * @brief コンポーネント情報を登録する
	 * @param name コンポーネント名
	 * @param classID クラスID
	 * @param createFunc 生成関数
	 */
	static void Register(const std::string& name, uint32_t classID, 
		std::function<void(ComponentManager*, GameObject*)> createFunc);

	/**
	 * @brief 名前からコンポーネントを生成する
	 * @param name コンポーネント名
	 * @param pGameObject ゲームオブジェクトへのポインタ
	 */
	static void CreateComponent(const std::string& name, GameObject* pGameObject);

	/**
	 * @brief クラスIDからコンポーネント名を取得する
	 * @param classID クラスID
	 * @return コンポーネント名
	 */
	static std::string GetComponentNameByClassID(uint32_t classID);

	/**
	 * @brief コンポーネント名の一覧を取得する
	 * @return コンポーネント名配列
	 */
	static std::vector<std::string> GetComponentNames();

private:
	ComponentRegister() = delete;

	/// コンポーネント登録情報
	struct ComponentInfo
	{
		/// コンポーネント名
		std::string name;

		/// クラスID
		uint32_t classID;

		/// 生成関数
		std::function<void(ComponentManager*, GameObject*)> createFunc;
	};

	static std::vector<std::unique_ptr<ComponentInfo>>& GetComponentInfos();
	static std::unordered_map<std::string, const ComponentInfo*>& GetNameMap();
	static std::unordered_map<uint32_t, const ComponentInfo*>& GetIDMap();
};
