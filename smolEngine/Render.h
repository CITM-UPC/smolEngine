#pragma once

#include "Module.h"
#include "Camera.h"
#include "Mesh.h"
#include "imgui.h"
#include "Light.h"
#include "Defs.h"
#include "Ray.h"
#include "Input.h"
#include "SDL2/SDL.h"
#include <glm/gtc/type_ptr.hpp>

#include "GameObject.h"

#define MAX_LIGHTS 8

class Render : public Module, public IInputObserver
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

	//raycast
	void HandleRaycast(int mouseX, int mouseY);
	Ray GenerateRayFromScreenCoordinates(int mouseX, int mouseY);
	std::shared_ptr<GameObject> CheckRaycastIntersections(const Ray& ray);
	std::shared_ptr<GameObject> CheckRaycastForSelection(const Ray& ray);

	// Called before quitting
	bool CleanUp();

	void DrawGameObjects();

	void AddGameObject(const std::string& path, const std::string& n);
	void AddGameObject(const std::string& n);
	void AddGameObject();

	void SetBackgroundColor(ImVec4 color);
	void OnResize(int width, int height);


	void drawQuadFaceTriangles(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
	void cubeTest();

	//observer
	void OnLeftMouseClick(int x, int y) override;
	void OnRightMouseClick(int x, int y) override;
	void OnMiddleMouseClick(int x, int y) override;



private:
	void drawAxis();

	void drawGrid(int grid_size, int grid_step);

public:
	Light lights[MAX_LIGHTS];

	std::shared_ptr<GameObject> currentSelectedObject;

	std::list<std::shared_ptr<GameObject>> objects;

	ImVec4 bg_color;
	bool vsync = 0;
	SDL_GLContext gl_context = NULL;
	mat4x4 ProjectionMatrix;
};