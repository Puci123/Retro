#include <cstdint> 

#include "DebugUtility.h"
#include "Renderer.h"
#include "Camera.h"
#include "Timer.h"


void Render(const Scean& scean)
{
	const Camera& cam = scean.GetCamera();
	Texture2D* const target = cam.GetTarget();

	Timer renderTime;
	renderTime.Start();

	for (size_t x = 0; x < target->GetWidth(); x++)
	{

		//================================== INITIAL VALUES ==================================//

		float screanSpaceX = 2 * x / static_cast<float>(target->GetWidth()) - 1;
		
		mu::vec2 rayDir{ cam.Dir() + cam.ClipPlane() * screanSpaceX};
	

		mu::vec2 deltaDist{ std::abs(1 / rayDir.x),  std::abs(1 / rayDir.y) }; // avoid diviosn by 0
		mu::vec2 sideDist{ 0.f,0.f };

		mu::vec2Int cameraCords{ static_cast<int32_t>(cam.Pos().x),static_cast<int32_t>(cam.Pos().y)};
		mu::vec2Int step{ 0, 0 };

		bool hit  = false;
		bool side = false;

		if (rayDir.x < 0) 
		{
			step.x = -1;
			sideDist.x = (cam.Pos().x - cameraCords.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (cam.Pos().x + 1 - cameraCords.x) * deltaDist.x;

		}

		if (rayDir.y < 0) 
		{
			step.y = -1;
			sideDist.y = (cam.Pos().y - cameraCords.y) * deltaDist.y;
		}
		else
		{
			step.y = -1;
			sideDist.y = (cam.Pos().y + 1 - cameraCords.y) * deltaDist.y;
		}

		//================================== DDA ==================================//

		while (!hit)
		{
			if (sideDist.x < sideDist.y) 
			{
				sideDist.x += deltaDist.x;
				cameraCords.x += step.x;
				side = false;
			}
			else
			{
				sideDist.y += deltaDist.y;
				cameraCords.y += step.y;
				side = true;
			}

			hit = (scean.GetCellValue(cameraCords.x, cameraCords.y) > 0);
		}

		//Calc distance from hit point to clipPlane
		float prepWallDist = 0.0f;

		if (!side)
			prepWallDist = (sideDist.x - deltaDist.x);
		else
			prepWallDist = (sideDist.y - deltaDist.y);

		

		//Draw Texture
		

		int32_t lineLenght = static_cast<uint32_t>(target->GetHeight() / prepWallDist);
		int32_t drawStart = -lineLenght / 2 + target->GetHeight() / 2;
		uint32_t drawEnd = lineLenght / 2 + target->GetHeight() / 2;

		if (drawStart < 0) drawStart = 0;
		if (drawEnd >= target->GetHeight()) drawEnd = target->GetHeight();


		mu::vec3 color = GetWallColor(scean.GetCellValue(cameraCords.x, cameraCords.y));
		if (side) color = color * 0.5;



		for (size_t y = drawStart; y < drawEnd; y++)
		{
			target->SetPixel(x, y, color);
		}

	}

	renderTime.Stop();
	LOG("frame rendered in time: " << renderTime);
}

mu::vec3 GetWallColor(uint8_t code)
{
	switch (code)
	{
		case 1: return mu::vec3{ 1,0,0 };
		case 2: return mu::vec3{ 0,1,0 };
		case 3: return mu::vec3{ 0,0,1 };
		case 4: return mu::vec3{ 1,1,1 };
		case 5: return mu::vec3{ 1,1,0 };

	}

	LOG_ERROR("INVALID COLOR CODE");
	ASSERT(false); //INVALID COLOR
	
	return mu::vec3{ 0,0,0 };
}
