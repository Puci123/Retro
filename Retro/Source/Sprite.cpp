#include "Sprite.h"

Sprite::Sprite(mu::vec2 spritePos, uint32_t textureID)
	:m_SpritePos(spritePos), m_TextureID(textureID)
{
}

Sprite::Sprite(float xPos, float yPos, uint32_t textureID)
	:Sprite(mu::vec2{ xPos,yPos }, textureID)
{}

Sprite::~Sprite()
{
}
