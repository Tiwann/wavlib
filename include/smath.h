#pragma once
#include <cmath>

#define _PI		3.14159265359
#define _1_PI	1 / _PI
#define _2PI	2 * _PI
#define _2_PI	2 / _PI
#define _PI_2	_PI / 2

namespace wavlib
{
	static double sgn(double x)
	{
		double result = (x > 0) ? 1.0 : -1.0;
		return result;
	}

	static float sgn(float x)
	{
		float result = (x > 0) ? 1.0f : -1.0f;
		return result;
	}

	
	static double triangle(double x)
	{
		double result = _2_PI * std::asin(std::sin(x));
		return result;
	}

}
