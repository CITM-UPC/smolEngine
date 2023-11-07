#include "Application.h"
#include <SDL2/SDL_timer.h>
#include <imgui_impl_opengl3.h>

// Constructor
Application::Application(int argc, char* args[]) : argc(argc), args(args)
{
	state = AppState::CREATE;

	win = std::make_unique<Window>(true);
	input = std::make_unique<Input>(true);
	render = std::make_unique<Render>(true);
	imgui = std::make_unique<ImguiEnabler>(true);

	// Ordered, render is the last to execute
	AddModuleFront(render.get());
	AddModuleFront(imgui.get());
	AddModuleFront(input.get());
	AddModuleFront(win.get());
}

// Destructor
Application::~Application() = default;

void Application::Run()
{
	while (state != AppState::QUIT)
	{
		switch (state)
		{
		case AppState::CREATE:
			if (Start())
				state = AppState::UPDATE;
			else
				state = AppState::END;
			break;

		case AppState::UPDATE:
			if (!Update())
				state = AppState::END;
			break;

		case AppState::END:
			if (CleanUp())
				state = AppState::QUIT;
			else
				state = AppState::FAIL;
			break;

		case AppState::FAIL:
			//TODO: Log errors
			state = AppState::QUIT;
			break;

		}
	}
}

void Application::AddModuleFront(Module * module)
{
	module->Init();
	modules.push_front(module);
}

void Application::AddModuleBack(Module* module)
{
	module->Init();
	modules.push_back(module);
}

// Called before the first frame
bool Application::Start()
{

	for (auto const& item : modules)
	{
		if (item->IsEnabled())
			if (!item->Start())
				return false;
	}

	ImGui_ImplSDL2_InitForOpenGL(app->win->window, app->render->gl_context);
	ImGui_ImplOpenGL3_Init("#version 130");

	//LOG("----------------- Time Start(): %f", timer.ReadMSec());

	return true;
}

// Called each loop iteration
bool Application::Update()
{
	bool ret = true;
	PrepareUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	if (ret == true)
		ret = RenderUI();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	frameStart = std::chrono::steady_clock::now();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	frameEnd = std::chrono::steady_clock::now();
	frameDuration = frameEnd - frameStart;

	if (frameDuration < Timer::dt)
		std::this_thread::sleep_for(Timer::dt - frameDuration);

	const auto frameEndAfterSleep = std::chrono::steady_clock::now();
	const auto frameDurationAfterSleep = frameEndAfterSleep - frameStart;


	float lastFPS = 0.0f;
	if(frcap)
		lastFPS = 1.0f / (frameDurationAfterSleep.count() * 0.000000001f);


	averageFps = (averageFps + lastFPS) / 2;
	fpsHistory.push_back(lastFPS);

	// Replace oldest data in the history
	if (fpsHistory.size() > 100) fpsHistory.erase(fpsHistory.begin());

	// Shows the time measurements in the window title
	static char title[256];
	sprintf_s(title, 256, "smolEngine | FPS: %.2f, Av.FPS: %.2f, Last-frame MS (dt): %.3f, frame cap: %s",
		lastFPS, averageFps, Timer::dt, frcap ? "on" : "off");


	app->win->SetTitle(title);
}

// Call modules before each loop iteration
bool Application::PreUpdate()
{
	for (auto const& m : modules)
	{
		if (!m->active) continue;
		if (!m->PreUpdate()) return false;
}

	return true;
}

// Call modules on each loop iteration
bool Application::DoUpdate()
{
	for (auto const& m : modules)
	{
		if (!m->active) continue;
		if (!m->Update()) return false;
	}

	return true;
}

// Call modules after each loop iteration
bool Application::PostUpdate()
{
	for (auto const& m : modules)
	{
		if (!m->active) continue;
		if (!m->PostUpdate()) return false;
	}

	return true;
}

bool Application::RenderUI()
{
	imgui->BeginUI();
	for (auto const& m : modules)
	{
		if (!m->active) continue;
		if (!m->OnRenderUI()) return false;
	}
	imgui->EndUI();

	return true;
}

// Called before quitting
bool Application::CleanUp()
{
	for (auto const& m : modules)
		if (!m->CleanUp()) return false;

	return true;
}

// ---------------------------------------
int Application::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* Application::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}