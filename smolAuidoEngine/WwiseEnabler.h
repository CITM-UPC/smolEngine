#pragma once
#include "Wwise.h"
#include <string>

class WwiseManager {
public:
    WwiseManager();
    ~WwiseManager();

    // Initializes Wwise sound engine
    bool Initialize();

    // Shuts down Wwise sound engine
    void Shutdown();

    bool LoadBank(const std::string bankName);



private:

};
