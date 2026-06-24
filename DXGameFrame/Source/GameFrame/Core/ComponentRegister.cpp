// ComponentRegister.h
#include "ComponentRegister.h"
#include "Scene.h"

void ComponentRegister::Register(const std::string& name, uint32_t classID,
	std::function<void(ComponentManager*, GameObject*)> createFunc)
{
	auto& componentInfos = GetComponentInfos();
	auto& nameMap = GetNameMap();
	auto& idMap = GetIDMap();

	if (nameMap.contains(name))
		return;

	// コンポーネント情報登録
	auto newInfo = std::make_unique<ComponentInfo>();
	newInfo->name = name;
	newInfo->classID = classID;
	newInfo->createFunc = createFunc;
	ComponentInfo* ptr = newInfo.get();
	componentInfos.push_back(std::move(newInfo));
	nameMap[name] = ptr;
	idMap[classID] = ptr;

}

void ComponentRegister::CreateComponent(const std::string& name, GameObject* pGameObject)
{
	auto& nameMap = GetNameMap();

	if (!nameMap.contains(name))
		return;

	ComponentManager* pManager = &pGameObject->GetScene()->GetComponentManager();
	nameMap[name]->createFunc(pManager, pGameObject);
}

std::string ComponentRegister::GetComponentNameByClassID(uint32_t classID)
{
	auto& idMap = GetIDMap();

	if (!idMap.contains(classID))
		return "ComponentName not found";

	return idMap[classID]->name;
}

std::vector<std::string> ComponentRegister::GetComponentNames()
{
	auto& nameMap = GetNameMap();

	// コンポーネント名を取得
	std::vector<std::string> result;
	for (auto pair : nameMap)
	{
		result.push_back(pair.first);
	}
	return result;
}

std::vector<std::unique_ptr<ComponentRegister::ComponentInfo>>& ComponentRegister::GetComponentInfos()
{
	// コンポーネント登録情報のリスト
	static std::vector<std::unique_ptr<ComponentInfo>> s_componentInfos;
	return s_componentInfos;
}

std::unordered_map<std::string, const ComponentRegister::ComponentInfo*>& ComponentRegister::GetNameMap()
{
	// コンポーネント名のマップ
	static std::unordered_map<std::string, const ComponentInfo*> s_nameMap;
	return s_nameMap;
}

std::unordered_map<uint32_t, const ComponentRegister::ComponentInfo*>& ComponentRegister::GetIDMap()
{
	// クラスIDのマップ
	static std::unordered_map<uint32_t, const ComponentInfo*> s_idMap;
	return s_idMap;
}
