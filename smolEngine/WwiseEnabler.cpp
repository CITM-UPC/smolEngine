//uncomment
//#include "WwiseEnabler.h"
//
//
//CAkFilePackageLowLevelIODeferred g_lowLevelIO;
//
//WwiseManager::WwiseManager() {}
//
//WwiseManager::~WwiseManager() {
//    Shutdown();
//}
//
//bool WwiseManager::Initialize() {
//    if (!InitMemoryManager()) return false;
//    if (!InitStreamManager()) return false;
//    if (!InitStreamDevice()) return false;
//    if (!InitSoundEngine()) return false;
//    if (!InitMusicEngine()) return false;
//    if (!SetBasePathAndLanguage()) return false;
//    if (!LoadInitialBanks()) return false;
//#ifndef AK_OPTIMIZED
//    if (!InitCommunication()) return false;
//#endif
//    if (!InitSpatialAudio()) return false;
//
//    return true;
//}
//
//bool WwiseManager::InitMemoryManager() {
//    AkMemSettings memSettings;
//    AK::MemoryMgr::GetDefaultSettings(memSettings);
//    AKRESULT result = AK::MemoryMgr::Init(&memSettings);
//    return LogResult("Memory manager", result);
//}
//
//bool WwiseManager::InitStreamManager() {
//    AkStreamMgrSettings stmSettings;
//    AK::StreamMgr::GetDefaultSettings(stmSettings);
//    AKRESULT result = (AK::StreamMgr::Create(stmSettings) != nullptr) ? AK_Success : AK_Fail;
//    return LogResult("Streaming Manager", result);
//}
//
//bool WwiseManager::InitStreamDevice() {
//    AkDeviceSettings deviceSettings;
//    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);
//    AKRESULT result = g_lowLevelIO.Init(deviceSettings);
//    return LogResult("Stream device and Low-Level I/O System", result);
//}
//
//bool WwiseManager::InitSoundEngine() {
//    AkInitSettings initSettings;
//    AkPlatformInitSettings platformInitSettings;
//    AK::SoundEngine::GetDefaultInitSettings(initSettings);
//    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);
//    AKRESULT result = AK::SoundEngine::Init(&initSettings, &platformInitSettings);
//    return LogResult("Sound Engine", result);
//}
//
//bool WwiseManager::InitMusicEngine() {
//    AkMusicSettings musicInit;
//    AK::MusicEngine::GetDefaultInitSettings(musicInit);
//    AKRESULT result = AK::MusicEngine::Init(&musicInit);
//    return LogResult("Music Engine", result);
//}
//
//bool WwiseManager::SetBasePathAndLanguage() {
//    g_lowLevelIO.SetBasePath(AKTEXT("smolEngine\\smolEditor\\Assets\\SoundBanks"));
//    AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(us)"));
//    SDL_Log("Set base path and language");
//    return true;
//}
//
//bool WwiseManager::LoadInitialBanks() {
//    bool initBankLoaded = LoadBank(BANKNAME_INIT);
//    bool BackgrundBankLoaded = LoadBank(BANKNAME_BACKGROUND);
//    bool ObjectsBankLoaded = LoadBank(BANKNAME_OBJECTS);
//    return initBankLoaded && BackgrundBankLoaded && ObjectsBankLoaded;
//}
//
//#ifndef AK_OPTIMIZED
//bool WwiseManager::InitCommunication() {
//    AkCommSettings commSettings;
//    AK::Comm::GetDefaultInitSettings(commSettings);
//    AKRESULT result = AK::Comm::Init(commSettings);
//    return LogResult("Communication", result);
//}
//#endif
//
//bool WwiseManager::InitSpatialAudio() {
//    AkSpatialAudioInitSettings settings;
//    AKRESULT result = AK::SpatialAudio::Init(settings);
//    return LogResult("Spatial Audio", result);
//}
//
//bool WwiseManager::LoadBank(const std::wstring& bankName) {
//    AkBankID bankID;
//    AKRESULT result = AK::SoundEngine::LoadBank(bankName.c_str(), bankID);
//    std::string bankNameStr(bankName.begin(), bankName.end());
//    return LogResult("Load bank " + bankNameStr, result);
//}
//
//void WwiseManager::Shutdown() {
//    AK::SoundEngine::Term();
//    AK::IAkStreamMgr::Get()->Destroy();
//    AK::MemoryMgr::Term();
//#ifndef AK_OPTIMIZED
//    AK::Comm::Term();
//#endif
//    SDL_Log("Wwise shutdown complete.");
//}
//
//bool WwiseManager::LogResult(const std::string& operation, AKRESULT result) {
//    if (result == AK_Success) {
//        SDL_Log("%s successful.", operation.c_str());
//        return true;
//    }
//    else {
//        SDL_Log("%s failed, error: %d", operation.c_str(), result);
//        return false;
//    }
//}
