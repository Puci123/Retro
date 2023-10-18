#include<iostream>

#include "Texture2D.h"
#include "Texture2D.h"
#include "DebugUtility.h"

Texture2D::Texture2D(uint32_t width, uint32_t height)
	:m_RenderID(0), m_Width(width), m_Height(height)
{
	m_TextureBuffer.resize(width * height);

	for (uint32_t i = 0; i < width * height; i++)
	{
		m_TextureBuffer[i] = mu::vec4{ 0.f, 0.f, 0.f, 1.f };
	}

	// Create Image on GPU side
	glGenTextures(1, &m_RenderID);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, &m_TextureBuffer[0]);
	Unbind();

	std::cout << "Created texture with dim: " << m_Width << "x" << m_Height << " (ID " << m_RenderID << ")" << std::endl;

}

Texture2D::~Texture2D()
{
	std::cout << "Texture destroyed with ID " << m_RenderID << std::endl;
	m_TextureBuffer = std::vector<mu::vec4>();
	glDeleteTextures(1, &m_RenderID);

}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_RenderID);

}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);

}


void Texture2D::SetPixel(uint32_t x, uint32_t y, mu::vec3 color)
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

