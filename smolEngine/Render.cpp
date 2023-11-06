#include "Render.h"
#include "Application.h"
#include "Defs.h"
#include <GL/glew.h>
#include <IL/il.h>


#include "CubeImmediateMode.h"
#include "CubeVertexArray.h"
#include "CubeVertexBuffer.h"
#include "CubeInterleavedVBO.h"
#include "CubeWireframeIVBO.h"

#include "GraphicObject.h"

Render::Render(bool startEnabled) : Module(startEnabled)
{
	vsync = true;
	bg_color = { 0.1f, 0.1f, 0.1f, 1.0f };
}

// Destructor
Render::~Render()
{}

// Called before the first frame
bool Render::Start()
{
	//LOG("render start");
	gl_context = SDL_GL_CreateContext(app->win->window);
	SDL_GL_MakeCurrent(app->win->window, gl_context);
	if (gl_context == NULL)
	{
		return false;
	}

	if (vsync && SDL_GL_SetSwapInterval(1) != 0)
	{
		//Log error
	}


	ilInit();
	glewInit();

	glViewport(0, 0, app->win->width, app->win->height);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return true;
}

// Called each loop iteration
bool Render::PreUpdate()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera.fov, camera.aspect, camera.zNear, camera.zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
		camera.center.x, camera.center.y, camera.center.z,
		camera.up.x, camera.up.y, camera.up.z);

	return true;
}

bool Render::Update(float dt)
{
	drawGrid(100, 1);
	drawAxis();

	assert(glGetError() == GL_NONE);
	return true;
}

bool Render::PostUpdate()
{
	glClearColor(bg_color.x * bg_color.w, bg_color.y * bg_color.w, bg_color.z * bg_color.w, bg_color.w);
	return true;
}

// Called before quitting
bool Render::CleanUp()
{
	LOG("Destroying SDL render");

	SDL_GL_DeleteContext(gl_context);
	return true;
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
