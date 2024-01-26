#include "Audio.h"
#include "Application.h"

Audio::Audio(bool startEnabled) : Module(startEnabled)
{

	if (!wwiseManager.Initialize()) {
		SDL_Log("Failed to initialize Wwise");
	}

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
	//LOG("Init Audio");

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
	//LOG("Destroying Audio");
	wwiseManager.Shutdown();

	return true;
}

void Audio::PlayBackgroundMusic(const char* eventName) {
	AK::SoundEngine::PostEvent(eventName, AK_INVALID_GAME_OBJECT);
}
