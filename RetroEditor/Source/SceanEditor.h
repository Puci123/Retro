#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include "Scean.h"
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

		void LoadAssets(const std::string& path);

		void DispalyScean();
		void DisplayToolBar();
		void DisplayHierarhy();
		void DisplayProperties();

	private:
		Scean* m_Scean;
		Texture2D* m_SceanVwieDisplay;
		Sprite* m_SelectedSprite = nullptr;

		mu::vec2 m_SceanCamearaPos = mu::vec2{ 0,0 };
		mu::vec3 m_SceanBackGroundColor = mu::vec3{ 0.33f , 0.f , 0.33f };
		float m_CameraZ = 1.f;

		float m_EditorDisplayScale = 40.f;
		float m_SceanCameraSpeed = 10.f;
		float m_CameraZoomSpeed = 0.05f;

		mu::vec2 m_SceanCellSize = mu::vec2{ 0,0 };

		std::vector<Texture2D*> m_TilesAssets;
		
		int32_t curentSelected			= -1;		//	-1 none
		int32_t m_CurentSelcedSprite	= -1;		// -1 none
		int32_t m_curentSelectedButton	= -1;		// -1 none 
		int32_t m_CurrentLayer			= 0;		//	0 walls, 1 sprites
		
		mu::vec2 m_MousePos			= mu::vec2{ 0,0 };
		mu::vec2Int m_GridMousePos  = mu::vec2Int{ 0,0 };

	private:
		void Input();
		void WallLayer();
		void SpriteLayer();
};

