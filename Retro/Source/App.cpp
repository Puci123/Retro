#include <iostream>
#include "App.h"
#include "Renderer.h"

App::App(uint32_t windowWidth, uint32_t windowhHeight, const std::string& name)
	:m_WindwoWidth(windowWidth), m_WindowHeight(windowhHeight)
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
	Render(m_Scean);
	m_Scean.GetCamera().GetTarget()->Update();

}

App::~App()
{


}

void App::Loop()
{
	/* Poll for and process events */
	glfwPollEvents();

	//Render scean
	Render(m_Scean);

	//================================== Input handle ================================== //
	
	//TO DO: MOVING CAMERA
	mu::vec2 traslation = mu::vec2{ 0.f,0.f };
	mu::vec2 camFwd = m_Scean.GetCamera().Dir();



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

	if (ImGui::IsKeyPressed(ImGuiKey_RightArrow)) m_Scean.RoteateCamera(0.1f);
	if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow)) m_Scean.RoteateCamera(-0.1f);

	m_Scean.MoveCam(traslation);

	//================================== Render GUI ================================== //

	//Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// ------------------------------ GUI CODE HERE ---------------------//
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()); //Enable docking UI

	//Vwie port Panel 
	ImGui::Begin("Vwie port");
	{
		//TO DO: Scaling window
		Texture2D* targetTexture = m_Scean.GetCamera().GetTarget();
		
		targetTexture->Bind();
		ImGui::Image((void*)(intptr_t)(targetTexture->GetID()), ImVec2(static_cast<float>(m_WindwoWidth), static_cast<float>(m_WindowHeight - 8.0)), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f)); //Draw target texture
		targetTexture->Unbind();
	}
	ImGui::End();

	//Property Panle 
	ImGui::Begin("Scean");
	{

	}
	ImGui::End();

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

}
