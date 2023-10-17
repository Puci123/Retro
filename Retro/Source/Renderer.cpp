#include "Renderer.h"
#include "Camera.h"

void Render(const Scean& scean)
{
	const Camera cam = scean.GetCamera();

	for (size_t x = 0; x < scean.GetWidth(); x++)
	{
		float screanSpaceX = 2 * x / static_cast<float>(scean.GetWidth()) - 1;
		mu::vec2 rayDir{ cam.dir + cam.clipPlane * screanSpaceX };
	}
}
