#pragma once
#include "MathUtylity.h"

struct Camera
{
	mu::vec2 pos;
	mu::vec2 dir;
	mu::vec2 clipPlane;
};
