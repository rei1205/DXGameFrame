// Color.cpp
#include "Color.h"
#include <cmath>

const Color Color::black(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::white(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::red(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::green(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::blue(0.0f, 0.0f, 1.0f, 1.0f);

Color::Color() :
	Color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

Color::Color(float red, float green, float blue, float alpha) :
	r(red), g(green), b(blue), a(alpha)
{
}

void Color::SetRGB255(float red, float green, float blue, float alpha)
{
	r = red * RGB255_InvMax;
	g = green * RGB255_InvMax;
	b = blue * RGB255_InvMax;
	a = alpha * RGB255_InvMax;
}

std::vector<float> Color::GetColorVector()
{
	std::vector<float> result = { r, g, b, a };
	return result;
}

Color Color::Normalized()
{
	Color result = *this;

	// ç≈è¨ílï‚ê≥
	result.r = std::fmaxf(result.r, 0.0f);
	result.g = std::fmaxf(result.g, 0.0f);
	result.b = std::fmaxf(result.b, 0.0f);
	result.a = std::fmaxf(result.a, 0.0f);

	// ç≈ëÂílï‚ê≥
	result.r = std::fminf(result.r, 1.0f);
	result.g = std::fminf(result.g, 1.0f);
	result.b = std::fminf(result.b, 1.0f);
	result.a = std::fminf(result.a, 1.0f);

	return result;
}
