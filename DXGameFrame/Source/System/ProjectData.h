// ProjectData.h
#pragma once
#include <string>

/**
 * @brief プロジェクト単位のデータを管理する
 */
class ProjectData
{
public:
	/**
	 * @brief プロジェクトデータを保存する
	 */
	static void Save();

	/**
	 * @brief プロジェクトデータを読み込む
	 * @return 成功したかを返す
	 */
	static bool Load();

	/**
	 * @brief プロジェクト名を設定する
	 * @param name プロジェクト名
	 */
	static void SetProjectName(const std::string& name)
	{
		s_projectName = name;
	}

	/**
	 * @brief プロジェクト名を取得する
	 * @return プロジェクト名
	 */
	static std::string GetProjectName()
	{
		return s_projectName;
	}

	/**
	 * @brief ゲーム画面の幅を設定する
	 * @return ゲーム画面の幅
	 */
	static void SetScreenWidth(int width)
	{
		s_screenWidth = width;
	}

	/**
	 * @brief ゲーム画面の幅を取得する
	 * @return ゲーム画面の幅
	 */
	static int GetScreenWidth()
	{
		return s_screenWidth;
	}

	/**
	 * @brief ゲーム画面の高さを設定する
	 * @param height ゲーム画面の高さ
	 */
	static void SetScreenHeight(int height)
	{
		s_screenHeight = height;
	}

	/**
	 * @brief ゲーム画面の高さを取得する
	 * @return ゲーム画面の高さ
	 */
	static int GetScreenHeight()
	{
		return s_screenHeight;
	}

	/**
	 * @brief フルスクリーン設定を行う
	 * @param isFullScreen フルスクリーン設定
	 */
	static void SetFullScreen(bool isFullScreen)
	{
		s_isFullScreen = isFullScreen;
	}

	/**
	 * @brief フルスクリーン設定を取得する
	 * @return フルスクリーン設定
	 */
	static bool IsFullScreen()
	{
		return s_isFullScreen;
	}

	/**
	 * @brief 動作FPSを設定する
	 * @param fps FPS値
	 */
	static void SetFPS(int fps)
	{
		s_fps = fps;
	}

	/**
	 * @brief 動作FPSを取得する
	 * @return FPS値
	 */
	static int GetFPS()
	{
		return s_fps;
	}

	/**
	 * @brief 開始シーンへのパスを設定する
	 * @param filePath シーンファイルへのパス
	 */
	static void SetStartScenePath(const std::string& filePath)
	{
		s_startScenePath = filePath;
	}

	/**
	 * @brief 開始シーンへのパスを取得する
	 * @return シーンファイルへのパス
	 */
	static std::string GetStartScenePath()
	{
		return s_startScenePath;
	}

	/**
	 * @brief 現在のエディタシーンへのパスを設定する
	 * @param filePath シーンファイルへのパス
	 */
	static void SetEditorScenePath(const std::string& filePath)
	{
		s_editorScenePath = filePath;
	}

	/**
	 * @brief 現在のエディタシーンへのパスを取得する
	 * @return シーンファイルへのパス
	 */
	static std::string GetEditorScenePath()
	{
		return s_editorScenePath;
	}

	/**
	 * @brief アセットフォルダへのパスを取得する
	 * @return アセットフォルダへのパス
	 */
	static std::string GetAssetsFolderPath()
	{
		return s_assetsFolderPath;
	}

	/**
	 * @brief エディタフォルダへのパスを取得する
	 * @return エディタフォルダへのパス
	 */
	static std::string GetEditorFolderPath()
	{
		return s_editorFolderPath;
	}

private:
	ProjectData() = delete;
	
	/// プロジェクト名
	static std::string s_projectName;

	/// ゲーム画面の幅
	static int s_screenWidth;

	/// ゲーム画面の高さ
	static int s_screenHeight;

	/// フルスクリーン設定
	static bool s_isFullScreen;

	/// FPS設定
	static int s_fps;

	/// 開始シーンへのパス
	static std::string s_startScenePath;

	/// 現在のエディタシーンへのパス
	static std::string s_editorScenePath;

	/// アセットフォルダのパス
	static const std::string s_assetsFolderPath;

	/// エディタフォルダのパス
	static const std::string s_editorFolderPath;
};
