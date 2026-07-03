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
	 * @param pNextScene 次のシーン
	 */
	static void ChangeScene(Scene* pNextScene);

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
	static Scene* GetActiveScene();

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
	 */
	static void DeserializeScene(const std::string& filePath);

private:
	/// 現在のシーン
	static Scene* s_pActiveScene;

	/// 変更先シーン
	static Scene* s_pNextScene;

	/// シーン配列
	static std::vector<std::unique_ptr<Scene>> s_sceneList;

	/**
	 * @brief シーンの変更を適用する
	 */
	static void ApplyChangeScene();
};