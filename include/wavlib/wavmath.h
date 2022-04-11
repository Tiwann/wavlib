#pragma once
#include <config.h>
#include <cmath>

#define S_PI	3.14159265359
#define S_1_PI	(1 / S_PI)
#define S_2PI	(2 * S_PI)
#define S_2_PI	(2 / S_PI)
#define S_PI_2	(S_PI / 2)

namespace wavlib
{
	float WAVLIB_PRIVATE sgn(float x)
	{
		const float result = (x > 0) ? 1.0f : -1.0f;
		return result;
	}
	
	float WAVLIB_PRIVATE triangle(float x)
	{
		const float result = static_cast<float>(S_2_PI) * std::asin(std::sin(x));
		return result;
	}
}
