#include "Sprite.h"

Sprite::Sprite(mu::vec2 spritePos,mu::vec2 sclae, uint32_t textureID)
	:m_SpritePos(spritePos),m_Scale(sclae), m_TextureID(textureID)
{
}

Sprite::Sprite(float xPos, float yPos,mu::vec2 scale, uint32_t textureID)
	:Sprite(mu::vec2{ xPos,yPos },scale, textureID)
{}

Sprite::~Sprite()
{
}
