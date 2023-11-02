#pragma once
#include "MathUtylity.h"
#include "Texture2D.h"


namespace Draw2D
{

	void DrawRect(mu::vec2 size, mu::vec2 center, mu::vec3 color ,Texture2D* const target);
	void DrawRectFrame(mu::vec2 size, mu::vec2 center, int32_t thickens, mu::vec3 color, Texture2D* const target);

	void ClearTexture(Texture2D* const target, mu::vec3 color);


}