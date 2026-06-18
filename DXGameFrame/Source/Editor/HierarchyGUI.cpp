// HierarchyGUI.cpp
#include "HierarchyGUI.h"
#include "Editor.h"
#include <ImGui/imgui.h>

HierarchyGUI::HierarchyGUI() :
    EditorWindow("Hierarchy")
{
}

void HierarchyGUI::OnGUI()
{
    Scene* pScene = Editor::GetTargetScene();
	if (pScene == nullptr)
		return;

    auto& gameObjects = pScene->GetGameObjectManager().GetGameObjects();

    // ウィンドウ上の右クリックメニュー
    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::MenuItem("Create Empty"))
        {
            GameObject::Create(pScene);
        }

        ImGui::EndPopup();
    }

    // メイン描画
    bool open = DrawRootNode();
    if (open)
    {
        for (auto& obj : gameObjects)
        {
            // 親が存在する場合処理スキップ
            if (obj->GetTransform()->GetParent() != nullptr)
                continue;

            DrawNode(obj->GetTransform());
        }

        ImGui::TreePop();
    }
}

bool HierarchyGUI::DrawRootNode()
{
    Scene* pScene = Editor::GetTargetScene();
    if (pScene == nullptr)
        return false;
    auto& gameObjects = pScene->GetGameObjectManager().GetGameObjects();

    // 動作設定
    ImGuiTreeNodeFlags flags =
        ImGuiTreeNodeFlags_OpenOnArrow |
        ImGuiTreeNodeFlags_OpenOnDoubleClick |
        ImGuiTreeNodeFlags_SpanAvailWidth;

    // オブジェクトがない場合の設定
    if (gameObjects.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    bool open = ImGui::TreeNodeEx(pScene, flags, "Scene");

    // 選択時の処理
    if (ImGui::IsItemClicked())
    {
        Editor::SetTargetGameObject(nullptr);
    }

    // ドロップ先
    if (ImGui::BeginDragDropTarget())
    {
        const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(
            "HIERARCHY_NODE", ImGuiDragDropFlags_AcceptNoDrawDefaultRect);
        if (payload != nullptr)
        {
            Transform* drag = *(Transform**)payload->Data;
            drag->SetParent((GameObject*)nullptr);
        }

        ImGui::EndDragDropTarget();
    }

    return open;
}

void HierarchyGUI::DrawNode(Transform* pTransform)
{
    auto children = pTransform->GetChildren();

    // 動作設定
    ImGuiTreeNodeFlags flags =
        ImGuiTreeNodeFlags_OpenOnArrow |
        ImGuiTreeNodeFlags_OpenOnDoubleClick |
        ImGuiTreeNodeFlags_SpanAvailWidth;

    if (children.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    bool selected = pTransform->GetGameObject() == Editor::GetTargetGameObject();
    if (selected)
    {
        // 選択中スタイル
        flags |= ImGuiTreeNodeFlags_Selected;
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImGui::GetStyle().Colors[ImGuiCol_Header]);
    }

    // ノード作成
    bool open = ImGui::TreeNodeEx(pTransform, flags, pTransform->GetGameObject()->GetName().c_str());
    NodeInteraction(pTransform);

    if (selected)
        ImGui::PopStyleColor();

    // 子を再帰的に描画
    if (open)
    {
        for (auto* child : children)
        {
            DrawNode(child);
        }
        ImGui::TreePop();
    }
}

void HierarchyGUI::NodeInteraction(Transform* pTransform)
{
    // 選択時の処理
    if (ImGui::IsItemClicked())
    {
        Editor::SetTargetGameObject(pTransform->GetGameObject());
    }

    // 右クリックメニュー
    if (ImGui::BeginPopupContextItem())
    {
        Editor::SetTargetGameObject(pTransform->GetGameObject());

        if (ImGui::MenuItem("Create Empty"))
        {
        }

        if (ImGui::MenuItem("Delete"))
        {

        }

        ImGui::EndPopup();
    }

    // 色を取得
    ImGuiStyle& style = ImGui::GetStyle();
    ImU32 targetColor = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Header]);
    ImU32 hoveredColor = ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_HeaderHovered]);

    // カーソルの位置を取得
    ImVec2 min = ImGui::GetItemRectMin();
    ImVec2 max = ImGui::GetItemRectMax();
    float mouseY = ImGui::GetMousePos().y;
    float height = max.y - min.y;
    float ratio = (mouseY - min.y) / height;


    // ドロップ挙動を取得
    DropType dropType;
    if (ratio < 0.25f)
    {
        dropType = DropType::BEFORE;
    }
    else if (ratio > 0.75f)
    {
        dropType = DropType::AFTER;
    }
    else
    {
        dropType = DropType::CHILD;
    }

    // ドラッグ元
    if (ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload("HIERARCHY_NODE", &pTransform, sizeof(pTransform));
        ImGui::Text("%s", pTransform->GetGameObject()->GetName().c_str());
        ImGui::EndDragDropSource();
    }

    // ドロップ先
    if (ImGui::BeginDragDropTarget())
    {
        const ImGuiPayload* payload;
        payload = ImGui::AcceptDragDropPayload("HIERARCHY_NODE",
            ImGuiDragDropFlags_AcceptNoDrawDefaultRect);

        // 親子関係を移動
        if (payload != nullptr)
        {
            Transform* drag = *(Transform**)payload->Data;
            if (!IsAncestorOf(drag, pTransform))
                DropObject(drag, pTransform, dropType);
        }
        ImGui::EndDragDropTarget();

        // 上下線描画
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        switch (dropType)
        {
        case DropType::BEFORE:
            drawList->AddLine(ImVec2(min.x, min.y), ImVec2(max.x, min.y), targetColor, 2.0f);
            break;

        case DropType::AFTER:
            drawList->AddLine(ImVec2(min.x, max.y), ImVec2(max.x, max.y), targetColor, 2.0f);
            break;

        case DropType::CHILD:
            drawList->AddRectFilled(min, max, hoveredColor);
            break;
        }
    }
}

