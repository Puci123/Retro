#include "Draw2D.h"

void Draw2D::DrawRect(mu::vec2 size, mu::vec2 center, mu::vec3 color , Texture2D* const target)
{
	mu::vec2Int startPoint = static_cast<mu::vec2Int>(mu::vec2{ center - size / 2 });
	mu::vec2Int endPoint   = static_cast<mu::vec2Int>(mu::vec2{ center + size / 2 });

	if (startPoint.x < 0) startPoint.x = 0;
	else if (startPoint.x >= target->GetWidth()) return;

	if (startPoint.y < 0) startPoint.y = 0;
	else if (startPoint.y >= target->GetHeight()) return;
	
	if (endPoint.x < 0) return;
	else if (endPoint.x >= target->GetWidth()) endPoint.x = target->GetWidth() - 1;

	if (endPoint.y < 0) return;
	else if (endPoint.y >= target->GetHeight()) endPoint.y = target->GetHeight() - 1;


	for (int32_t x = startPoint.x; x < endPoint.x; x++)
	{
		for (int32_t y = startPoint.y; y < endPoint.y; y++)
		{
			target->SetPixel(x, y, color);
		}
	}
}

void Draw2D::DrawRectTextured(mu::vec2 size, mu::vec2 center, const Texture2D& texturem, Texture2D* const target)
{
	mu::vec2Int startPoint = static_cast<mu::vec2Int>(mu::vec2{ center - size / 2 });
	mu::vec2Int endPoint = static_cast<mu::vec2Int>(mu::vec2{ center + size / 2 });

	if (startPoint.x < 0) startPoint.x = 0;
	else if (startPoint.x >= target->GetWidth()) return;

	if (startPoint.y < 0) startPoint.y = 0;
	else if (startPoint.y >= target->GetHeight()) return;

	if (endPoint.x < 0) return;
	else if (endPoint.x >= target->GetWidth()) endPoint.x = target->GetWidth() - 1;

	if (endPoint.y < 0) return;
	else if (endPoint.y >= target->GetHeight()) endPoint.y = target->GetHeight() - 1;


	for (int32_t x = startPoint.x; x < endPoint.x; x++)
	{
		for (int32_t y = startPoint.y; y < endPoint.y; y++)
		{
			int32_t texX = static_cast<int32_t>(((x - startPoint.x) / size.x) * texturem.GetWidth());
			int32_t texY = static_cast<int32_t>(((y - startPoint.y) / size.y) * texturem.GetHeight());

			target->SetPixel(x, y, texturem.SampleTexture(texX,texY));
		}
	}
}

void Draw2D::DrawRectFrame(mu::vec2 size, mu::vec2 center, int32_t thickens, mu::vec3 color, Texture2D* const target)
{
	
	mu::vec2Int startPoint = static_cast<mu::vec2Int>(mu::vec2{ center - size / 2 });
	mu::vec2Int endPoint = static_cast<mu::vec2Int>(mu::vec2{ center + size / 2 });

	if (startPoint.x < 0) startPoint.x = 0;
	else if (startPoint.x >= target->GetWidth()) return;

	if (startPoint.y < 0) startPoint.y = 0;
	else if (startPoint.y >= target->GetHeight()) return;

	if (endPoint.x < 0) return;
	else if (endPoint.x >= target->GetWidth()) endPoint.x = target->GetWidth() - 1;

	if (endPoint.y < 0) return;
	else if (endPoint.y >= target->GetHeight()) endPoint.y = target->GetHeight() - 1;


	for (int32_t x = startPoint.x; x < endPoint.x; x++)
	{
		for (int32_t y = startPoint.y; y < endPoint.y; y++)
		{
			if (x <= startPoint.x + thickens || y <= startPoint.y + thickens || x >= endPoint.x - thickens || y >= endPoint.y - thickens)
				target->SetPixel(x, y, color);
		}
	}

}

