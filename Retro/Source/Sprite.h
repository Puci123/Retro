#pragma once
#include "MathUtylity.h"

class Sprite
{
	public:
		Sprite(mu::vec2 pos, mu::vec2 scale, uint32_t textureID);
		Sprite(float xPos, float yPos, mu::vec2 scale, uint32_t textureID);
		~Sprite();

		inline uint32_t GetTextureID()		 const { return m_TextureID; }
		inline mu::vec2 GetPos()			 const { return m_SpritePos; }
		inline mu::vec2 GetScale()			 const { return m_Scale; }
		inline int32_t GetHeightOffset()	 const { return m_HeightOffset; }


	private:
		mu::vec2 m_SpritePos;
		mu::vec2 m_Scale;
		int32_t m_HeightOffset = 0;
	

		uint32_t m_TextureID;
		

};

