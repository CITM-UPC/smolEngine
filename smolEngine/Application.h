#pragma once
#include "Module.h"
#include "Defs.h"
#include "Timer.h"
#include "PerfTimer.h"

//Modules
#include "Window.h"
#include "ImguiEnabler.h"
#include "Render.h"
#include "Input.h"

enum class AppState
{
	CREATE,
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
	std::unique_ptr<ImguiEnabler> imgui;

	bool frcap = true;

private:

	int argc = 0;
	char** args;

	std::list<Module*> modules;

	unsigned int frames = 0;
	float dt = 0;

	Timer timer;
	PerfTimer ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;
	float secondsSinceStartup = 0.0f;

	uint32 maxFrameDuration = 0;

	AppState state;
};

extern Application* app;

Application* CreateApplication(int argc, char** argv);