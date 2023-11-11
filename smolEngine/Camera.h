#pragma once
#include "Module.h"
#include "glmath.h"

class Camera : public Module
{
public:
	Camera(bool start_enabled = true);
	~Camera();

	bool Start();
	bool Update();
	bool CleanUp();

	void Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference = false);
	void LookAt(const vec3& Spot);
	void Move(const vec3& Movement);
	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:

	vec3 X, Y, Z, Position, Reference;

private:

	float cameraspeed, zoomspeed = 0.0f;
	mat4x4 ViewMatrix, ViewMatrixInverse;
};
