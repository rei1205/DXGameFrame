// GameTime.cpp
#include "GameTime.h"

GameTime::TimePoint GameTime::s_startTimePoint;
GameTime::TimePoint GameTime::s_lastTimePoint;
unsigned int GameTime::s_targetFPS;
float GameTime::s_processingTime;
float GameTime::s_deltaTime;

void GameTime::Init(unsigned int targetFPS)
{
	s_targetFPS = targetFPS;
	s_startTimePoint = std::chrono::steady_clock::now();
	s_lastTimePoint = s_startTimePoint;
}

void GameTime::Update()
{
	// ‡Œvˆ—ŠÔ‚ğ‹‚ß‚é
	TimePoint current = std::chrono::steady_clock::now();
	s_processingTime = std::chrono::duration<float>(current - s_lastTimePoint).count();

	if (s_targetFPS != 0)
	{
		// FPSŒÅ’è
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
}
