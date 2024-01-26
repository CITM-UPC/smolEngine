#pragma once
#include "Module.h"
#include "WwiseEnabler.h"

class Audio : public Module
{
public:


	Audio(bool startEnabled);

	// Destructor
	virtual ~Audio();

	// Called when adding the modules to the application (cannot use app->)
	bool Init();

	// Called before render is available
	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void PlayBackgroundMusic(const char* eventName);

	// Called before quitting
	bool CleanUp();
private:
	WwiseManager wwiseManager;


};

