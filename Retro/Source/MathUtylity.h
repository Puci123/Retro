#pragma once
#include <cstdint> 

namespace mu 
{
	struct  vec2
	{
		float x, y;
	};

	struct vec3
	{
		float x, y, z;
	};

	struct  vec4
	{
		float x, y, z, w;
	};


	inline vec2 operator+ (vec2 a, vec2 b) 
	{
		return vec2{ a.x + b.x, a.y + b.y };
	}

	inline vec2 operator- (vec2 a, vec2 b)
	{
		return vec2{ a.x - b.x, a.y - b.y };
	}


	inline vec2 operator* (vec2 a, float b)
	{
		return vec2{ a.x * b, a.y * b };
	}

	inline vec2 operator* (float b, vec2 a)
	{
		return vec2{ a.x * b, a.y * b };
	}


	inline vec3 operator* (vec3 a, float b)
	{
		return vec3{ a.x * b, a.y * b, a.z * b};
	}

	inline vec3 operator/ (vec3 a, float b) 
	{
		return a * (1 / b);
	}

	struct vec2Int
	{
		int32_t x;
		int32_t y;
	};
}