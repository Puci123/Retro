#pragma once
#include "Scean.h"
#include "MathUtylity.h"
#include "Texture2D.h"


void Render(const Scean& scean);
void Clear(Texture2D* targt);

mu::vec3 GetWallColor(uint8_t code);