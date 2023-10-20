#pragma once
#include <cstdint> 
#include <vector>

#include "Camera.h"
#include "Texture2D.h"

class Scean
{
	public:
		Scean();
		Scean(uint32_t width, uint32_t height);
		Scean(uint32_t width, uint32_t height, const std::vector<uint8_t>& layout);

		~Scean();

		uint8_t  GetCellValue(uint32_t x, uint32_t y) const;
		const Texture2D& GetTexture(uint32_t texID) const;

		inline uint32_t GetWidth()  const { return m_MapWidth; }
		inline uint32_t GetHeight() const { return m_MapHeight; }

		inline const Camera& GetCamera()	const	{ return m_CameraMain; }
		inline void SetCam(const Camera& cam) { m_CameraMain = cam; }

		void MoveCam(mu::vec2 traslation);
		void RoteateCamera(float r);

	private:
		uint32_t m_MapWidth;
		uint32_t m_MapHeight;

		std::vector<uint8_t>	m_MapLayout;
		std::vector<Texture2D>	m_SceanTextures;

		Camera m_CameraMain;
};
