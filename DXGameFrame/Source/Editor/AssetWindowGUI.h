// AssetWindowGUI.h
#pragma once
#include "EditorWindow.h"
#include <vector>
#include <filesystem>
#include <memory>

/// アセット階層情報
struct AssetNode
{
	/// 現在のパス
	std::filesystem::path path;

	/// フォルダフラグ
	bool isFolder = false;

	/// 子要素
	std::vector<std::unique_ptr<AssetNode>> children;
};

class AssetWindowGUI : public EditorWindow
{
public:
	AssetWindowGUI();
	~AssetWindowGUI() = default;

private:
	/// ルートアセットノード
	std::unique_ptr<AssetNode> m_root;

    /**
	 * @brief GUIの描画を行う
	 */
	void OnGUI() override;

	/**
	 * @brief アセットノードの描画を再帰的に行う
	 * @param pNode 現在のノードへのポインタ
	 */
	void DrawNode(const AssetNode* pNode);

	/**
	 * @brief アセットフォルダ構成の再読み込み
	 */
	void Refresh();

	/**
	 * @brief アセット階層情報を再帰的に構築する
	 * @param path 現在のパス
	 * @return 作成したノードへのポインタ (unique_ptr)
	 */
	std::unique_ptr<AssetNode> BuildAssetNode(const std::filesystem::path& path);
};
