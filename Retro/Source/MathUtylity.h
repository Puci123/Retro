#pragma once
#include <cstdint> 

namespace mu
{
	constexpr float epsilon = 0.000000001f;

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

	struct vec2Int
	{
		int32_t x;
		int32_t y;

		vec2Int(vec2 a);
		vec2Int(int32_t _x, int32_t _y);

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

	inline vec2 operator/ (vec2 a, float b)
	{
		return a * (1 / b);
	}


	inline vec3 operator* (vec3 a, float b)
	{
		return vec3{ a.x * b, a.y * b, a.z * b };
	}

	inline vec3 operator/ (vec3 a, float b)
	{
		return a * (1 / b);
	}

	inline bool Close2Zero(vec3 a) 
	{
		return(a.x < epsilon && a.y < epsilon && a.z < epsilon);
	}

	//========================================== RAD & DEG ==========================================//

	inline float Rad2Deg(float rad) 
	{
		return rad * 57.2957795f;
	}

	inline float Deg2Rad(float deg) 
	{
		return deg * 0.0174532925f;
	}


	//================================= FLOAT =================================//

	inline float Clamp01(float a) 
	{
		if (a < 0.f) return 0.f;
		if (a > 1.f) return 1.f;

		return a;
	}

}