void HierarchyGUI::DropObject(Transform* drag, Transform* target, DropType dropType)
{
    Scene* pScene = Editor::GetTargetScene();
    if (pScene == nullptr)
        return;

    // 操作先インデックスを取得
    size_t index = 0;
    if (!pScene->GetGameObjectManager().GetElementIndex(target->GetGameObject(), &index))
        return;

    // オブジェクト移動
    switch (dropType)
    {
    case DropType::BEFORE:
        pScene->GetGameObjectManager().MoveElementIndex(drag->GetGameObject(), index);
        drag->SetParent(target->GetParent());
        break;

    case DropType::AFTER:
        pScene->GetGameObjectManager().MoveElementIndex(drag->GetGameObject(), index + 1);
        drag->SetParent(target->GetParent());
        break;

    case DropType::CHILD:
        pScene->GetGameObjectManager().MoveElementIndex(drag->GetGameObject(), index + 1);
        drag->SetParent(target);
        break;
    }

    // 子要素の並び替え
    Transform* parent = drag->GetParent();
    if (parent != nullptr)
    {
        auto children = parent->GetChildren();

        if (dropType == DropType::CHILD)
        {
            parent->MoveChildIndex(drag, parent->GetChildren().size() - 1);
        }
        else
        {
            // 移動先インデックスを取得
            size_t childIndex = 0;
            if (!parent->GetChildIndex(target, &childIndex))
                return;

            if (dropType == DropType::BEFORE)
            {
                parent->MoveChildIndex(drag, childIndex);
            }
            else if (dropType == DropType::AFTER)
            {
                parent->MoveChildIndex(drag, childIndex + 1);
            }
        }
    }
}

bool HierarchyGUI::IsAncestorOf(Transform* ancestor, Transform* target)
{
    Transform* current = target;

    while (current)
    {
        if (current == ancestor)
            return true;

        current = current->GetParent();
    }

    return false;
}
