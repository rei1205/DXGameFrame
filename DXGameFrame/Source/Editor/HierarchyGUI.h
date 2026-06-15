// HierarchyGUI.h
#pragma once
#include "EditorWindow.h"
#include "../GameFrame/Component/Transform.h"

/**
 * @brief オブジェクト階層のGUI
 */
class HierarchyGUI : public EditorWindow
{
public:
	HierarchyGUI();
	~HierarchyGUI() = default;

private:
	/**
	 * @brief GUIの描画を行う
	 */
	void OnGUI() override;

	/**
	 * @brief 最上位のノードを描画する
	 */
	void DrawRootNode();

	/**
	 * @brief 再帰的にツリー構造を描画する
	 * @param pTransform 基点となるTransformへのポインタ
	 */
	void DrawNode(Transform* pTransform);

	/**
	 * @brief ノードに対する操作
	 */
	void NodeInteraction(Transform* pTransform);

	/**
	 * @brief 親以上に指定したTransformがあるか判定する
	 * @param ancestor 検索対象のTransformへのポインタ
	 * @param target 元のTransformへのポインタ
	 * @return 親以上に存在すればtrueを返す
	 */
	bool IsAncestorOf(Transform* ancestor, Transform* target);
};
