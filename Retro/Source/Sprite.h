#pragma once

#include <string>
#include <vector>
#include <memory>

#include "MathUtylity.h"

class Module; 


class Sprite
{
	public:
		Sprite();
		Sprite(mu::vec2 pos, mu::vec2 scale, int32_t textureID);
		Sprite(float xPos, float yPos, mu::vec2 scale, int32_t textureID);
		Sprite(const Sprite& other);
		~Sprite();

		Sprite& operator=(Sprite&& other) noexcept { return *this; }


		void AddModule(std::unique_ptr<Module> module);
		void UpdateAllModules();
		std::vector<std::string> GetModulesName();
		

		inline int32_t GetTextureID()		 const { return m_TextureID; }
		inline mu::vec2 GetPos()			 const { return m_SpritePos; }
		inline mu::vec2 GetScale()			 const { return m_Scale; }
		inline int32_t GetHeightOffset()	 const { return m_HeightOffset; }
		inline std::string GetName()	     const { return m_Name; }


		inline void SetPos(mu::vec2 pos)				{ m_SpritePos = pos; }
		inline void SetScale(mu::vec2 scale)			{ m_Scale = scale; }
		inline void SetHeight(int32_t height)			{ m_HeightOffset = height; }
		inline void SetName(const std::string& name)	{ m_Name = name; }


	private:
		mu::vec2 m_SpritePos;
		mu::vec2 m_Scale;
		
		int32_t m_HeightOffset = 0;
		int32_t m_TextureID;
		
		std::string m_Name = "New object";
		std::vector<std::unique_ptr<Module>> m_Modules;
};

