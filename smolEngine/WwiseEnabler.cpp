#include "WwiseEnabler.h"
#include <Windows.h>

//memory management
#include "AK/SoundEngine/Common/AkMemoryMgr.h"
#include "AK/SoundEngine/Common/AkModule.h"

//streaming
#include "AK/SoundEngine/Common/IAkStreamMgr.h"
#include "AK/Tools/Common/AkPlatformFuncs.h"
#include "AK/SoundEngine/Common/AkTypes.h"
#include "Common/AkFilePackageLowLevelIODeferred.h"

//file packaging
#include "Common/AkFilePackage.h"
#include "Common/AkFilePackageLUT.h"

//communications
// Include for communication between Wwise and the game -- Not needed in the release version
#ifndef AK_OPTIMIZED
#include "AK/Comm/AkCommunication.h"
#endif  AK_OPTIMIZED

//music engine
#include "AK/MusicEngine/Common/AkMusicEngine.h"

//spatial audio
#include "AK/SpatialAudio/Common/AkSpatialAudio.h"
#include "Wwise_IDs.h"

#include "AK/SoundEngine/Common/AkModule.h"
#include "AK/SoundEngine/Common/AkSoundEngine.h" // Main sound engine
#include "AK/SoundEngine/Common/AkMemoryMgr.h"    // Memory manager
#include "AK/SoundEngine/Common/AkStreamMgrModule.h"    // Streaming manager
#include "AK/SoundEngine/Common/IAkStreamMgr.h"   // Streaming manager interface

#define BANKNAME_INIT L"Init.bnk"
#define BANKNAME_MANTELENGINE L"Background_music.bnk"


CAkFilePackageLowLevelIODeferred g_lowLevelIO;

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

	// STREAM MANAGER
	AkStreamMgrSettings stmSettings;
	AK::StreamMgr::GetDefaultSettings(stmSettings);

	if (AK::StreamMgr::Create(stmSettings))
	{
		SDL_Log("Streaming Manager created");
	}
	else
	{
		SDL_Log("Could not create the Streaming Manager");
		return false;
	}

	// STREAM DEVICE
	AkDeviceSettings deviceSettings;
	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

	if (g_lowLevelIO.Init(deviceSettings) == AK_Success)
	{
		SDL_Log("Created stream device and Low-Level I/O System");
	}
	else
	{
		SDL_Log("Could not create the streaming device and Low-Level I/O system");
		return false;
	}

	//sound engine
	AkInitSettings initSettings;
	AkPlatformInitSettings platformInitSettings;
	AK::SoundEngine::GetDefaultInitSettings(initSettings);
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

	if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) == AK_Success)
	{
		SDL_Log("Sound Engine Initialized");
	}
	else
	{
		SDL_Log("Could not initialize Sound Engine");
		return false;
	}


	//music engine
	AkMusicSettings musicInit;
	AK::MusicEngine::GetDefaultInitSettings(musicInit);

	if (AK::MusicEngine::Init(&musicInit) == AK_Success)
	{
		SDL_Log("Succes on initialize the Music Engine.");
	}
	else
	{
		SDL_Log("Could not initialize the Music Engine");
		return false;
	}

	g_lowLevelIO.SetBasePath(AKTEXT("smolEngine\\smolEditor\\Assets\\SoundBanks"));
	AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(us)"));

	//bank init
	AkBankID bankID;
	if (AK::SoundEngine::LoadBank(BANKNAME_INIT, bankID) == AK_Success)
	{
		SDL_Log("Init bank loaded");
	}
	else
	{
		SDL_Log("Could not load init bank");
		return false;
	}

	if (AK::SoundEngine::LoadBank(BANKNAME_MANTELENGINE, bankID) == AK_Success)
	{
		SDL_Log("MantelEngine bank loaded");
	}
	else
	{
		SDL_Log("Could not load MantelEngine bank");
		return false;
	}

	//communications
#ifndef AK_OPTIMIZED
	// Initialize communications (not in release build!)

	AkCommSettings commSettings;
	AK::Comm::GetDefaultInitSettings(commSettings);
	if (AK::Comm::Init(commSettings) == AK_Success)
	{
		SDL_Log("Succes on initialize communication.");
	}
	else
	{
		SDL_Log("Could not initialize communication");
		return false;
	}
#endif // AK_OPTIMIZED


	//spatial audio
	AkSpatialAudioInitSettings settings; // The constructor fills AkSpatialAudioInitSettings with the recommended default settings. 

	if (AK::SpatialAudio::Init(settings) == AK_Success)
	{
		SDL_Log("Succes on initialize the Spatial Audio");
	}
	else
	{
		SDL_Log("Could not initialize the Spatial Audio.");
		return false;
	}


	return true;
}

bool WwiseManager::LoadBank(const std::string bankName) {
	AkBankID bankID;
	AKRESULT result = AK::SoundEngine::LoadBank(bankName.c_str(), bankID);

	if (result != AK_Success) {

		SDL_Log("Failed to load bank %s, error: %d", bankName, result);
	}

	return result == AK_Success;
}

// Shutdown Wwise sound engine
void WwiseManager::Shutdown() {
	AK::SoundEngine::Term();
	AK::IAkStreamMgr::Get()->Destroy();
	AK::MemoryMgr::Term();
}
