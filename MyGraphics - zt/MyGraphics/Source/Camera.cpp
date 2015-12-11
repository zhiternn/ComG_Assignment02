//#include "Camera.h"
//#include "Application.h"
//#include "Mtx44.h"
//
//Camera::Camera()
//{
//	Reset();
//}
//
//Camera::~Camera()
//{
//}
//
//void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
//{
//	this->position = defaultPosition = pos;
//	this->target = defaultTarget = target;
//	Vector3 view = (target - position).Normalized();
//	Vector3 right = view.Cross(up);
//	right.y = 0;
//	right.Normalize();
//	this->up = defaultUp = right.Cross(view).Normalized();
//
//}
//
//void Camera::Update(double dt)
//{
//	static const float CAMERA_SPEED = 80.f;
//	Vector3 direction = (target - position).Normalized();
//
//	if (Application::IsKeyPressed('W'))
//	{
//		position += direction * (float)(50.f * dt);
//		target += direction * (float)(50.f * dt);
//	}
//	if (Application::IsKeyPressed('S'))
//	{
//		position -= direction * (float)(50.f * dt);
//		target -= direction * (float)(50.f * dt);
//	}
//	if (Application::IsKeyPressed(VK_LEFT))
//	{
//		float yaw = (float)(-CAMERA_SPEED * dt);
//		Mtx44 rotate;
//		rotate.SetToRotation(yaw, 0, 1, 0);
//		direction = rotate * direction;
//		target = direction;
//	}
//	if (Application::IsKeyPressed(VK_RIGHT))
//	{
//		float yaw = (float)(CAMERA_SPEED * dt);
//		Mtx44 rotate;
//		rotate.SetToRotation(yaw, 0, 1, 0);
//		direction = rotate * direction;
//		target = direction;
//	}
//	if (Application::IsKeyPressed(VK_UP))
//	{
//		float pitch = (float)(-CAMERA_SPEED * dt);
//		Vector3 view = (target - position).Normalized();
//		Vector3 right = view.Cross(up);
//		right.y = 0;
//		right.Normalize();
//		up = right.Cross(view).Normalized();
//		Mtx44 rotate;
//		rotate.SetToRotation(pitch, right.x, right.y, right.z);
//		position = rotate * position;
//	}
//	if (Application::IsKeyPressed(VK_DOWN))
//	{
//		float pitch = (float)(CAMERA_SPEED * dt);
//		Vector3 view = (target - position).Normalized();
//		Vector3 right = view.Cross(up);
//		right.y = 0;
//		right.Normalize();
//		up = right.Cross(view).Normalized();
//		Mtx44 rotate;
//		rotate.SetToRotation(pitch, right.x, right.y, right.z);
//		position = rotate * position;
//	}
//	if (Application::IsKeyPressed('Z'))
//	{
//		Vector3 direction = target - position;
//		if (direction.Length() > 5)
//		{
//			Vector3 view = (target - position).Normalized();
//			position += view * (float)(50.f * dt);
//		}
//	}
//	if (Application::IsKeyPressed('X'))
//	{
//		Vector3 view = (target - position).Normalized();
//		position -= view * (float)(50.f * dt);
//	}
//	if (Application::IsKeyPressed('R'))
//	{
//		Reset();
//	}
//	//std::cout << (target - position).Length() << std::endl;
//}
//
//void Camera::Reset()
//{
//	position = defaultPosition;
//	target = defaultTarget;
//	up = defaultUp;
//}

#include "Camera.h"
#include "Application.h"

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
		Vector3 direction2(direction);
		direction2.y += 1;
		position += direction2.Cross(direction) * (float)(30.f * dt);
		target += direction2.Cross(direction) * (float)(30.f * dt);
	}
	if (Application::IsKeyPressed(0x53)){ // S
		Vector3 direction = (target - position).Normalized();
		direction.y = 0;
		position -= direction * (float)(30.f * dt);
		target -= direction * (float)(30.f * dt);
	}
	if (Application::IsKeyPressed(0x44)){ // D
		Vector3 direction = (target - position).Normalized();
		Vector3 direction2(direction);
		direction2.y += 1;
		position += direction.Cross(direction2) * (float)(30.f * dt);
		target += direction.Cross(direction2) * (float)(30.f * dt);
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
		//Vector3 view = (target - position).Normalized();
		//Vector3 right = view.Cross(up);
		//right.y = 0;
		//right.Normalize();
		//up = right.Cross(view).Normalized();
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
		//Vector3 view = (target - position).Normalized();
		//Vector3 right = view.Cross(up);
		//right.y = 0;
		//right.Normalize();
		//up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed(VK_RIGHT)){
		theta += (float)(100 * dt);
		target.Set(camX(phi, theta) + position.x, camY(phi, theta) + position.y, camZ(phi, theta) + position.z);
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
