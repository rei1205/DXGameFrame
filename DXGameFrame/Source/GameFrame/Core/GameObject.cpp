// GameObject.cpp
#include "GameObject.h"
#include "../Component/Transform.h"
#include "ComponentRegister.h"
#include "Scene.h"

GameObject::GameObject() :
	m_pScene(nullptr),
	m_pTransform(nullptr),
	m_guid(GUID_NULL),
	m_isActive(true),
	m_isDestroyed(false)
{
}

bool GameObject::IsActiveHierarchy() const
{
	// 非アクティブな場合再帰処理を終了
	if (!m_isActive || IsDestroyed())
		return false;

	// 親がない場合再帰処理を終了
	Transform* pParent = GetTransform()->GetParent();
	if (pParent == nullptr)
		return m_isActive;

	// 再帰的に有効状態を求める
	return pParent->GetGameObject()->IsActiveHierarchy();
}

void GameObject::Destroy()
{
	auto children = m_pTransform->GetChildren();
	for (auto& child : children)
	{
		child->GetGameObject()->Destroy();
	}

	m_isDestroyed = true;
}

void GameObject::OnDestroy()
{
	// 所持コンポーネントを全て削除
	while (!m_components.empty())
	{
		Component* component = m_components.back();
		m_pScene->GetComponentManager().RemoveComponent(component);
	}
}

void GameObject::Serialize(nlohmann::json& jsonData)
{
	wchar_t buffer[39];
	StringFromGUID2(m_guid, buffer, 39);
	std::wstring ws(buffer);
	std::string guid(ws.begin(), ws.end());
	jsonData["GUID"] = guid;

	jsonData["Name"] = m_name;
	jsonData["Active"] = m_isActive;
}

void GameObject::Deserialize(nlohmann::json& jsonData)
{
	std::string guidStr = jsonData["GUID"];
	std::wstring wGuidStr(guidStr.begin(), guidStr.end());
	HRESULT hr = CLSIDFromString(wGuidStr.c_str(), &m_guid);

	m_name = jsonData["Name"];
	m_isActive = jsonData["Active"];
}

void GameObject::SerializeComponents(nlohmann::json& jsonData)
{
	for(auto& component : m_components)
	{
		nlohmann::json compJson;
		uint32_t classID = component->GetClassID();
		compJson["ComponentType"] = ComponentRegister::GetComponentNameByClassID(classID);
		component->Serialize(compJson);
		jsonData["Components"].push_back(compJson);
	}
}

void GameObject::DeserializeComponents(nlohmann::json& jsonData)
{
	for(auto& compJson : jsonData["Components"])
	{
		std::string componentType = compJson.value("ComponentType", "ComponentName not found");
		if (componentType == "Transform")
		{
			GetTransform()->Deserialize(compJson);
			continue;
		}

		if (ComponentRegister::CreateComponent(componentType, this))
		{
			m_components.back()->Deserialize(compJson);
		}
	}
}

void GameObject::RegisterComponent(Component* pComponent)
{
	m_components.push_back(pComponent);
}

void GameObject::UnregisterComponent(Component* pComponent)
{
	auto it = std::find(m_components.begin(), m_components.end(), pComponent);
	if (it != m_components.end())
		m_components.erase(it);
}