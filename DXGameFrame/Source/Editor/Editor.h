// Editor.h
#pragma once
#include "EditorWindow.h"
#include "../GameFrame/Core/Scene.h"
#include "../GameFrame/Core/ObjPtr.h"

/**
 * @brief エディタGUIを扱う
 */
class Editor
{
public:
	/**
	 * @brief エディタの初期化処理
	 */
	static void Init();
	
	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief 更新処理
	 */
	static void Execute();

	/**
	 * @brief 操作対象シーンを設定する
	 * @param pScene 操作対象シーンへのポインタ
	 */
	static void SetTargetScene(Scene* pScene)
	{
		s_pTargetScene = pScene;
	}

	/**
	 * @brief 操作対象シーンを取得する
	 * @return 操作対象シーンへのポインタ
	 */
	static Scene* GetTargetScene()
	{
		return s_pTargetScene;
	}

	/**
	 * @brief 操作対象ゲームオブジェクトを設定する
	 * @param pGameObject 操作対象ゲームオブジェクトへのポインタ
	 */
	static void SetTargetGameObject(GameObject* pGameObject)
	{
		s_pTargetGameObject = pGameObject;
	}

	/**
	 * @brief 操作対象ゲームオブジェクトを取得する
	 * @return 操作対象ゲームオブジェクトへのポインタ
	 */
	static GameObject* GetTargetGameObject()
	{
		return s_pTargetGameObject.Get();
	}

private:
	Editor() = delete;

	/// 操作対象シーン
	static Scene* s_pTargetScene;

	/// 操作対象ゲームオブジェクト
	static ObjPtr<GameObject> s_pTargetGameObject;

	/// エディタウィンドウ配列
	static std::vector<std::unique_ptr<EditorWindow>> s_editorWindows;

	/// 初期化済みフラグ
	static bool s_initialized;

	/**
	 * @brief ルートウィンドウのGUIを作成する
	 */
	static void RootWindowGUI();
};
