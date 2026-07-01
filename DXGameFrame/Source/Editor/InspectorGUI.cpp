// Inspector.cpp
#include "InspectorGUI.h"
#include "Editor.h"
#include "../GameFrame/Core/GameObject.h"
#include "../GameFrame/Core/ComponentRegister.h"
#include <ImGui/imgui.h>

InspectorGUI::InspectorGUI() :
	EditorWindow("インスペクター")
{
}

void InspectorGUI::OnGUI()
{
	GameObject* pGameObject = Editor::GetTargetGameObject();
	if (pGameObject == nullptr)
		return;
	auto components = pGameObject->GetComponents();
	
	// ゲームオブジェクト情報
	GameObjectGUI();

	// コンポーネント描画
	for (auto& component : components)
	{
		ComponentGUI(component);
		ImGui::Dummy(ImVec2(0, 5));
		ImGui::Separator();
	}

	// コンポーネント追加ボタン
	AddComponentButton();

	// コンポーネント操作イベントの処理
	if (m_operationEvent != nullptr)
	{
		m_operationEvent();
		m_operationEvent = nullptr;
	}
}

void InspectorGUI::GameObjectGUI()
{
	GameObject* pGameObject = Editor::GetTargetGameObject();
	bool isActive = pGameObject->IsActiveSelf();

	// アクティブ状態設定
	if (ImGui::Checkbox("##Active", &isActive))
	{
		pGameObject->SetActive(isActive);
	}

	// 名前入力欄
	ImGui::SameLine();
	static char name[64] = "";
	strcpy_s(name, sizeof(name), pGameObject->GetName().c_str());
	if (ImGui::InputTextWithHint("##Name", "Name...", name, sizeof(name)))
	{
		pGameObject->SetName(name);
	}
	ImGui::Separator();
}

void InspectorGUI::ComponentGUI(Component* pComponent)
{
	// 動作設定
	ImGuiTreeNodeFlags flags =
		ImGuiTreeNodeFlags_DefaultOpen |
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth;

	bool isTransform = pComponent->GetClassID() == ClassID<Transform>::GetID();
	bool isEnable = pComponent->IsEnabled();
	
	// 有効状態設定
	if (isTransform)
	{
		ImGui::Dummy(ImVec2(ImGui::GetFrameHeight(), 0));
	}
	else
	{
		ImGui::PushID(pComponent);
		if (ImGui::Checkbox("##Enable", &isEnable))
		{
			pComponent->SetEnabled(isEnable);
		}
		ImGui::PopID();
	}
	ImGui::SameLine();

	// コンポーネント名
	std::string name = ComponentRegister::GetComponentNameByClassID(pComponent->GetClassID());
	bool open = ImGui::TreeNodeEx(pComponent, flags, name.c_str());

	// 右クリックメニュー
	if (!isTransform && ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Remove"))
		{
			m_operationEvent = [pComponent]()
				{
					pComponent->Destroy();
				};
		}
		ImGui::EndPopup();
	}

	if (open)
	{
		pComponent->OnInspectorGUI();
		ImGui::TreePop();
	}
}

void InspectorGUI::AddComponentButton()
{
	GameObject* pGameObject = Editor::GetTargetGameObject();
	auto componentNames = ComponentRegister::GetComponentNames();

	ImVec2 size(160, 26);
	float centerX = ImGui::GetWindowWidth() * 0.5f;
	float posX = centerX - size.x * 0.5f;

	// コンポーネント追加ボタン
	ImGui::Dummy(ImVec2(0, 10));
	ImGui::SetCursorPosX(posX);
	if (ImGui::Button("Add Component", size))
	{
		ImGui::OpenPopup("AddComponentPopup");
	}

	// コンポーネント追加ポップアップ
	if (ImGui::BeginPopup("AddComponentPopup"))
	{
		// 検索欄
		static char filter[64] = "";
		ImGui::InputTextWithHint("##Filter", "Search...", filter, sizeof(filter));
		ImGui::Separator();

		for (auto& name : componentNames)
		{
			// Transformは除外
			if (name == "Transform")
				continue;

			// 名前検索
			if (filter[0] != '\0' && name.find(filter) == std::string::npos)
				continue;

			// コンポーネントリスト
			if (ImGui::MenuItem(name.c_str()))
			{
				m_operationEvent = [name, pGameObject]()
					{
						ComponentRegister::CreateComponent(name, pGameObject);
					};

				ImGui::CloseCurrentPopup();
			}
		}

		ImGui::EndPopup();
	}
}
