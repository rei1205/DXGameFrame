// HierarchyGUI.h
#pragma once
#include "EditorWindow.h"
#include "../GameFrame/Component/Transform.h"
#include <functional>

/**
 * @brief オブジェクト階層のGUI
 */
class HierarchyGUI : public EditorWindow
{
public:
	HierarchyGUI();
	~HierarchyGUI() = default;
	
private:
	/// ドロップ挙動
	enum class DropType
	{
		BEFORE,     // 上
		AFTER,      // 下
		CHILD       // 子要素
	};

	/// ゲームオブジェクト操作イベント
	std::function<void()> m_operationEvent;

	/**
	 * @brief GUIの描画を行う
	 */
	void OnGUI() override;

	/**
	 * @brief 最上位のノードを描画する
	 * @return 開閉フラグ
	 */
	bool DrawRootNode();

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
	 * @brief ノードドロップ時の処理
	 * @param drag ドラッグ中ノードのTransformへのポインタ
	 * @param target ターゲットノードのTransformへのポインタ
	 * @param dropType ドロップ挙動
	 */
	void DropObject(Transform* drag, Transform* target, DropType dropType);

	/**
	 * @brief 親以上に指定したTransformがあるか判定する
	 * @param ancestor 検索対象のTransformへのポインタ
	 * @param target 元のTransformへのポインタ
	 * @return 親以上に存在すればtrueを返す
	 */
	bool IsAncestorOf(Transform* ancestor, Transform* target);
};
