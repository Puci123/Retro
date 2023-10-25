#pragma once
#include "MathUtylity.h"

class Sprite
{
	public:
		Sprite(mu::vec2 spritePos, uint32_t textureID);
		Sprite(float xPos, float yPos, uint32_t textureID);
		~Sprite();

		inline uint32_t GetTextureID() const { return m_TextureID; }
		inline mu::vec2 GetPos() const { return m_SpritePos; }

	private:
		mu::vec2 m_SpritePos;
		uint32_t m_TextureID;
		

};

