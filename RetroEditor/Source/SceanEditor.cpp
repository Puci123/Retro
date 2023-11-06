#include <filesystem>

#include "SceanEditor.h"
#include "Draw2D.h"

SceanEditor::SceanEditor(int32_t screanWidth, int32_t screanHeight)
	:m_SceanVwieDisplay(nullptr), m_Scean(nullptr)
{
	

}

SceanEditor::~SceanEditor()
{}

void SceanEditor::LoadAssets(const std::string& path)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string fileName  = entry.path().filename().string();
		int32_t splitPos = fileName.find('.');


		if (splitPos != std::string::npos)
		{

			std::string extection = fileName.substr(splitPos, splitPos + 3);
			if (extection == ".png")
			{
				LOG("LODING ASSET: " << entry.path() << " with extection: " << extection);
				m_TilesAssets.push_back(new Texture2D(entry.path().string()));
			}
			else
			{
				LOG_ERROR("ASSET HAVE INVALID EXTECTION: " << entry.path());
			}
		}
		else
		{
			LOG_ERROR("THERE IS AOTHER DIRECTORY: " << entry.path());

		}
	
	}

}

void SceanEditor::DispalyScean()
{


	//======================  Draw scean in editor	==============================//

	mu::vec2 cellSize = mu::vec2{ m_EditorDisplayScale,m_EditorDisplayScale };
	mu::vec2 speartationLineSize = mu::vec2{ 2.f, 2.f };
	mu::vec3 cellColor = mu::vec3{ 0.f,0.f,0.f };


	cellSize = cellSize / m_CameraZ;

	Draw2D::ClearTexture(m_SceanVwieDisplay, m_SceanBackGroundColor);

	for (int32_t y = 0; y < m_Scean->GetHeight(); y++)
	{
		for (int32_t x = 0; x < m_Scean->GetWidth(); x++)
		{
			if (m_Scean->GetCellValue(x, y) > 0) cellColor = mu::vec3{ 0.f,0.f,0.f };
			else cellColor = mu::vec3{ 1.f,1.f,1.f };

			mu::vec2 celCenter = mu::vec2{ x * cellSize.x,  y * cellSize.y };

			//Project form world space to screan space
			celCenter = celCenter - m_SceanCamearaPos;

			Draw2D::DrawRect(cellSize - speartationLineSize, celCenter, cellColor, m_SceanVwieDisplay);
		}
	}


	mu::vec2 cameraPos = mu::vec2{ m_Scean->GetCamera().Pos().x * cellSize.x - m_SceanCamearaPos.x, m_Scean->GetCamera().Pos().y * cellSize.y - m_SceanCamearaPos.y };
	Draw2D::DrawRect(cellSize, cameraPos, mu::vec3{ 0,0,1 }, m_SceanVwieDisplay);


	//======================  Mouse postion ==============================//
	ImGui::Begin("Scean");

	if (ImGui::IsWindowFocused())
	{
		//Get in window mouse pos
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();

		mu::vec2 mousePos = mu::vec2{ ImGui::GetMousePos().x - ImGui::GetWindowPos().x,ImGui::GetMousePos().y - ImGui::GetWindowPos().y};
		mu::vec2 windowMax = mu::vec2{ ImGui::GetWindowContentRegionMax().x, ImGui::GetWindowContentRegionMax().y };
		mu::vec2 windowMin = mu::vec2{ ImGui::GetWindowContentRegionMin().x, ImGui::GetWindowContentRegionMin().y };

		mousePos.x = mu::Clamp01(mousePos.x / (windowMax.x - windowMin.x)) * m_SceanVwieDisplay->GetWidth();
		mousePos.y = mu::Clamp01(1 - mousePos.y / (windowMax.y - windowMin.y)) * m_SceanVwieDisplay->GetHeight();

		//Get in grid Pos

		mu::vec2 mousePos2Cam = mousePos + m_SceanCamearaPos + cellSize / 2;

		float perX = mu::Clamp01(mousePos2Cam.x / ((m_Scean->GetWidth() - 1) * cellSize.x));
		float perY = mu::Clamp01(mousePos2Cam.y / ((m_Scean->GetHeight() - 1) * cellSize.y));

		mu::vec2Int inGridPos = mu::vec2Int(static_cast<int32_t>(perX * (m_Scean->GetWidth() - 1)), static_cast<int32_t>(perY * (m_Scean->GetHeight() - 1)));


		//Test draw tareget cell in diffrent color
		mu::vec2 rectPos = mu::vec2{ inGridPos.x * cellSize.x, inGridPos.y * cellSize.y };
		rectPos = rectPos - m_SceanCamearaPos;

		Draw2D::DrawRectFrame(cellSize, rectPos, 5, mu::vec3{ 0,1,0 }, m_SceanVwieDisplay);


		//Mouse
		if (ImGui::IsMouseClicked(0, true) && curentSelected > -1)
		{
			m_Scean->InseretWall(inGridPos, curentSelected + 1);
		}
		else if(ImGui::IsMouseClicked(1,true))
		{
			m_Scean->InseretWall(inGridPos, 0);
		}
	}

	//========================== RENDER ==========================// 

	m_SceanVwieDisplay->Update();

	//Display taraget in scean viwe
	ImVec2 viwieSize = ImGui::GetContentRegionMax();
	viwieSize = ImVec2(viwieSize.x, viwieSize.y - ImGui::GetFrameHeight() * 2);

	m_SceanVwieDisplay->Bind();
	ImGui::Image((void*)(intptr_t)(m_SceanVwieDisplay->GetID()), ImVec2(static_cast<float>(viwieSize.x), static_cast<float>(viwieSize.y)), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f)); //Draw target texture
	m_SceanVwieDisplay->Unbind();


	//========================== Input Test ==========================// 


	if (ImGui::IsWindowFocused())
	{

		//Camera movment
		if (ImGui::IsKeyPressed(ImGuiKey_UpArrow))			m_SceanCamearaPos.y += m_SceanCameraSpeed;
		else if (ImGui::IsKeyPressed(ImGuiKey_DownArrow))	m_SceanCamearaPos.y -= m_SceanCameraSpeed;
		else if (ImGui::IsKeyPressed(ImGuiKey_RightArrow))	m_SceanCamearaPos.x += m_SceanCameraSpeed;
		else if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow))	m_SceanCamearaPos.x -= m_SceanCameraSpeed;
		else if (ImGui::IsKeyPressed(ImGuiKey_W))			m_CameraZ += m_CameraZoomSpeed;
		else if (ImGui::IsKeyPressed(ImGuiKey_S))			m_CameraZ -= m_CameraZoomSpeed;

		if (m_CameraZ < 0.75f) m_CameraZ = 0.75f;



	}


	ImGui::End();
}


void SceanEditor::DisplayToolBar()
{
	ImGui::Begin("ToolBar");

	if(ImGui::CollapsingHeader("Tiles"))
	{
		for (size_t i = 0; i < m_TilesAssets.size(); i++)
		{
			if (i == m_curentSelectedButton) ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);

			m_TilesAssets[i]->Bind();
			if (ImGui::ImageButton((void*)(intptr_t)(m_TilesAssets[i]->GetID()), ImVec2(static_cast<float>(m_TilesAssets[i]->GetWidth()), static_cast<float>(m_TilesAssets[i]->GetHeight())),ImVec2(1,1),ImVec2(0,0))) 
			{
				curentSelected = m_Scean->AddMapTileTexture(*m_TilesAssets[i], m_TilesAssets[i]->GetAssetName());
				m_curentSelectedButton = i;
			}
			m_TilesAssets[i]->Unbind();

			if (i == m_curentSelectedButton) ImGui::PopStyleColor(1);
		}
	}

	ImGui::ShowMetricsWindow();
	ImGui::End();
}

