#pragma once
#include <memory>
#include "MathUtylity.h"
#include "Texture2D.h"


class Camera
{

	public:
		Camera();
		Camera(mu::vec2 pos, mu::vec2 dir, mu::vec2 clipPlane, Texture2D* target);

		inline mu::vec2 Pos()			  const { return m_Pos;}
		inline mu::vec2 Dir()			  const { return m_Dir;}
		inline mu::vec2 ClipPlane()		  const { return m_ClipPlane;}
		inline uint32_t TargetTextureID() const { return m_TargetTexture->GetID(); }
		
		inline Texture2D* const GetTarget()    const { return  m_TargetTexture; }


		void BindTargetTexture()	const;
		void UnbindTargetTexture()  const;

		void MoveCamera(mu::vec2 traslation);
		void RotateCam(float rotation);

	private:
		mu::vec2 m_Pos;
		mu::vec2 m_Dir;
		mu::vec2 m_ClipPlane;

		Texture2D* m_TargetTexture;
};
