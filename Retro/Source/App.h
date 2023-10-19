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
		Camera m_TempCam;
};
