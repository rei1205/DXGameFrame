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

    // メイン描画
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

void HierarchyGUI::DrawRootNode()
{
    Scene* pScene = Editor::GetTargetScene();
    if (pScene == nullptr)
        return;
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
}

void HierarchyGUI::DrawNode(Transform* pTransform)
{
    auto children = pTransform->GetChildren();

    // 動作設定
    ImGuiTreeNodeFlags flags =
        ImGuiTreeNodeFlags_OpenOnArrow |
        ImGuiTreeNodeFlags_OpenOnDoubleClick |
        ImGuiTreeNodeFlags_SpanAvailWidth;

    bool selected = pTransform->GetGameObject() == Editor::GetTargetGameObject();
    if (selected)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImGui::GetStyle().Colors[ImGuiCol_Header]);
    }

    if (children.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

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

    // ドロップ挙動
    enum class DropType
    {
        BEFORE,     // 上
        AFTER,      // 下
        CHILD       // 子要素
    };

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
            {
                switch (dropType)
                {
                case DropType::BEFORE:
                    drag->SetParent(pTransform->GetParent());
                    break;

                case DropType::AFTER:
                    drag->SetParent(pTransform->GetParent());
                    break;

                case DropType::CHILD:
                    drag->SetParent(pTransform);
                    break;
                }
            }
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
