#include <iostream>

#include "App.h"
#include "Renderer.h"
#include "Draw2D.h"


App::App(uint32_t windowWidth, uint32_t windowhHeight, const std::string& name)
	:m_WindwoWidth(windowWidth), m_WindowHeight(windowhHeight), m_SceanEditor(m_WindwoWidth,m_WindowHeight)
{
	//================================== INT WINDOW ==========================//

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	m_Window = glfwCreateWindow(m_WindwoWidth, m_WindowHeight, name.c_str(), NULL, NULL);
	
	if (!m_Window)
		std::cout << "Can't create window" << std::endl;

	glfwMakeContextCurrent(m_Window);
	
	glewInit();
	glfwSwapInterval(1);	 // 1/0 | enable/disable vsync


	//================================== Init ImGui ================================== //

	//set up IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	m_ImGuiIO = &ImGui::GetIO(); (void)m_ImGuiIO;
	m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	//set style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (m_ImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 1.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 130");


	//Addition setup
	m_Scean.SetCam(Camera(mu::vec2{ 22.0f, 12.f }, mu::vec2{ -1.0f, 0.f }, mu::vec2{ 0.f, 0.66f }, new Texture2D(m_WindwoWidth, m_WindowHeight)));
	m_Scean.GetCamera().SetFOV(70.f);

	Renderer::Render(m_Scean, m_Scean.GetCamera());
	m_Scean.GetCamera().GetTarget()->Update();

	//Editor setup
	m_SceanVwieDisplay = new Texture2D(m_WindwoWidth, m_WindowHeight);
	m_SceanEditor.OpenScean(&m_Scean);
	m_SceanEditor.SetTargetTexture(m_SceanVwieDisplay);

	//Load assetes
	m_SceanEditor.LoadAssets("Resources\\Textures\\");
}

App::~App()
{


}

void App::Loop()
{
	/* Poll for and process events */
	glfwPollEvents();

	//Render scean
	Renderer::Render(m_Scean, m_Scean.GetCamera());

	//================================== Render GUI ================================== //

	//Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// ------------------------------ GUI CODE HERE ---------------------//
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()); //Enable docking UI

	DrawViwePort();
	m_SceanEditor.DispalyScean();
	m_SceanEditor.DisplayToolBar();
	m_SceanEditor.DisplayHierarhy();
	m_SceanEditor.DisplayProperties();
	//DrawEditorPorpoerties();
	
	// -------------------------------------------------------------------//


	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	if (m_ImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}


	glfwSwapBuffers(m_Window);
	Update();

}

void App::DrawViwePort()
{
	ImGui::Begin("Vwie port");


	//Camera movment 
	//TO DO abstract to anthore class

	mu::vec2 traslation = mu::vec2{ 0.f,0.f };
	mu::vec2 camFwd = m_Scean.GetCamera().Dir();

	//======================== Game camera movment TEST //========================

	//TODO dect if item is hovered 

	if (ImGui::IsWindowFocused())
	{

		if (ImGui::IsKeyPressed(ImGuiKey_UpArrow))
		{
			traslation.x = camFwd.x * 0.2f;
			traslation.y = camFwd.y * 0.2f;

		}
		else if (ImGui::IsKeyPressed(ImGuiKey_DownArrow))
		{
			traslation.x = -camFwd.x * 0.2f;
			traslation.y = -camFwd.y * 0.2f;
		}

		if (ImGui::IsKeyPressed(ImGuiKey_D))
		{
			m_Scean.RoteateCamera(5.f);
		}
		else if (ImGui::IsKeyPressed(ImGuiKey_A))
		{
			m_Scean.RoteateCamera(-5.f);
		}
		else if (ImGui::IsKeyPressed(ImGuiKey_RightArrow))
		{
			mu::vec2 temp = mu::vec2{ camFwd.y, -camFwd.x };
			traslation.x = temp.x * 0.2f;
			traslation.y = temp.y * 0.2f;
		}
		else if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow))
		{
			mu::vec2 temp = mu::vec2{ -camFwd.y, camFwd.x };
			traslation.x = temp.x * 0.2f;
			traslation.y = temp.y * 0.2f;
		}
	}

	m_Scean.MoveCam(traslation);


	//======================== ACTULY DARAW ====================================//
	
	ImVec2 viwieSize = ImGui::GetContentRegionMax();
	viwieSize = ImVec2(viwieSize.x, viwieSize.y - ImGui::GetFrameHeight()  * 2);


	Texture2D* targetTexture = m_Scean.GetCamera().GetTarget();

	targetTexture->Bind();
	ImGui::Image((void*)(intptr_t)(targetTexture->GetID()), ImVec2(static_cast<float>(viwieSize.x), static_cast<float>(viwieSize.y)), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f)); //Draw target texture
	targetTexture->Unbind();

	ImGui::End();

}


void App::DrawEditorPorpoerties()
{
	ImGui::Begin("Properites");

	if (ImGui::CollapsingHeader("Game camera")) 
	{
		Camera& cam				= m_Scean.GetCamera();
		mu::vec2 cameraPos		= cam.Pos();
		float rotation			= cam.GetAangleRotation();
		float fov				= cam.GetFov();

		ImGui::DragFloat2("Pos ", reinterpret_cast<float*>(&cameraPos), 0.1f);
		ImGui::DragFloat("Dir ", reinterpret_cast<float*>(&rotation));
		ImGui::DragFloat("Camera clip ", reinterpret_cast<float*>(&fov));

		
		cam.SetPos(cameraPos);
		cam.SetRotation(rotation);
		cam.SetFOV(fov);
	}

	
	ImGui::End();
}

void App::Update() 
{
	//================= UPDARE GAME OBJECTS IN SCEAN =================// 
	m_Scean.UpdateSprites();


}
