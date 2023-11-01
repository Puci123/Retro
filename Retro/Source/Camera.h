#pragma once
#include <memory>
#include "MathUtylity.h"
#include "Texture2D.h"


class Camera
{

	public:
		Camera();
		Camera(mu::vec2 pos, mu::vec2 dir, mu::vec2 clipPlane, Texture2D* target);

		inline float GetAangleRotation()	  const { return m_AngleRotation; }
		inline mu::vec2 Pos()				  const { return m_Pos;}
		inline mu::vec2 Dir()			      const { return m_Dir;}
		inline mu::vec2 ClipPlane()		      const { return m_ClipPlane;}
		inline uint32_t TargetTextureID()     const { return m_TargetTexture->GetID(); }
		inline Texture2D* const GetTarget()   const { return  m_TargetTexture; }
		inline void SetPos(mu::vec2 pos)			{ m_Pos = pos; }

		void BindTargetTexture()	const;
		void UnbindTargetTexture()  const;

		void SetRotation(float theta);
		void SetFOV(float phi);
		float GetFov();

		void MoveCamera(mu::vec2 traslation);
		void RotateCam(float rotation);

	
	private:
		Texture2D* m_TargetTexture;
		mu::vec2 m_Pos;
		mu::vec2 m_Dir;
		mu::vec2 m_ClipPlane;

		float m_AngleRotation = 180.0f;

};
