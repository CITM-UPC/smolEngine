#include "Editor.h"
#include "../smolEngine/Defs.h"

Editor::Editor(bool startEnabled) : Module(startEnabled)
{
}

// Destructor
Editor::~Editor()
{}

// Called before the first frame
bool Editor::Start()
{
	//LOG("render start");

	return true;
}

// Called each loop iteration
bool Editor::PreUpdate()
{

	return true;
}

bool Editor::Update(float dt)
{
	return true;
}

bool Editor::PostUpdate()
{
	return true;
}

// Called before quitting
bool Editor::CleanUp()
{
	LOG("Destroying SDL render");

	return true;
}