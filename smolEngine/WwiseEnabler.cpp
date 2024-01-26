#include "WwiseEnabler.h"
#include <Windows.h>

//memory management
#include "AK/SoundEngine/Common/AkMemoryMgr.h"
#include "AK/SoundEngine/Common/AkModule.h"


WwiseManager::WwiseManager() {

}


WwiseManager::~WwiseManager() {

	Shutdown();
}


bool WwiseManager::Initialize() {
	// MEMORY MANAGER
	AkMemSettings memSettings;
	AK::MemoryMgr::GetDefaultSettings(memSettings);

	if (AK::MemoryMgr::Init(&memSettings) == AK_Success)
	{
		SDL_Log("Created Memory manager");
	}
	else
	{
		SDL_Log("Could not create memory manager");
		return false;
	}




	return true;
}

bool WwiseManager::LoadBank(const std::string bankName) {
	

	return true;
}

// Shutdown Wwise sound engine
void WwiseManager::Shutdown() {

}


