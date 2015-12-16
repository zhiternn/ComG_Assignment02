#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Vector3 currentTargetPos;
	Vector3 currentPositionpos;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	float phi, theta;
	float distance;

	float camX(float x, float y);
	float camY(float x, float y);
	float camZ(float x, float y);

	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void Update(double dt);
	virtual void Update2(double dt);
};

#endif

/*
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

class Camera
{
public:
Vector3 position;
Vector3 target;
Vector3 up;

Camera();
~Camera();
void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
void Reset();
void Update(double dt);

float camX(float x, float y);
float camY(float x, float y);
float camZ(float x, float y);

float phi, theta, distance;
};

#endif
*/