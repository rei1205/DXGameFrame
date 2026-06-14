// GameTime.h
#pragma once
#include <chrono>

/**
 * @brief 時間管理・FPS制御を行うクラス
 */
class GameTime
{
public:
	/**
	 * @brief 初期化処理
	 * @param targetFPS 目標FPS
	 */
	static void Init(unsigned int targetFPS);

	/**
	 * @brief 時間を更新して目標FPSまで待機する
	 */
	static void Update();

	/**
	 * @brief FPSを設定する
	 * @param targetFPS 目標FPS
	 */
	static void SetTargetFPS(unsigned int targetFPS)
	{
		s_targetFPS = targetFPS;
	}

	/**
	 * @brief 初期化時点からの経過時間を取得する
	 * @return 合計経過時間
	 */
	static float GetTotalTime()
	{
		return std::chrono::duration<float>(s_lastTimePoint - s_startTimePoint).count();
	}

	/**
	 * @brief 前のフレームからの経過時間を取得する
	 * @return 前のフレームからの経過時間
	 */
	static float GetDeltaTime()
	{
		return s_deltaTime;
	}

	/**
	 * @brief 前のフレームからの処理時間を取得する
	 * @return 前のフレームからの処理時間
	 */
	static float GetProssingTime()
	{
		return s_processingTime;
	}

	/**
	 * @brief 処理時間表示設定を行う
	 * @param showFPS 処理時間表示設定
	 */
	static void SetShowProssingTime(bool showProssingTime)
	{
		s_showProssingTime = showProssingTime;
	}

private:
	using TimePoint = std::chrono::steady_clock::time_point;

	/// 開始時間
	static TimePoint s_startTimePoint;

	/// 最終実行時間
	static TimePoint s_lastTimePoint;

	/// 目標FPS
	static unsigned int s_targetFPS;

	/// 前のフレームからの処理時間
	static float s_processingTime;

	/// 前のフレームからの経過時間
	static float s_deltaTime;
	
	/// 処理時間表示フラグ
	static bool s_showProssingTime;

	/**
	 * @brief 平均処理時間を表示する
	 */
	static void ShowProssingTime();
};
