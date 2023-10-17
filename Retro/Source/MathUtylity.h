#pragma once

namespace mu 
{
	struct  vec2
	{
		float x, y;
	};

	inline vec2 operator+ (vec2 a, vec2 b) 
	{
		return vec2{ a.x + b.x, a.y + b.y };
	}

	inline vec2 operator* (vec2 a, float b)
	{
		return vec2{ a.x * b, a.y * b };
	}

	inline vec2 operator* (float b, vec2 a)
	{
		return vec2{ a.x * b, a.y * b };
	}
}