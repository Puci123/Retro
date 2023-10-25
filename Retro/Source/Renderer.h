#pragma once
#include<vector>

#include "Scean.h"
#include "MathUtylity.h"
#include "Texture2D.h"


void Render(const Scean& scean);
void Clear(Texture2D* targt);
void SortSprites(std::vector<int32_t>& order, std::vector<float>& dist2sprite, int32_t n);


mu::vec3 GetWallColor(uint8_t code);
mu::vec3 SampleTexture(const Texture2D& texture, uint32_t xCord, uint32_t yCord);