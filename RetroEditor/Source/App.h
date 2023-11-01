#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<string>
#include<memory>

#include "ImGUI/imgui_impl_opengl3.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_internal.h"

#include "Scean.h"
#include "Camera.h"

class App
{
	public:
		App(uint32_t windowWidth, uint32_t windowhHeight, const std::string& name);
		~App();
		

		void Update();
		void Loop();


		inline bool IsRunning() const { return true; }

	private:
		uint32_t m_WindwoWidth;
		uint32_t m_WindowHeight;
		
		GLFWwindow* m_Window;
		ImGuiIO* m_ImGuiIO;

		Scean m_Scean;
		Texture2D* m_SceanVwieDisplay;


		mu::vec2 m_SceanCamearaPos;
		mu::vec3 m_SceanBackGroundColor = mu::vec3{ 0.85f , 0.f , 0.85f };
		float m_CameraZ = 1.f;

		float m_EditorDisplayScale	= 40.f;
		float m_SceanCameraSpeed	= 10.f;
		float m_CameraZoomSpeed		= 0.05f;

	private:
		void DrawViwePort();
		void DrawSceanViwie();
		void DrawEditorPorpoerties();
		
		
};
