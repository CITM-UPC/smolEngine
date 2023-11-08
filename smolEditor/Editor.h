#pragma once

#include "../smolEngine/Module.h"
#include "../smolEngine/Defs.h"
#include "Panel.h"
#include "AboutPanel.h"

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
	bool OnRenderUI();

	// Called before quitting
	bool CleanUp();

private:

	std::unique_ptr<Panel> about;

	std::list<Panel*> panels;
};
