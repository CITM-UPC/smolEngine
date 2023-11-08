#pragma once

#include "Module.h"
#include "Camera.h"
#include "imgui.h"
#include "Light.h"
#include "Defs.h"
#include "SDL2/SDL.h"
#include <glm/gtc/type_ptr.hpp>

#define MAX_LIGHTS 8

class Render : public Module
{
public:

	Render(bool startEnabled);

	// Destructor
	virtual ~Render();

	// Called when adding the modules to the application (cannot use app->)
	bool Init();
	
	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update();
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void SetBackgroundColor(ImVec4 color);
	void OnResize(int width, int height);


private:
	void drawAxis();

	void drawGrid(int grid_size, int grid_step);

public:
	Light lights[MAX_LIGHTS];
	ImVec4 bg_color;
	bool vsync;
	SDL_GLContext gl_context = NULL;
	mat4x4 ProjectionMatrix;
};