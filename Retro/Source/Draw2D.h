#pragma once
#include "MathUtylity.h"
#include "Texture2D.h"
#include "Sprite.h"

namespace Draw2D
{

	void DrawRect(mu::vec2 size, mu::vec2 center, mu::vec3 color ,Texture2D* const target);
	void DrawRectTextured(mu::vec2 size, mu::vec2 center, const Texture2D& texture, Texture2D* const target);
	void DrawRectFrame(mu::vec2 size, mu::vec2 center, int32_t thickens, mu::vec3 color, Texture2D* const target);

	void DrawSprite(mu::vec2 size, mu::vec2 center, const Texture2D& texture, Texture2D* const target);								//Black as transparent
	void DrawSpriteOpaqe(mu::vec2 size, mu::vec2 center, const Texture2D& texture, Texture2D* const target, float transparency);	

	void ClearTexture(Texture2D* const target, mu::vec3 color);

	void Desaturate(Texture2D* const target, float intesity = 1.f);
}