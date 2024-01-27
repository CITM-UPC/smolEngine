#include "Render.h"
#include "Application.h"
#include "Window.h"
#include "Defs.h"
#include <GL/glew.h>
#include "SDL2/SDL_opengl.h"
#include <IL/il.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "WwiseUtils.h"


#include "CubeImmediateMode.h"
#include "CubeVertexArray.h"
#include "CubeVertexBuffer.h"
#include "CubeInterleavedVBO.h"
#include "CubeWireframeIVBO.h"

Render::Render(bool startEnabled) : Module(startEnabled)
{
	vsync = VSYNC;
	bg_color = { 0.1f, 0.1f, 0.1f, 1.0f };
	
}

// Destructor
Render::~Render()
{
	
}

bool Render::Init()
{

	return true;
}

// Called before the first frame
bool Render::Start()
{

	//LOG("render start");
	app->input->RegisterObserver(this);
	gl_context = SDL_GL_CreateContext(app->win->window);
	if (!gl_context)
		return false;
	

	ilInit();

	if (glewInit() != GLEW_OK)
		return false;

	if (vsync && (SDL_GL_SetSwapInterval(1) != 0))
		return false;

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		return false;

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
		return false;

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClearDepth(1.0f);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
		return false;

	GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);

		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();

		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	OnResize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//comment
	AddGameObject("Assets/Street environment_V01.fbx", "Street", false);
	AddGameObject("Assets/Cube.fbx", "Sound_static_cube", false);
	AddGameObject("Assets/Cube.fbx", "Sound_moving_cube", true);
	AddGameObject("Background_music", false);
	//AddGameObject("Assets/untitled.fbx", "unreal mannequin");

	////uncomment
	//AddGameObject("Assets/Cube.fbx", "Sound_static_cube", AK::EVENTS::PLAY_AMBIENCE);
	//AddGameObject("Assets/Cube.fbx", "Sound_moving_cube", AK::EVENTS::PLAY_TALKING);
	//AddGameObject("Background_music", AK::EVENTS::PLAY_SONG1);

	dvec3 startPos = dvec3(0, 0, 0); // Posición inicial
	dvec3 endPos = dvec3(10, 10, 10); // Posición final
	float duration = 5.0f;
	const char* name = "Sound_moving_cube";
	for (auto const& object : objects)
	{	
		if (object.get()->GetStaticObject()) {
			object.get()->StartMoving(startPos, endPos, duration);
		}
		
	}

	return true;
}

// Called each loop iteration
bool Render::PreUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(app->camera->GetViewMatrixf());

	

	// light 0 on cam pos
	lights[0].SetPos(app->camera->Position.x, app->camera->Position.y, app->camera->Position.z);

	for (uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return true;
}

bool Render::Update()
{
	for (auto const& object : objects)
	{
		object->Update();
	}

	return true;
}

bool Render::PostUpdate()
{

	drawGrid(100, 1);
	drawAxis();

	DrawGameObjects();

	assert(glGetError() == GL_NONE);
	return true;
}

// Called before quitting
bool Render::CleanUp()
{
	LOG("Destroying SDL render");
	app->input->UnregisterObserver(this);
	SDL_GL_DeleteContext(gl_context);
	return true;
}


void Render::OnLeftMouseClick(int x, int y) {
	HandleRaycast(x,y);
}

void Render::OnRightMouseClick(int x, int y) {
}

void Render::OnMiddleMouseClick(int x, int y) {
}

//raycast
void Render::HandleRaycast(int mouseX, int mouseY) {
	Ray ray = GenerateRayFromScreenCoordinates(mouseX, mouseY);
	std::shared_ptr<GameObject> selectedObject = CheckRaycastIntersections(ray);

	// Deselect the currently selected object, if any
	if (currentSelectedObject) {
		currentSelectedObject->SetSelected(false);
	}

	// Update the selection
	if (selectedObject) {
		selectedObject->SetSelected(true);
		currentSelectedObject = selectedObject; // Update the currently selected object
	}
	else {
		currentSelectedObject.reset(); // No object is selected
	}
}

// Method to generate a ray from screen coordinates
Ray Render::GenerateRayFromScreenCoordinates(int mouseX, int mouseY) {
	//Convert screen coordinates to normalized device coordinates
	float x = (2.0f * mouseX) / app->win->GetWindowWidth() - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / app->win->GetWindowHeight();
	vec2 normalizedCoords(x, y);

	//Convert normalized device coordinates to clip coordinates
	vec4 clipCoords(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);

	//Convert clip coordinates to eye coordinates
	vec4 eyeCoords = inverse(app->camera->GetProjectionMatrix()) * clipCoords;
	eyeCoords = vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	//Convert eye coordinates to world coordinates
	vec4 worldCoords = inverse(app->camera->GetViewMatrix()) * eyeCoords;
	vec3 rayWorld(worldCoords.x, worldCoords.y, worldCoords.z);

	//Create the ray
	Ray ray(app->camera->Position, normalize(rayWorld));

	return ray;
}

