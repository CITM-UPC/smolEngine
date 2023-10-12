#pragma once

#include <chrono>

#include "types.h"
#include "Camera.h"

class smolEngine
{
public:
	Camera camera;

	smolEngine();
	void step(std::chrono::duration<double> dt);
	void render();
};

