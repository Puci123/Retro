#pragma once
#include<vector>

#include "Scean.h"
#include "MathUtylity.h"
#include "Texture2D.h"


namespace Renderer 
{

	void Render(const Scean& scean);
	void Clear(Texture2D* targt);

	void SortSprites(std::vector<int32_t>& order, std::vector<float>& dist2sprite, int32_t n);
}
