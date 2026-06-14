// GameTime.cpp
#include "GameTime.h"
#include "Debug.h"

GameTime::TimePoint GameTime::s_startTimePoint;
GameTime::TimePoint GameTime::s_lastTimePoint;
unsigned int GameTime::s_targetFPS;
float GameTime::s_processingTime;
float GameTime::s_deltaTime;
bool GameTime::s_showProssingTime = false;

void GameTime::Init(unsigned int targetFPS)
{
	s_targetFPS = targetFPS;
	s_startTimePoint = std::chrono::steady_clock::now();
	s_lastTimePoint = s_startTimePoint;
}

void GameTime::Update()
{
	// çáåvèàóùéûä‘ÇãÅÇﬂÇÈ
	TimePoint current = std::chrono::steady_clock::now();
	s_processingTime = std::chrono::duration<float>(current - s_lastTimePoint).count();

	if (s_targetFPS != 0)
	{
		// FPSå≈íË
		auto target = std::chrono::duration<double>(1.0 / s_targetFPS);
		while (true)
		{
			if (current - s_lastTimePoint >= target)
				break;

			current = std::chrono::steady_clock::now();
		}
	}

	s_deltaTime = std::chrono::duration<float>(current - s_lastTimePoint).count();
	s_lastTimePoint = current;

	// èàóùéûä‘ï\é¶
	if (s_showProssingTime)
		ShowProssingTime();
}

void GameTime::ShowProssingTime()
{
	const int showIntervalFrame = 300;
	static int frameCount = 0;
	static float sumProssingTime = 0.0f;

	frameCount++;
	sumProssingTime += GameTime::GetProssingTime() * 1000.0f;

	if (frameCount >= showIntervalFrame)
	{
		float avgTime = sumProssingTime / (float)showIntervalFrame;
		Debug::ConsoleLog(std::to_string(avgTime) + "ms");

		frameCount = 0;
		sumProssingTime = 0.0f;
	}
}
