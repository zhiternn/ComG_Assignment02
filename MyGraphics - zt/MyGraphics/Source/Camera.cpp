#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;

	currentTargetPos = pos;
	currentPositionpos = target;

	phi = 0.f;
	theta = -90.f;
	distance = -20.f; // it is set to negative to prevent the camPos to snap to opposite end. Since the position and target will "switch" places when Update2 is used
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************
************************/
void Camera::Update(double dt)
{
	if (Application::IsKeyPressed(0x57)){ // W
		Vector3 direction = (target - position).Normalized();
		direction.y = 0;
		position += direction * (float)(30.f * dt);
		target += direction * (float)(30.f * dt);
	}
	if (Application::IsKeyPressed(0x41)){ // A
		Vector3 direction = (target - position).Normalized();
		position += Vector3(0, 1, 0).Cross(direction) * (float)(30.f * dt);
		target += Vector3(0, 1, 0).Cross(direction) * (float)(30.f * dt);
	}
	if (Application::IsKeyPressed(0x53)){ // S
		Vector3 direction = (target - position).Normalized();
		direction.y = 0;
		position -= direction * (float)(30.f * dt);
		target -= direction * (float)(30.f * dt);
	}
	if (Application::IsKeyPressed(0x44)){ // D
		Vector3 direction = (target - position).Normalized();
		position += direction.Cross(Vector3(0, 1, 0)) * (float)(30.f * dt);
		target += direction.Cross(Vector3(0, 1, 0)) * (float)(30.f * dt);
	}
	if (Application::IsKeyPressed(0x5A)){ // Z
		position.y += (float)(20 * dt);
		target.y += (float)(20 * dt);
	}
	if (Application::IsKeyPressed(0x58)){ // X
		position.y -= (float)(20 * dt);
		target.y -= (float)(20 * dt);
	}

	if (Application::IsKeyPressed(VK_UP)){
		if (phi <= 60.0f){// prevents camera from ascending once it reached 90 degrees
			phi += (float)(100 * dt);
		}
		target.Set(camX(phi, theta) + position.x, camY(phi, theta) + position.y, camZ(phi, theta) + position.z);
	}
	if (Application::IsKeyPressed(VK_LEFT)){
		theta -= (float)(100 * dt);
		target.Set(camX(phi, theta) + position.x, camY(phi, theta) + position.y, camZ(phi, theta) + position.z);
	}
	if (Application::IsKeyPressed(VK_DOWN)){
		if (phi >= -60.0f){// prevents camera from descending once it reached -90 degrees
			phi -= (float)(50 * dt);
		}
		target.Set(camX(phi, theta) + position.x, camY(phi, theta) + position.y, camZ(phi, theta) + position.z);
	}
	if (Application::IsKeyPressed(VK_RIGHT)){
		theta += (float)(100 * dt);
		target.Set(camX(phi, theta) + position.x, camY(phi, theta) + position.y, camZ(phi, theta) + position.z);
	}
}

void Camera::Update2(double dt)
{
	if (Application::IsKeyPressed(0x5A)){ // Z
		if (distance < -3.f)
			distance += (float)(50 * dt);
		position.Set(camX(phi, theta)*distance + target.x, camY(phi, theta)*distance + target.y, camZ(phi, theta)*distance + target.z);
	}
	if (Application::IsKeyPressed(0x58)){ // X
		distance -= (float)(50 * dt);
		position.Set(camX(phi, theta)*distance + target.x, camY(phi, theta)*distance + target.y, camZ(phi, theta)*distance + target.z);
	}
	if (Application::IsKeyPressed(VK_UP)){
		if (phi >= -60.0f){// prevents camera from ascending once it reached 90 degrees
			phi -= (float)(100 * dt);
		}
		position.Set(camX(phi, theta)*distance + target.x, camY(phi, theta)*distance + target.y, camZ(phi, theta)*distance + target.z);
	}
	if (Application::IsKeyPressed(VK_LEFT)){
		theta += (float)(100 * dt);
		position.Set(camX(phi, theta)*distance + target.x, camY(phi, theta)*distance + target.y, camZ(phi, theta)*distance + target.z);
	}
	if (Application::IsKeyPressed(VK_DOWN)){
		if (phi <= 60.0f){// prevents camera from descending once it reached -90 degrees
			phi += (float)(50 * dt);
		}
		position.Set(camX(phi, theta)*distance + target.x, camY(phi, theta)*distance + target.y, camZ(phi, theta)*distance + target.z);
	}
	if (Application::IsKeyPressed(VK_RIGHT)){
		theta -= (float)(100 * dt);
		position.Set(camX(phi, theta)*distance + target.x, camY(phi, theta)*distance + target.y, camZ(phi, theta)*distance + target.z);
	}
}

float Camera::camX(float x, float y){
	return cos(Math::DegreeToRadian(x))*cos(Math::DegreeToRadian(y));
}
float Camera::camY(float x, float y){
	return sin(Math::DegreeToRadian(x));
}
float Camera::camZ(float x, float y){
	return cos(Math::DegreeToRadian(x))*sin(Math::DegreeToRadian(y));
}
