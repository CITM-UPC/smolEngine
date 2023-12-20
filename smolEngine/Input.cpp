#include "Application.h"
#include "Input.h"
#include "Defs.h"

#define MAX_KEYS 300

Input::Input(bool start_enabled) : Module(start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KEY_STATE) * MAX_MOUSE_BUTTONS);
}

// Destructor
Input::~Input()
{
	RELEASE(keyboard);
}

// Called before render is available
bool Input::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
bool Input::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	//in case of resizable window
	//mouse_x /= SCREEN_SIZE;
	//mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for (int i = 0; i < 5; ++i)
	{
		if (buttons & SDL_BUTTON(i))
		{
			if (mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if (mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	SDL_Event e;
	std::string filepath;
	while (SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);

		switch (e.type)
		{
		case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {
				isLeftButtonDown = true;
			}
			if (GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN) {
				isRightButtonDown = true;
			}
			if (GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_DOWN) {
				isMiddleButtonDown = true;
			}
			NotifyMouseClick(mouse_x, mouse_y);
			
			break;

		case SDL_MOUSEBUTTONUP:
			if (GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP) {
				isLeftButtonDown = false;
			}
			if (GetMouseButton(SDL_BUTTON_RIGHT) == KEY_UP) {
				isRightButtonDown = false;
			}
			if (GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_UP) {
				isMiddleButtonDown = false;
			}
			
			break;

		case SDL_MOUSEMOTION:
			//divide by window_size in case window resizable
			mouse_x = e.motion.x;
			mouse_y = e.motion.y;

			mouse_x_motion = e.motion.xrel;
			mouse_y_motion = e.motion.yrel;

			if (isRightButtonDown || isLeftButtonDown || isMiddleButtonDown) {
				NotifyMouseDrag(mouse_x, mouse_y);
			}
			break;

		case SDL_QUIT:
			quit = true;
			break;

		case SDL_DROPFILE:

			filepath = e.drop.file;

			// Check if the dropped file has the .fbx extension
			if (filepath.substr(filepath.find_last_of(".") + 1) == "fbx") {
				
				LOG("fbx detected, loading...");
				app->render->AddGameObject(filepath, "NewGameObject");
			}
			else {
				LOG("couldn't load fbx file. Make sure that it is a fbx file and not another.");
			}

		case SDL_WINDOWEVENT:
			switch (e.window.event)
			{
				//case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				windowEvents[WE_HIDE] = true;
				break;

				//case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				windowEvents[WE_SHOW] = true;
				break;
			}
		}
	}

	// Update the last mouse position at the end of each frame
	lastMouseX = mouse_x;
	lastMouseY = mouse_y;

	if (quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return false;

	return true;
}

//observer
void Input::NotifyMouseClick(int x, int y) {

	// Handle left mouse click
	if (GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {
		for (auto* observer : observers) {
			observer->OnLeftMouseClick(x, y);
		}
	}

	// Handle right mouse click
	if (GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN) {
		for (auto* observer : observers) {
			observer->OnRightMouseClick(x, y);
		}
	}

	// Handle middle mouse click (mouse wheel button)
	if (GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_DOWN) {
		for (auto* observer : observers) {
			observer->OnMiddleMouseClick(x, y);
		}
	}
}

void Input::NotifyMouseDrag(int x, int y) {
	// Handle right mouse button hold for dragging
	if (isRightButtonDown) {
		// Calculate the deltas
		int dx = mouse_x - lastMouseX;
		int dy = mouse_y - lastMouseY;
		for (auto* observer : observers) {
			// Cast the observer to the Camera type or use a dynamic_cast if needed
			Camera* cameraObserver = dynamic_cast<Camera*>(observer);
			if (cameraObserver) {
				cameraObserver->OnMouseRightDrag(dx, dy);
			}
		}
	}
}

void Input::RegisterObserver(IInputObserver* observer) {
	observers.push_back(observer);
}

void Input::UnregisterObserver(IInputObserver* observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

// Called before quitting
bool Input::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}