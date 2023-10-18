#include "Camera.h"
#include "DebugUtility.h"

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
