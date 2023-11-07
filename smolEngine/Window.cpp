#include "Window.h"

Window::Window(bool startEnabled) : Module(startEnabled)
{
	window = NULL;
	screenSurface = NULL;
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
}

// Destructor
Window::~Window()
{
}

bool Window::Init()
{
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		//LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		// Create window
		SDL_version compiled;
		SDL_VERSION(&compiled);
		std::cout << "SDL Compiled with " << std::to_string(compiled.major) << '.' << std::to_string(compiled.minor) << '.' << std::to_string(compiled.patch);

		SDL_version linked;
		SDL_GetVersion(&linked);
		std::cout << "SDL Linked with " << std::to_string(linked.major) << '.' << std::to_string(linked.minor) << '.' << std::to_string(linked.patch);


		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if (FULLSCREEN) flags |= SDL_WINDOW_FULLSCREEN;
		if (BORDERLESS) flags |= SDL_WINDOW_BORDERLESS;
		if (RESIZABLE) flags |= SDL_WINDOW_RESIZABLE;
		if (FULLSCREEN_WINDOW) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		if (FULLSCREEN_WINDOW)
		{
			fullscreen = true;
		}
		else
		{
			fullscreen = false;
		}


		//// setup SDL window
		//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		//SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//// GL 3.1 + GLSL 130
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (window == NULL)
		{
			//LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			// Get window surface
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return ret;
}

// Called before render is available
bool Window::Start()
{
	//LOG("Init SDL window & surface");
	bool ret = true;


	return ret;
}

// Called before quitting
bool Window::CleanUp()
{
	//LOG("Destroying SDL window and quitting all SDL systems");

	// Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	// Quit SDL subsystems
	SDL_Quit();
	return true;
}

// Set new window title
void Window::SetTitle(const char* new_title)
{
	SDL_SetWindowTitle(window, new_title);
}

void Window::GetWindowSize(uint& width, uint& height) const
{
	width = this->width;
	height = this->height;
}