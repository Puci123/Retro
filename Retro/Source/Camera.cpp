#include "Camera.h"
#include "DebugUtility.h"
#include <ImGUI/imgui.h>

Camera::Camera():
	m_Pos(mu::vec2{0,0}),m_Dir(mu::vec2{0,0}),m_ClipPlane({0,0})
{
	m_TargetTexture = nullptr;
}

Camera::Camera(mu::vec2 pos, mu::vec2 dir, mu::vec2 clipPlane, Texture2D* target)
	:m_Pos(pos), m_Dir(dir), m_ClipPlane(clipPlane)
{
	m_TargetTexture = target;
}

void Camera::BindTargetTexture() const
{
	m_TargetTexture->Bind();
}

void Camera::UnbindTargetTexture() const
{
	m_TargetTexture->Unbind();
}

void Camera::MoveCamera(mu::vec2 traslation)
{
	m_Pos = m_Pos + traslation;
}

void Camera::RotateCam(float rotation)
{
	mu::vec2 oldDir = m_Dir;
	rotation = -rotation;

	m_Dir.x = m_Dir.x * cosf(rotation) - m_Dir.y * sinf(rotation);
	m_Dir.y = oldDir.x * sinf(rotation) + oldDir.y * cosf(rotation);

	mu::vec2 oldPlane = m_ClipPlane;
	
	m_ClipPlane.x = m_ClipPlane.x * cosf(rotation) - m_ClipPlane.y * sinf(rotation);
	m_ClipPlane.y = oldPlane.x * sinf(rotation) + oldPlane.y * cosf(rotation);


}
