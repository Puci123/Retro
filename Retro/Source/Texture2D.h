#pragma once

#pragma once
#include <GL/glew.h>
#include<vector>
#include<stbi/stbi_image.h>
#include <string>

#include "DebugUtility.h"
#include "MathUtylity.h"


class Texture2D
{
public:
	Texture2D(int32_t width, int32_t height, bool gpuBind = true);
	Texture2D(const std::string& path, bool gpuBind = true);

	~Texture2D();

	void Copy2GPU();
	void Bind();
	void Unbind();

	void SetPixel(int32_t x, int32_t y, mu::vec3 color);
	void Update();

	inline int32_t GetWidth()			const { return m_Width; }
	inline int32_t GetHeight()			const { return m_Height; }
	inline uint32_t GetID()				const { return m_RenderID; }
	inline std::string GetAssetName()	const { return m_AssetName; }

	inline mu::vec3 SampleTexture(int32_t x, int32_t y) const
	{
		ASSERT(x < m_Width); //Inavlid witdth;
		ASSERT(y < m_Height); //Inavlid witdth;

		mu::vec4 temp = m_TextureBuffer[y * m_Width + x];
		return mu::vec3{ temp.x, temp.y, temp.z };
	}


private:
	std::string m_AssetName = "";
	uint32_t	m_RenderID;
	int32_t		m_Width;
	int32_t		m_Height;
	bool		m_GpuSide;

	std::vector<mu::vec4> m_TextureBuffer;

};


