#pragma once
#include <cstdint> 
#include <vector>
#include <unordered_map>

#include "Camera.h"
#include "Texture2D.h"
#include "Sprite.h"

class Scean
{
	public:
		Scean();
		Scean(int32_t width, int32_t height);
		Scean(int32_t width, int32_t height, const std::vector<uint8_t>& layout);

		~Scean();

		uint8_t  GetCellValue(int32_t x, int32_t y)	  const;
		const Texture2D& GetTexture(uint32_t texID)   const;

		inline int32_t GetWidth()						const { return m_MapWidth; }
		inline int32_t GetHeight()						const { return m_MapHeight; }

		inline Camera& GetCamera()							  { return m_CameraMain; }
		inline void SetCam(const Camera& cam)				  { m_CameraMain = cam; }

		inline uint32_t SpriteCount()					const{ return m_SceanSprites.size(); }
		inline Sprite& GetSprite(int32_t id)				 { return m_SceanSprites[id]; }
		inline const Sprite& GetSprite(int32_t id)		const{ return m_SceanSprites[id]; }


		bool const IsSprite(const mu::vec2& pos, float ep = 0.01f);

		void MoveCam(mu::vec2 traslation);
		void RoteateCamera(float r);
		void UpdateSprites();

		void InseretWall (mu::vec2Int pos, int32_t elemntID);
		void InsertSpeite(mu::vec2    pos, int32_t elemntID);
		bool DeleteSpriteWithID(int32_t id);
		
		int32_t GetSpriteFromCeell(mu::vec2Int cell);
		int32_t AddMapTileTexture(const Texture2D& asset, const std::string& name);

	private:
		int32_t m_MapWidth;
		int32_t m_MapHeight;

		std::vector<uint8_t>	m_MapLayout			= std::vector<uint8_t>(1,1);

		std::vector<Texture2D>	m_SceanTextures;
		std::vector<Sprite>		m_SceanSprites;
		
		std::unordered_map<std::string, int32_t> m_NamesIDs;


		Camera m_CameraMain;
		int32_t m_IDcounter = 0;
};
