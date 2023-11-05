#pragma once

#include "Scean.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include "ImGUI/imgui_impl_opengl3.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_internal.h"


class SceanEditor
{
	public:
		SceanEditor(int32_t screanWidth, int32_t screanHeight);
		~SceanEditor();


		inline void OpenScean(Scean* scean)				{ m_Scean = scean; }
		inline void SetTargetTexture(Texture2D* target) { m_SceanVwieDisplay = target; }

		void LoadAssets();

		void DispalyScean();
		void DisplayToolBar();

	private:
		Scean* m_Scean;
		Texture2D* m_SceanVwieDisplay;

		mu::vec2 m_SceanCamearaPos = mu::vec2{ 0,0 };
		mu::vec3 m_SceanBackGroundColor = mu::vec3{ 0.85f , 0.f , 0.85f };
		float m_CameraZ = 1.f;

		float m_EditorDisplayScale = 40.f;
		float m_SceanCameraSpeed = 10.f;
		float m_CameraZoomSpeed = 0.05f;

		std::vector<Texture2D*> temp;


};

