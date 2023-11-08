#pragma once

#include "Module.h"
#include "Imgui.h"

class ImguiEnabler : public Module
{
public:

	ImguiEnabler(bool startEnabled);

	// Destructor
	virtual ~ImguiEnabler();

	// Called when adding the modules to the application (cannot use app->)
	bool Init();

	// Called before render is available
	bool Start();

	// Called before quitting
	bool CleanUp();

	void BeginUI();
	void EndUI();

private:

};
