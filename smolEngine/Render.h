#pragma once

#include "Module.h"
#include "SDL2/SDL.h"
#include <glm/gtc/type_ptr.hpp>

class Render : public Module
{
public:

	Render(bool startEnabled);

	// Destructor
	virtual ~Render();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();

private:
	void drawAxis();

	void drawGrid(int grid_size, int grid_step);

public:
	bool vsync;
	SDL_GLContext gl_context;
};