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
	 * @brief コンポーネント情報の描画を行う
	 */
	void DrawComponent(Component* pComponent);

	/**
	 * @brief コンポーネント追加ボタンのGUI
	 */
	void AddComponentButton();
};