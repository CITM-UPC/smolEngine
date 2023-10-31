#pragma once

#include "Module.h"
#include "Defs.h"
#include "SDL2/SDL.h"

class Window : public Module
{
	Window(bool startEnabled);

	// Destructor
	virtual ~Window();

	// Called before render is available
	bool Start();

	// Called before quitting
	bool CleanUp();

	// Changae title
	void SetTitle(const char* title);

	//change icon
	/*void SetIcon(const char* new_icon);*/

	// Retrive window size
	void GetWindowSize(uint& width, uint& height) const;

public:
	// The window we'll be rendering to
	SDL_Window* window;

	// The surface contained by the window
	SDL_Surface* screenSurface;

	bool fullscreen = 0;

	std::string title = WINDOW_TITLE;
	uint width = 0;
	uint height = 0;
};
