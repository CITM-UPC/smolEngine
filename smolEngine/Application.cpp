#include "Application.h"
#include <SDL2/SDL_timer.h>

// Constructor
Application::Application(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;
	timer = Timer();

	win = std::make_unique<Window>(true);
	//input = eastl::make_unique<Input>(true);
	render = std::make_unique<Render>(true);
	imgui = std::make_unique<ImguiEnabler>(true);

	// Ordered, render is the last to execute
	AddModuleFront(render.get());
	AddModuleFront(imgui.get());
	//AddModuleFront(input.get());
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
			//Log errors
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
	timer.Start();
	startupTime.Start();
	lastSecFrameTime.Start();

	for (auto const& item : modules)
	{
		if (item->IsEnabled())
			if (!item->Start())
				return false;
	}
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

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	frameTime.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{

	frameCount++;
	secondsSinceStartup = startupTime.ReadSec();
	//dt = frameTime.ReadMSec();
	dt = frameTime.ReadSec();
	lastSecFrameCount++;
	if (lastSecFrameTime.ReadMSec() > 1000) {
		lastSecFrameTime.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
		// Average FPS for the whole game life
		averageFps = (averageFps + framesPerSecond) / 2;
	}


	if (frcap)
	{
		float delay = float(maxFrameDuration) - dt;

		PerfTimer delayTimer = PerfTimer();
		delayTimer.Start();
		if (maxFrameDuration > 0 && delay > 0) {
			SDL_Delay(delay);
			//LOG("We waited for %f milliseconds and the real delay is % f", delay, delayTimer.ReadMs());
			//dt = maxFrameDuration;
		}
		else {
			//LOG("No wait");
		}
	}
	if (framesPerSecond != 0) dt = (float)(1 / (float)framesPerSecond);

	// Shows the time measurements in the window title
	static char title[256];
	sprintf_s(title, 256, "Engine | FPS: %i, Av.FPS: %.2f, Last-frame MS (dt): %.3f, vsync: %s",
		framesPerSecond, averageFps, dt, frcap ? "on" : "off");


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
		if (!m->Update(dt)) return false;
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