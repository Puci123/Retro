#include "Scean.h"
#include "DebugUtility.h"



Scean::Scean()
	:m_MapWidth(24), m_MapHeight(24)
{
	m_MapLayout =
	{
	  1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
	  1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1,
	  1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	m_CameraMain = Camera(mu::vec2{22.0f, 12.f},mu::vec2{-1.0f, 0.f},mu::vec2{0.f, 0.66f}, nullptr);
	LOG("Created map with size: " << m_MapWidth << "x" << m_MapHeight);

}

Scean::Scean(uint32_t width, uint32_t height)
	: m_MapWidth(width), m_MapHeight(height)
{
	m_MapLayout.resize(width * height,0);
	m_CameraMain = Camera(mu::vec2{ 22.0f, 12.f }, mu::vec2{ -1.0f, 0.f }, mu::vec2{ 0.f, 0.66f }, nullptr);
}

Scean::Scean(uint32_t width, uint32_t height, const std::vector<uint8_t>& layout)
	: m_MapWidth(width), m_MapHeight(height)
{
	m_MapLayout.resize(width * height);

	for (size_t i = 0; i < width * height; i++)
	{
		m_MapLayout[i] = layout[i];
	}


	m_CameraMain = Camera(mu::vec2{ 22.0f, 12.f }, mu::vec2{ -1.0f, 0.f }, mu::vec2{ 0.f, 0.66f }, nullptr);
}

Scean::~Scean(){}


uint8_t Scean::GetCellValue(uint32_t x, uint32_t y) const
{
	ASSERT(x < m_MapWidth);		    //Invalid map width
	ASSERT(y < m_MapHeight);		//Invalid map height

	return m_MapLayout[y * m_MapWidth + x];
}

void Scean::MoveCam(mu::vec2 translation)
{
	m_CameraMain.MoveCamera(translation);
}

void Scean::RoteateCamera(float r)
{
	m_CameraMain.RotateCam(r);
}
	
