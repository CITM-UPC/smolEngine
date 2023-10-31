#pragma once

#include "Module.h"

class ImguiEnabler : public Module
{
public:

	ImguiEnabler(bool startEnabled);

	// Destructor
	virtual ~ImguiEnabler();

	// Called before render is available
	bool Start();

	// Called before quitting
	bool CleanUp();

	void BeginUI();
	void EndUI();

private:
	

};
