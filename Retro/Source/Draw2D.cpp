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
	else if (endPoint.y >= target->GetHeight()) endPoint.y = target->GetWidth() - 1;


	for (int32_t x = startPoint.x; x < endPoint.x; x++)
	{
		for (int32_t y = startPoint.y; y < endPoint.y; y++)
		{
			target->SetPixel(x, y, color);
		}
	}


//	target->Update();

}
