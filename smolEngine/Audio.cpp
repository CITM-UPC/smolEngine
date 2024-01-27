#include "Audio.h"
#include "Application.h"


Audio::Audio(bool startEnabled) : Module(startEnabled)
{
	//uncomment
	//if (!wwiseManager.Initialize()) {
	//	SDL_Log("Failed to initialize Wwise");
	//}

}

// Destructor
Audio::~Audio()
{
}

bool Audio::Init()
{
	return true;
}

// Called before render is available
bool Audio::Start()
{
	//uncomment
	//PlayBackgroundMusic("Play_Song1");
	bool ret = true;

	return ret;
}

bool Audio::PreUpdate()
{
	return true;
}

bool Audio::Update(float dt)
{
	return true;
}

bool Audio::PostUpdate()
{
	return true;
}

// Called before quitting
bool Audio::CleanUp()
{
	//uncomment
	//wwiseManager.Shutdown();

	return true;
}

//void Audio::PlayBackgroundMusic(std::string eventName) {
//	//uncomment
//	//AK::SoundEngine::PostEvent(eventName.c_str(), AK_INVALID_GAME_OBJECT);
//}
