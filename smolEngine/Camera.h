#pragma once
#include "Module.h"
#include "Input.h"
#include "glmath.h"

class Camera : public Module, public IInputObserver
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

	void OnMiddleMouseClick(int x, int y) override;
	void OnLeftMouseClick(int x, int y) override;
	void OnRightMouseClick(int x, int y) override;
	void OnMouseRightDrag(int dx, int dy);
	
	//setters
	void SetProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
		projectionMatrix = perspective(fov, aspectRatio, nearPlane, farPlane);
	}
	

	//getters
	float* GetViewMatrixf() { return &viewMatrix; };

	const mat4x4& GetProjectionMatrix() const { return projectionMatrix; };

	const mat4x4& GetViewMatrix() const { return viewMatrix; };

private:

	void CalculateViewMatrix();

public:

	vec3 X, Y, Z, Position, Reference;

private:

	float cameraspeed, zoomspeed = 0.0f;
	mat4x4 viewMatrix, ViewMatrixInverse, projectionMatrix;
};