// Method to check for intersections with objects
std::shared_ptr<GameObject> Render::CheckRaycastIntersections(const Ray& ray) {
	std::shared_ptr<GameObject> closestHitObject = nullptr;
	float closestDistance = std::numeric_limits<float>::max();

	// Iterate over all objects and check for intersection with the ray
	for (auto& object : objects) {

		if (object->GetBoundingBox().Intersects(ray)) {
			closestHitObject = object;
			break;
		}

		float distance;
		if (object->Intersects(ray, distance)) {
			if (distance < closestDistance) {
				closestDistance = distance;
				closestHitObject = object;
			}
		}
	}

	return closestHitObject;
}

void Render::DrawGameObjects()
{
	for (auto const& object : objects)
	{
		object->Draw();
	}
}

void Render::AddGameObject()
{
	std::shared_ptr<GameObject> object;
	object = std::make_shared<GameObject>();

	objects.push_back(object);
}

//uncomment
//void Render::AddGameObject(const std::string& path, const std::string& n, AkUniqueID soundEventID, bool StaticObject) 
//{
//	std::shared_ptr<GameObject> object = std::make_shared<GameObject>(path, n, soundEventID, StaticObject);
//
//	objects.push_back(object);
//}
//
//void Render::AddGameObject(const std::string& n, AkUniqueID soundEventID, bool StaticObject)
//{
//	std::shared_ptr<GameObject> object = std::make_shared<GameObject>(n, soundEventID, StaticObject);
//
//	objects.push_back(object);
//}

//ucomment
void Render::AddGameObject(const std::string& path, const std::string& n, bool StaticObject)
{
	std::shared_ptr<GameObject> object;
	object = std::make_shared<GameObject>(path, n, StaticObject);

	objects.push_back(object);
}

void Render::AddGameObject(const std::string& n, bool StaticObject)
{
	std::shared_ptr<GameObject> object;
	object = std::make_shared<GameObject>(n, StaticObject);

	objects.push_back(object);
}

void Render::AddGameObject(const std::string& n)
{
	std::shared_ptr<GameObject> object;
	object = std::make_shared<GameObject>(n);

	objects.push_back(object);
}

void Render::SetBackgroundColor(ImVec4 color)
{
	bg_color = color;
}

void Render::drawAxis()
{
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0.8, 0, 0);
	glColor3ub(0, 255, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0.8, 0);
	glColor3ub(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 0.8);
	glEnd();
}

void Render::drawGrid(int grid_size, int grid_step)
{
	glLineWidth(1.0);
	glColor3ub(128, 128, 128);

	glBegin(GL_LINES);
	for (int i = -grid_size; i <= grid_size; i += grid_step) {
		//XY plane
		glVertex2i(i, -grid_size);
		glVertex2i(i, grid_size);
		glVertex2i(-grid_size, i);
		glVertex2i(grid_size, i);

		//XZ plane
		glVertex3i(i, 0, -grid_size);
		glVertex3i(i, 0, grid_size);
		glVertex3i(-grid_size, 0, i);
		glVertex3i(grid_size, 0, i);
	}
	glEnd();
}

void Render::drawQuadFaceTriangles(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d)
{
	glVertex3fv(&a.x);
	glVertex3fv(&b.x);
	glVertex3fv(&c.x);

	glVertex3fv(&c.x);
	glVertex3fv(&d.x);
	glVertex3fv(&a.x);
}

void Render::cubeTest()
{
	glm::vec3 a = glm::vec3(-1, -1, 1);
	glm::vec3 b = glm::vec3(1, -1, 1);
	glm::vec3 c = glm::vec3(1, 1, 1);
	glm::vec3 d = glm::vec3(-1, 1, 1);
	glm::vec3 e = glm::vec3(-1, -1, -1);
	glm::vec3 f = glm::vec3(1, -1, -1);
	glm::vec3 g = glm::vec3(1, 1, -1);
	glm::vec3 h = glm::vec3(-1, 1, -1);

	glBegin(GL_TRIANGLES);
	//front
	glColor3f(255, 0, 0);
	drawQuadFaceTriangles(a, b, c, d);
	//back
	glColor3f(0, 255, 0);
	drawQuadFaceTriangles(h, g, f, e);
	//left
	glColor3f(0, 0, 255);
	drawQuadFaceTriangles(e, a, d, h);
	//right
	glColor3f(255, 255, 0);
	drawQuadFaceTriangles(b, f, g, c);
	//top
	glColor3f(255, 255, 255);
	drawQuadFaceTriangles(d, c, g, h);
	//bottom
	glColor3f(0, 0, 0);
	drawQuadFaceTriangles(b, a, e, f);
	glEnd();
}

void Render::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
