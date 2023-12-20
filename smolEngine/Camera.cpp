#include "Application.h"
#include "Camera.h"

Camera::Camera(bool start_enabled) : Module(start_enabled)
{
	CalculateViewMatrix();

	X = vec3(0.6f, 0.0f, 0.7f);
	Y = vec3(0.35f, 0.8f, -0.3f);
	Z = vec3(-0.7f, 0.45f, 0.55f);

	Position = vec3(-100.0f, 50.0f, 70.0f);
	Reference = vec3(-120.0f, 50.0f, 8.0f);
}

Camera::~Camera()
{
	app->input->UnregisterObserver(this);
}

// -----------------------------------------------------------------
bool Camera::Start()
{
	LOG("Setting up the camera");
	app->input->RegisterObserver(this);

	zoomspeed = 0.5f;
	cameraspeed = 0.05f;

	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool Camera::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
bool Camera::Update()
{
	static float originalSpeed = cameraspeed; // Store the original speed

	vec3 newPos(0, 0, 0);

	// Check if SHIFT is pressed and adjust camera speed
	if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT && cameraspeed == originalSpeed) {
		cameraspeed *= 2; // Double the speed
	}
	else if (app->input->GetKey(SDL_SCANCODE_LSHIFT) != KEY_REPEAT && cameraspeed != originalSpeed) {
		cameraspeed = originalSpeed; // Reset to original speed
	}

	// Update the original speed if not holding SHIFT
	if (app->input->GetKey(SDL_SCANCODE_LSHIFT) != KEY_REPEAT) {
		float mouseWheel = app->input->GetMouseZ();
		originalSpeed = std::clamp(originalSpeed + 0.05f * mouseWheel, 0.01f, 2.0f);
	}

	// Calculate new position based on WASD and RF keys
	newPos.y += cameraspeed * (app->input->GetKey(SDL_SCANCODE_R) - app->input->GetKey(SDL_SCANCODE_F));
	newPos += (X * (app->input->GetKey(SDL_SCANCODE_D) - app->input->GetKey(SDL_SCANCODE_A)) +
		Z * (app->input->GetKey(SDL_SCANCODE_S) - app->input->GetKey(SDL_SCANCODE_W))) * cameraspeed;

	// Apply new position and zoom
	Position += newPos;
	if (app->input->GetMouseButton(SDL_BUTTON_RIGHT) != KEY_REPEAT) {
		Position -= Z * zoomspeed * app->input->GetMouseZ();
	}

	Reference += newPos;

	// Recalculate matrix -------------
	CalculateViewMatrix();

	return true;
}

void Camera::OnLeftMouseClick(int x, int y) {
}

void Camera::OnRightMouseClick(int x, int y) {
}

void Camera::OnMiddleMouseClick(int x, int y) {
	//pan camera
}

void Camera::OnMouseRightDrag(int dx, int dy) {
    // Rotation sensitivity
    float Sensitivity = 0.25f;

    // Apply rotation to camera based on mouse movement
    if (dx != 0) {
        float DeltaX = -(float)dx * Sensitivity;
        X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
        Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
        Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
    }

    if (dy != 0) {
        float DeltaY = -(float)dy * Sensitivity;
        Y = rotate(Y, DeltaY, X);
        Z = rotate(Z, DeltaY, X);

        if (Y.y < 0.0f) {
            Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
            Y = cross(Z, X);
        }

    }
}

// -----------------------------------------------------------------
void Camera::Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if (!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void Camera::LookAt(const vec3& Spot)
{
	Reference = Spot;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	CalculateViewMatrix();
}


// -----------------------------------------------------------------
void Camera::Move(const vec3& Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void Camera::CalculateViewMatrix()
{
	viewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(viewMatrix);
}

