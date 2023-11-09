#pragma once
#include "Module.h"
#include "Defs.h"
#include <chrono>
#include <thread>

//Modules
#include "Window.h"
#include "ImguiEnabler.h"
#include "Render.h"
#include "Input.h"
#include "Camera.h"

namespace Timer
{
	using namespace std;
	using namespace chrono;

	static const unsigned int targetFPS = 60;
	static const auto dt = 1.0s / targetFPS;
}

enum class AppState
{
	CREATE = 0,
	UPDATE,
	END,
	FAIL,
	QUIT
};

class Application
{
public:
	Application(int argc, char* args[]);

	virtual ~Application();

	void Run();

	void AddModuleFront(Module* module);

	void AddModuleBack(Module* module);

	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetVersion() const {
		return "0.1";
	}


private:

	bool Start();

	bool Update();

	bool CleanUp();

	void PrepareUpdate();

	void FinishUpdate();

	bool PreUpdate();

	bool DoUpdate();

	bool PostUpdate();

	bool RenderUI();



public:

	// Modules
	std::unique_ptr<Window> win;
	std::unique_ptr<Render> render;
	std::unique_ptr<Input> input;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<ImguiEnabler> imgui;


private:

	int argc = 0;
	char** args;

	std::list<Module*> modules;

	Timer::steady_clock::time_point frameStart;
	Timer::steady_clock::time_point frameEnd;
	Timer::nanoseconds frameDuration;

	//std::vector<float> fpsHistory;

	float averageFps = 0.0f;

	bool frcap = FRAMECAP;

	AppState state;
};

extern Application* app;

Application* CreateApplication(int argc, char** argv);