// InspectorGUI.h
#pragma once
#include "EditorWindow.h"
#include "../GameFrame/Core/Component.h"
#include <functional>

/**
 * @brief オブジェクト詳細のGUI
 */
class InspectorGUI : public EditorWindow
{
public:
	InspectorGUI();
	~InspectorGUI() = default;

private:
	/// コンポーネント操作イベント
	std::function<void()> m_operationEvent;
	
	/**
	 * @brief GUIの描画を行う
	 */
	void OnGUI() override;

	/**
	 * @brief ゲームオブジェクト情報のGUI
	 */
	void GameObjectGUI();

	/**
	 * @brief コンポーネント情報のGUI
	 * @param pComponent コンポーネントへのポインタ
	 */
	void ComponentGUI(Component* pComponent);

	/**
	 * @brief コンポーネント追加ボタンのGUI
	 */
	void AddComponentButton();
};