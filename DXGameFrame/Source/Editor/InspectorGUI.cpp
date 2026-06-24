// Inspector.cpp
#include "InspectorGUI.h"
#include "Editor.h"
#include "../GameFrame/Core/GameObject.h"
#include "../GameFrame/Core/ComponentRegister.h"
#include <ImGui/imgui.h>

InspectorGUI::InspectorGUI() :
	EditorWindow("Inspector")
{
}

void InspectorGUI::OnGUI()
{
	GameObject* pGameObject = Editor::GetTargetGameObject();
	if (pGameObject == nullptr)
		return;
	auto components = pGameObject->GetComponents();

	// コンポーネント描画
	for (auto& component : components)
	{
		DrawComponent(component);
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

void InspectorGUI::DrawComponent(Component* pComponent)
{
	// 動作設定
	ImGuiTreeNodeFlags flags =
		ImGuiTreeNodeFlags_DefaultOpen |
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth;

	// コンポーネント描画
	std::string name = ComponentRegister::GetComponentNameByClassID(pComponent->GetClassID());
	bool open = ImGui::TreeNodeEx(pComponent, flags, name.c_str());

	// 右クリックメニュー
	if (pComponent->GetClassID() != ClassID<Transform>::GetID() &&
		ImGui::BeginPopupContextItem())
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

	if (ImGui::Button("Add Component"))
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
