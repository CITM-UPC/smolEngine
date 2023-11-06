#include "ImguiEnabler.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "Application.h"

ImguiEnabler::ImguiEnabler(bool startEnabled) : Module(startEnabled)
{

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows


	// Setup Dear ImGui style

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();



	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
}

// Destructor
ImguiEnabler::~ImguiEnabler()
{
}

bool ImguiEnabler::Init()
{
	ImGui_ImplOpenGL3_Init("#version 130");
	return true;
}

// Called before render is available
bool ImguiEnabler::Start()
{
	//LOG("Init Imgui Enabler");
	bool ret = true;

	return ret;
}

// Called before quitting
bool ImguiEnabler::CleanUp()
{
	//LOG("Destroying Imgui Enabler");

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ImguiEnabler::BeginUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(app->win->window);
	ImGui::NewFrame();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(10.0f, 10.0f), ImGuiDockNodeFlags_PassthruCentralNode);
	//ImGuizmo::BeginFrame();
}

void ImguiEnabler::EndUI()
{
	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize = ImVec2((float)app->win->width, (float)app->win->height);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	SDL_GL_SwapWindow(app->win->window);
}
