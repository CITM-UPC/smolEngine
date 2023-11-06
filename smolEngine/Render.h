#pragma once

#include "Module.h"
#include "Camera.h"
#include "SDL2/SDL.h"
#include "imgui.h"
#include "Defs.h"
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

	void SetBackgroundColor(ImVec4 color);

private:
	void drawAxis();

	void drawGrid(int grid_size, int grid_step);

public:
	Camera camera;
	ImVec4 bg_color;
	bool vsync;
	SDL_GLContext gl_context;
};