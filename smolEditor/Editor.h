#pragma once

#include "../smolEngine/Module.h"

class Editor : public Module
{
public:

	Editor(bool startEnabled);

	// Destructor
	virtual ~Editor();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();
};
