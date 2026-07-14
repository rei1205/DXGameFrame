// AssetWindowGUI.cpp
#include "AssetWindowGUI.h"
#include <ImGui/imgui.h>

AssetWindowGUI::AssetWindowGUI():
	EditorWindow("アセット")
{
    Refresh();
}

void AssetWindowGUI::OnGUI()
{
    if (ImGui::Button("Refresh"))
        Refresh();

    if (m_root != nullptr)
        DrawNode(m_root.get());
}

void AssetWindowGUI::DrawNode(const AssetNode* pNode)
{
    std::string name = pNode->path.filename().string();

    if (pNode->isFolder)
    {
        // 再帰的にツリー描画
        if (ImGui::TreeNode(name.c_str()))
        {
            for (auto& child : pNode->children)
                DrawNode(child.get());

            ImGui::TreePop();
        }
    }
    else
    {
        ImGui::Selectable(name.c_str());

        // ドラッグ元設定
        if (ImGui::BeginDragDropSource())
        {
            std::string path = pNode->path.string();
            ImGui::SetDragDropPayload("ASSET_PATH", path.c_str(), path.size() + 1);
            ImGui::Text("%s", name.c_str());
            ImGui::EndDragDropSource();
        }
    }
}

void AssetWindowGUI::Refresh()
{
	// アセットノードを再構築
    m_root = std::move(BuildAssetNode("Assets"));
}

std::unique_ptr<AssetNode> AssetWindowGUI::BuildAssetNode(const std::filesystem::path& path)
{
    auto node = std::make_unique<AssetNode>();

    node->path = path;
    node->isFolder = std::filesystem::is_directory(path);

    if (!node->isFolder)
        return node;

	// アセットノードを再帰的に構築
    std::error_code errorCode;
    for (const auto& entry : std::filesystem::directory_iterator(path, errorCode))
    {
        if (errorCode) continue;

        node->children.push_back(
            BuildAssetNode(entry.path())
        );
    }

    return node;
}