#include "Sprite.h"

Sprite::Sprite()
	:Sprite(mu::vec2{ 0,0 }, mu::vec2{ 1, 1 }, 0)
{}

Sprite::Sprite(float xPos, float yPos,mu::vec2 scale, int32_t textureID)
	:Sprite(mu::vec2{ xPos,yPos },scale, textureID)
{}

Sprite::Sprite(mu::vec2 spritePos,mu::vec2 sclae, int32_t textureID)
	:m_SpritePos(spritePos),m_Scale(sclae), m_TextureID(textureID)
{
	static uint32_t spriteCounter = 0;
	SetName("New object " + std::to_string(spriteCounter));
	spriteCounter++;
}


Sprite::~Sprite()
{}
