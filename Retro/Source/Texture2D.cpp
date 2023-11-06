#include<iostream>

#include "Texture2D.h"
#include "Texture2D.h"
#include "DebugUtility.h"

Texture2D::Texture2D(int32_t width, int32_t height, bool gpuBind)
	:m_RenderID(0), m_Width(width), m_Height(height), m_GpuSide(gpuBind)
{
	m_TextureBuffer.resize(width * height);

	for (int32_t i = 0; i < width * height; i++)
	{
		m_TextureBuffer[i] = mu::vec4{ 1.f, 0.f, 1.f, 1.f };
	}

	if (m_GpuSide)
	{
		// Create Image on GPU side
		glGenTextures(1, &m_RenderID);
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, &m_TextureBuffer[0]);
		Unbind();

		LOG("Created texture with dim: " << m_Width << "x" << m_Height << " (ID " << m_RenderID << ")");
	}
	else
	{
		LOG("Created texture with dim: " << m_Width << "x" << m_Height << " (CPU SIDE)");
	}
}

Texture2D::Texture2D(const std::string& path, bool gpuBind)
	:m_GpuSide(gpuBind), m_RenderID(0),m_AssetName(path)
{
	
	stbi_set_flip_vertically_on_load(1);

	int32_t  numberOfParameters;
	uint8_t* tempBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &numberOfParameters, 4);

	if (stbi_failure_reason()) 
	{
		LOG_ERROR(" " << stbi_failure_reason());
		ASSERT(false);
	}
	else
	{
		LOG("Texture loaded from " << path << " OK!");

	}


	m_TextureBuffer.resize(m_Width * m_Height);
	int32_t curentPixel = 0;

	while (curentPixel < m_Width * m_Height)
	{
		mu::vec4 pixelColor{ tempBuffer[4 * curentPixel] / 255.f, tempBuffer[4 * curentPixel + 1] / 255.f, tempBuffer[4 * curentPixel + 2] / 255.f, tempBuffer[4 * curentPixel + 3] / 255.f };
		m_TextureBuffer[curentPixel++] = pixelColor;
	}

	delete[] tempBuffer;


	if (m_GpuSide)
	{
		// Create Image on GPU side
		glGenTextures(1, &m_RenderID);
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, &m_TextureBuffer[0]);
		Unbind();

		LOG("Created texture with dim: " << m_Width << "x" << m_Height << " (ID " << m_RenderID << ")");
	}
	else
	{
		LOG("Created texture with dim: " << m_Width << "x" << m_Height << " (CPU SIDE)");
	}
}

Texture2D::~Texture2D()
{
	m_TextureBuffer = std::vector<mu::vec4>();
	
	if (m_GpuSide) 
	{

		LOG("Texture destroyed with ID " << m_RenderID);	
		glDeleteTextures(1, &m_RenderID);
	}
	else
	{
		LOG("Texture destroyed CPU SIDE");
	}

}

void Texture2D::Copy2GPU()
{
	glGenTextures(1, &m_RenderID);
	m_GpuSide = true;
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, &m_TextureBuffer[0]);
	Unbind();

	LOG("Created texture with dim: " << m_Width << "x" << m_Height << " (ID " << m_RenderID << ")");

}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_RenderID);

}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);

}


void Texture2D::SetPixel(int32_t x, int32_t y, mu::vec3 color)
{
	

	ASSERT(x < m_Width && y < m_Height);
	m_TextureBuffer[y * m_Width + x] = mu::vec4{ static_cast<float>(color.x), static_cast<float>(color.y), static_cast<float>(color.z), 1.f };

}

void Texture2D::Update()
{
	Bind();
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_FLOAT, &m_TextureBuffer[0].x);
	Unbind();

}

