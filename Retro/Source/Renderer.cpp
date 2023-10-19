#include <cstdint> 

#include "DebugUtility.h"
#include "Renderer.h"
#include "Camera.h"
#include "Timer.h"


void Render(const Scean& scean)
{
	Timer renderTime;
	renderTime.Start();

	const Camera& cam = scean.GetCamera();
	
	Texture2D* const target = cam.GetTarget();
	Clear(target);

	for (size_t x = 0; x < target->GetWidth(); x++)
	{

		//================================== INITIAL VALUES ==================================//

		float cameraX = (2 * x / static_cast<float>(target->GetWidth())) - 1;
		
		mu::vec2 rayDir{ cam.Dir() + (cam.ClipPlane() * cameraX)};
	

		mu::vec2Int map{ static_cast<int32_t>(cam.Pos().x),static_cast<int32_t>(cam.Pos().y)};
		mu::vec2 deltaDist{ std::abs(1 / rayDir.x),  std::abs(1 / rayDir.y) }; // avoid diviosn by 0
		mu::vec2 sideDist{ 0.f,0.f };

		mu::vec2Int step{ 0, 0 };

		bool hit  = false;
		bool side = false;
		float prepWallDist = 0.0f;


		if (rayDir.x < 0) 
		{
			step.x = -1;
			sideDist.x = (cam.Pos().x - map.x) * deltaDist.x;
		}
		else
		{
			step.x = 1;
			sideDist.x = (map.x + 1.0f - cam.Pos().x) * deltaDist.x;

		}
		
		if (rayDir.y < 0) 
		{
			step.y = -1;
			sideDist.y = (cam.Pos().y - map.y) * deltaDist.y;
		}
		else
		{
			step.y = 1;
			sideDist.y = (map.y + 1.0f - cam.Pos().y) * deltaDist.y;
		}

		//================================== DDA ==================================//

		while (!hit)
		{
			if (sideDist.x < sideDist.y) 
			{
				sideDist.x += deltaDist.x;
				map.x += step.x;
				side = false;
			}
			else
			{
				sideDist.y += deltaDist.y;
				map.y += step.y;
				side = true;
			}

			hit = (scean.GetCellValue(map.x, map.y) > 0);
		}

		//Calc distance from hit point to clipPlane

		if (!side)
			prepWallDist = (sideDist.x - deltaDist.x);
		else
			prepWallDist = (sideDist.y - deltaDist.y);

		

		//Draw Texture
		

		int32_t lineLenght = static_cast<int32_t>(target->GetHeight() / prepWallDist);
		int32_t drawStart = -lineLenght / 2 + target->GetHeight() / 2;
		uint32_t drawEnd = lineLenght / 2 + target->GetHeight() / 2;

		if (drawStart < 0) drawStart = 0;
		if (drawEnd >= target->GetHeight()) drawEnd = target->GetHeight() - 1;


		mu::vec3 color = GetWallColor(scean.GetCellValue(map.x, map.y));
		if (side) color = color * 0.5;



		for (size_t y = drawStart; y < drawEnd; y++)
		{
			target->SetPixel(x, y, color);
		}

	}

	//Update texture
	target->Update();

	renderTime.Stop();
	LOG("frame rendered in time: " << renderTime);
}

void Clear(Texture2D* targt)
{
	for (size_t y = 0; y < targt->GetHeight(); y++)
	{
		for (size_t x = 0; x < targt->GetWidth(); x++)
		{
			targt->SetPixel(x, y, mu::vec3{ 0,0,0 });
		}
	}

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
