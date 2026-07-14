// Scene.h
#pragma once
#include "Scene.h"

/**
 * @brief シーンの管理を行う
 */
class SceneManager
{
public:
	/**
	 * @brief 初期化処理
	 */
	static void Init();

	/**
	 * @brief 終了処理
	 */
	static void Uninit();

	/**
	 * @brief アクティブなシーンの時間を進める
	 */
	static void Execute();

	/**
	 * @brief シーンを変更する
	 * @details 同じフレームで複数回呼ばれた場合は最初に呼ばれたものが有効になります
	 * @param filePath シーンファイルへのパス
	 */
	static void ChangeScene(const std::string& filePath);

	/**
	 * @brief 現在のアクティブなシーンを取得する
	 * @return アクティブなシーンへのポインタ
	 */
	static Scene* GetActiveScene()
	{
		return s_pActiveScene.get();
	}

	/**
	 * @brief 現在のシーン名を取得する
	 * @return シーン名
	 */
	static std::string GetCurrentSceneName();

	/**
	 * @brief 現在のシーンファイルへのパスを取得する
	 * @return シーンファイルへのパス
	 */
	static std::string GetCurrentSceneFilePath()
	{
		return s_currentSceneFilePath;
	}

	/**
	 * @brief シーンをシリアライズする
	 * フレーム処理中に呼ばないでください
	 * @param filePath シーンファイルへのパス
	 */
	static void SerializeScene(const std::string& filePath);

	/**
	 * @brief シーンをデシリアライズする
	 * フレーム処理中に呼ばないでください
	 * @param filePath シーンファイルへのパス
	 * @return 成功したかを返す
	 */
	static bool DeserializeScene(const std::string& filePath);

	/**
	 * @brief シーンの変更を適用する
	 * フレーム処理中に呼ばないでください
	 */
	static void ApplyChangeScene();

private:
	/// 現在のシーン
	static std::unique_ptr<Scene> s_pActiveScene;

	/// シーン変更フラグ
	static bool s_sceneChangeFlag;

	/// 現在のシーンファイルへのパス
	static std::string s_currentSceneFilePath;

	/// 変更先シーンファイルへのパス
	static std::string s_nextSceneFilePath;
};