void Draw2D::DrawSprite(mu::vec2 size, mu::vec2 center, const Texture2D& texture, Texture2D* const target)
{
	mu::vec2Int startPoint = static_cast<mu::vec2Int>(mu::vec2{ center - size / 2 });
	mu::vec2Int endPoint = static_cast<mu::vec2Int>(mu::vec2{ center + size / 2 });

	if (startPoint.x < 0) startPoint.x = 0;
	else if (startPoint.x >= target->GetWidth()) return;

	if (startPoint.y < 0) startPoint.y = 0;
	else if (startPoint.y >= target->GetHeight()) return;

	if (endPoint.x < 0) return;
	else if (endPoint.x >= target->GetWidth()) endPoint.x = target->GetWidth() - 1;

	if (endPoint.y < 0) return;
	else if (endPoint.y >= target->GetHeight()) endPoint.y = target->GetHeight() - 1;


	for (int32_t x = startPoint.x; x < endPoint.x; x++)
	{
		for (int32_t y = startPoint.y; y < endPoint.y; y++)
		{
			int32_t texX = static_cast<int32_t>(((x - startPoint.x) / size.x) * texture.GetWidth());
			int32_t texY = static_cast<int32_t>(((y - startPoint.y) / size.y) * texture.GetHeight());

			mu::vec3 color = texture.SampleTexture(texX, texY);

			if(!mu::Close2Zero(color)) target->SetPixel(x, y, color);
		}
	}
}

void Draw2D::DrawSpriteOpaqe(mu::vec2 size, mu::vec2 center, const Texture2D& texture, Texture2D* const target, float transparency)
{
	mu::vec2Int startPoint = static_cast<mu::vec2Int>(mu::vec2{ center - size / 2 });
	mu::vec2Int endPoint = static_cast<mu::vec2Int>(mu::vec2{ center + size / 2 });

	if (startPoint.x < 0) startPoint.x = 0;
	else if (startPoint.x >= target->GetWidth()) return;

	if (startPoint.y < 0) startPoint.y = 0;
	else if (startPoint.y >= target->GetHeight()) return;

	if (endPoint.x < 0) return;
	else if (endPoint.x >= target->GetWidth()) endPoint.x = target->GetWidth() - 1;

	if (endPoint.y < 0) return;
	else if (endPoint.y >= target->GetHeight()) endPoint.y = target->GetHeight() - 1;


	for (int32_t x = startPoint.x; x < endPoint.x; x++)
	{
		for (int32_t y = startPoint.y; y < endPoint.y; y++)
		{
			int32_t texX = static_cast<int32_t>(((x - startPoint.x) / size.x) * texture.GetWidth());
			int32_t texY = static_cast<int32_t>(((y - startPoint.y) / size.y) * texture.GetHeight());

			mu::vec3 color = texture.SampleTexture(texX, texY);

			if (mu::Close2Zero(color)) continue;
			
			color.x = mu::Lerp(color.x, target->SampleTexture(x, y).x, transparency);
			color.y = mu::Lerp(color.y, target->SampleTexture(x, y).y, transparency);
			color.z = mu::Lerp(color.z, target->SampleTexture(x, y).z, transparency);

			target->SetPixel(x, y, color);
		}
	}

}

void Draw2D::ClearTexture(Texture2D* const target, mu::vec3 color)
{
	for (int32_t y= 0; y < target->GetHeight(); y++)
	{
		for (int32_t x = 0; x < target->GetWidth(); x++)
		{
			target->SetPixel(x, y, color);
		}
	}

}

void Draw2D::Desaturate(Texture2D* const target, float intesity)
{
	for (int32_t y = 0; y < target->GetHeight(); y++)
	{
		for (int32_t x = 0; x < target->GetWidth(); x++)
		{
			mu::vec3 color = target->SampleTexture(x, y);
			float temp = (color.x + color.y + color.z) / 3.f;

			if (temp > 0.33f) temp = 0.33f;

			color = mu::vec3{ mu::Lerp(color.x , temp , intesity), mu::Lerp(color.y , temp , intesity), mu::Lerp(color.z , temp , intesity) };

			target->SetPixel(x, y, color);
		}
	}
}
