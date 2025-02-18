#include "Sprite.h"
#include "Module.h"

Sprite::Sprite()
	:Sprite(mu::vec2{ 0,0 }, mu::vec2{ 1, 1 }, 0)
{}

Sprite::Sprite(float xPos, float yPos,mu::vec2 scale, int32_t textureID)
	:Sprite(mu::vec2{ xPos,yPos },scale, textureID)
{}

Sprite::Sprite(const Sprite& other)
	:Sprite(other.GetPos(),other.GetScale(),other.GetTextureID())
{
	SetName(other.GetName());
}

Sprite::Sprite(mu::vec2 spritePos,mu::vec2 sclae, int32_t textureID)
	:m_SpritePos(spritePos),m_Scale(sclae), m_TextureID(textureID)
{
	static uint32_t spriteCounter = 0;
	SetName("New object " + std::to_string(spriteCounter));
	spriteCounter++;
}


Sprite::~Sprite()
{}

void Sprite::AddModule(std::unique_ptr<Module> mod)
{
	m_Modules.push_back(std::move(mod));
	m_Modules.back()->Start();
}

void Sprite::UpdateAllModules()
{
	for (const std::unique_ptr<Module>& module : m_Modules)
	{
		module->Update();
	}

}

std::vector<std::string> Sprite::GetModulesName()
{
	std::vector<std::string> modulesName;
	for (const std::unique_ptr<Module>& module : m_Modules)
	{
		modulesName.push_back(module->ToString());
	}
	
	return modulesName;
}
