#pragma once
#include "Scean.h"
#include "MathUtylity.h"
#include "Texture2D.h"


void Render(const Scean& scean);
void Clear(Texture2D* targt);

mu::vec3 GetWallColor(uint8_t code);
mu::vec3 SampleTexture(const Texture2D& texture, uint32_t xCord, uint32_t yCord);