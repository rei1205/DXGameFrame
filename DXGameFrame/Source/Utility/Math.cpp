// Math.cpp
#include "Math.h"
#include <cmath>

bool Math::Approximately(float a, float b)
{
	return std::fabs(a - b) <= Epsilon;
}

float Math::Clamp(float min, float max, float value)
{
	if (value < min) return min;
	if (value > max) return max;

	return value;
}

float Math::Clamp01(float value)
{
	if (value < 0.0f) return 0.0f;
	if (value > 1.0f) return 1.0f;

	return value;
}

float Math::Lerp(float a, float b, float t)
{
	t = Clamp01(t);
	return a + (b - a) * t;
}

float Math::MoveTowards(float current, float target, float maxDelta)
{
	if (maxDelta < 0.0f)
		maxDelta = -maxDelta;

	float delta = target - current;

	// 目標値クランプ
	if (std::fabs(delta) <= maxDelta)
		return target;

	// 目標値に向けて移動した値を返す
	return current + (delta > 0 ? maxDelta : -maxDelta);
}

float Math::MoveTowardsAngle(float current, float target, float maxDelta)
{
	if (maxDelta < 0.0f)
		maxDelta = -maxDelta;

	float delta = DeltaAngle(current, target);

	// 目標値クランプ
	if (std::fabs(delta) <= maxDelta)
		return target;

	// 目標角に向けて回転した値を返す
	return current + (delta > 0 ? maxDelta : -maxDelta);
}

float Math::DegToRad(float deg)
{
	return deg * Deg2Rad;
}

float Math::RadToDeg(float rad)
{
	return rad * Rad2Deg;
}

float Math::DeltaAngle(float a, float b)
{
	float delta = fmodf(b - a, 360.0f);

	if (delta > 180.0f)
	{
		delta -= 360.0f;
	}
	else if (delta < -180.0f)
	{
		delta += 360.0f;
	}
	return delta;
}