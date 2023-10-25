#include <cstdint> 
#include <vector>
#include <algorithm>

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

	const Texture2D& floorTextrue = scean.GetTexture(3);
	const Texture2D& ceelingTextrue = scean.GetTexture(4);

	std::vector<float> zBuffer = std::vector<float>(target->GetWidth(),0.f);
	std::vector<float> distToSprite = std::vector<float>(scean.SpriteCount(), 0.f);
	std::vector<int32_t> spriteOrder = std::vector<int32_t>(scean.SpriteCount(), -1);

	float floorScale	= 0.5f;
	float cealingScale  = 0.5f;

	//================================== DRAW FLOORS  ==================================//

	for (size_t y = 0; y < target->GetHeight(); y++)
	{
		mu::vec2 rayDri0 = mu::vec2{ cam.Dir() - cam.ClipPlane() };
		mu::vec2 rayDir1 = mu::vec2{ cam.Dir() + cam.ClipPlane() };

		int32_t yCenter = y - target->GetHeight() / 2;
		float zPos = target->GetHeight() / 2.f;

		//Distance form camera to curent floor row (0 -> floor; 0.5-> midle; 1 -> cealing)
		float rowDist = zPos / yCenter;

		mu::vec2 step = rowDist * (rayDir1 - rayDri0) / static_cast<float>(target->GetWidth());

		//World cords of most left column
		mu::vec2 floorStart = mu::vec2{ cam.Pos() + rayDri0 * rowDist};


		for (size_t x = 0; x < target->GetWidth(); x++)
		{
			mu::vec2Int cell	= mu::vec2Int{static_cast<int32_t>(floorStart.x), static_cast<int32_t>(floorStart.y) };
			mu::vec2Int uvCords = mu::vec2Int{
				
				static_cast<int32_t>(floorTextrue.GetWidth()  * (floorStart.x - cell.x)) & (static_cast<int32_t>(floorTextrue.GetWidth()) -  1),
				static_cast<int32_t>(floorTextrue.GetHeight() * (floorStart.y - cell.y)) & (static_cast<int32_t>(floorTextrue.GetHeight()) - 1)
			};

			floorStart = floorStart + step;


			//Draw floor to screan
			mu::vec3 color = floorTextrue.SampleTexture(static_cast<int32_t>(uvCords.x * floorScale) % floorTextrue.GetWidth(), static_cast<int32_t>(uvCords.y * floorScale) % floorTextrue.GetHeight());
			target->SetPixel(x, target->GetHeight() -  y - 1, color);

			//Draw cealing to screan [WARING: HAVE TO BE SAME SIZE AS FLOOR (texture)]
			color = ceelingTextrue.SampleTexture(static_cast<int32_t>(uvCords.x * cealingScale) % ceelingTextrue.GetWidth(), static_cast<int32_t>(uvCords.y * cealingScale) % ceelingTextrue.GetHeight());
			target->SetPixel(x, y, color);
		}
	}



	//================================== DRAW WALLS ==================================//
	for (size_t x = 0; x < target->GetWidth(); x++)
	{

		float cameraX = (2 * x / static_cast<float>(target->GetWidth())) - 1;
		
		mu::vec2 rayDir{ cam.Dir() + (cam.ClipPlane() * cameraX)};
	

		mu::vec2Int map{ static_cast<int32_t>(cam.Pos().x),static_cast<int32_t>(cam.Pos().y)};
		mu::vec2 deltaDist{ std::abs(1.f / rayDir.x),  std::abs(1.f / rayDir.y) }; // avoid diviosn by 0
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

		

		//Line height calcuclation
		
		int32_t lineLenght = static_cast<int32_t>(target->GetHeight() / prepWallDist);
		int32_t drawStart = -lineLenght / 2 + target->GetHeight() / 2;
		uint32_t drawEnd = lineLenght / 2 + target->GetHeight() / 2;

		if (drawStart < 0) drawStart = 0;
		if (drawEnd >= target->GetHeight()) drawEnd = target->GetHeight() - 1;

		//Texture sampling
		const Texture2D& objectTexture = scean.GetTexture(scean.GetCellValue(map.x, map.y));
		float exactWallX = 0;
		
		if (!side)	exactWallX = cam.Pos().y + prepWallDist * rayDir.y;
		else		exactWallX = cam.Pos().x + prepWallDist * rayDir.x;

		exactWallX -= std::floor(exactWallX);

		//TexCord
		mu::vec2 texCord{ 0,0 };

		texCord.x =  floor(exactWallX * objectTexture.GetWidth());
		
		if (!side && rayDir.x > 0) texCord.x = objectTexture.GetWidth() - texCord.x - 1;
		if (side  && rayDir.y < 0) texCord.x = objectTexture.GetWidth() - texCord.x - 1;

		float verticalStep = static_cast<float>(objectTexture.GetHeight()) / static_cast<float>(lineLenght);
		texCord.y = (drawStart - (target->GetHeight() / 2.f) + (lineLenght / 2.f)) * verticalStep;


		// Draw to screan
		for (size_t y = drawStart; y < drawEnd; y++)
		{

			mu::vec3 color = objectTexture.SampleTexture(static_cast<uint32_t>(texCord.x), static_cast<uint32_t>(texCord.y));
			target->SetPixel(x, y, color);

			texCord.y += verticalStep;
		}
		zBuffer[x] = prepWallDist;

	}


	//================================== Draw Sprites ==================================//

	for (size_t i = 0; i < scean.SpriteCount(); i++)
	{
		mu::vec2 spritePos = scean.GetSprite(i).GetPos();

		//TODO: CREATE HEAP TO ACCELETARE
		spriteOrder[i] = i;
		distToSprite[i] = (cam.Pos().x - spritePos.x) * (cam.Pos().x - spritePos.x) + (cam.Pos().y - spritePos.y) * (cam.Pos().y - spritePos.y);
	}

	SortSprites(spriteOrder, distToSprite, scean.SpriteCount());

	//Project sprites to camera plane
	for (int i = 0; i < scean.SpriteCount(); i++)
	{
		const Sprite& curentSprite = scean.GetSprite(spriteOrder[i]);
		mu::vec2 spritePos = curentSprite.GetPos() - cam.Pos();

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		float invertCamDet = 1.0f / (cam.ClipPlane().x * cam.Dir().y - cam.ClipPlane().y * cam.Dir().x);
		mu::vec2 trnasform = invertCamDet * mu::vec2{ cam.Dir().y * curentSprite.GetPos().x - cam.Dir().x * curentSprite.GetPos().y,					//x
													-cam.ClipPlane().y * curentSprite.GetPos().x + cam.ClipPlane().y * curentSprite.GetPos().x };		//y (depth not height)

		int32_t screanSpaceX = static_cast<int32_t>((target->GetWidth() / 2) * (1 + trnasform.x / trnasform.y));

		//height of the sprite 
		int32_t spriteHeight = static_cast<int32_t>(abs(target->GetHeight() / trnasform.y));

		mu::vec2Int spriteDrawStart{ 0,0 };
		mu::vec2Int spriteDrawStop{ 0, 0 };

		spriteDrawStart.y = target->GetHeight() / 2 - scean.GetTexture(curentSprite.GetTextureID()).GetHeight() / 2;
		if (spriteDrawStart.y < 0) spriteDrawStart.y = 0;

		spriteDrawStop.y = target->GetHeight() / 2 + scean.GetTexture(curentSprite.GetTextureID()).GetHeight() / 2;
		if (spriteDrawStop.y >= target->GetHeight()) spriteDrawStop.y = target->GetHeight() - 1;

		//width of sprite
		int32_t spriteWidth = spriteHeight; //???

		spriteDrawStart.x = screanSpaceX - spriteWidth / 2;
		if (spriteDrawStart.x < 0) spriteDrawStart.x = 0;

		spriteDrawStop.x = screanSpaceX + spriteWidth / 2;
		if (spriteDrawStop.x >= target->GetWidth()) spriteDrawStop.x = target->GetWidth() - 1;


		for (size_t x = spriteDrawStart.x; x < spriteDrawStop.x; x++)
		{
			if (trnasform.y > 0 && x > 0 && x < target->GetWidth() && trnasform.y < zBuffer[x])
			{
				//TODO: write sprite to screan

				for (size_t y = spriteDrawStart.y; y < spriteDrawStop.y; y++)
				{

				}
			}
		}

		
	}

	//Update texture
	target->Update();

	renderTime.Stop();
	//LOG("frame rendered in time: " << renderTime);
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

void SortSprites(std::vector<int32_t>& order, std::vector<float>& dist2sprite, int32_t n)
{
	std::vector<std::pair<float, int32_t>> spritesPair(n);

	for (int32_t i = 0; i < n; i++)
	{
		spritesPair[i].first  = dist2sprite[i];
		spritesPair[i].second = order[i];

	}

	std::sort(spritesPair.begin(), spritesPair.end());

	for (int32_t i = 0; i < n; i++)
	{
		dist2sprite[i] = spritesPair[n - i - 1].first;
		order[i] = spritesPair[n - i - 1].second;
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

mu::vec3 SampleTexture(const Texture2D& texture, uint32_t xCord, uint32_t yCord)
{
	return mu::vec3();
}
