#pragma once
#include "Matrix4.h"
#include "Vector3.h"

class Markers;

class Camera {
public:
	Camera(void) {
		yaw = 0.0f;
		pitch = 0.0f;
	};
	
	Camera(float pitch, float yaw, Vector3 position);

	~Camera(void) {};

	void UpdateCamera( bool autoCam, float dt = 1.0f );

	Matrix4 BuildViewMatrix();

	Vector3 GetPosition() const { return position; }
	void SetPosition(Vector3 val) { position = val; }

	float GetYaw() const { return yaw; }
	void SetYaw(float y) { yaw = y; }

	float GetPitch() const { return pitch; }
	void SetPitch(float p) { pitch = p; }

	bool cmpr(float a, float b, float c) { return fabs(a - b) < c; }

protected:
	float yaw;
	float pitch;
	Vector3 position;

	float by;

	Vector3 start = Vector3(7984.0f * 0.3f, 255.0f * 0.2f, 7984.0f * 0.65f);
	Vector3 end = Vector3(7984.0f * 0.6f, 255.0f * 1.5f, 7984.0f * 0.35f);

	Markers* markers;

	int waypointNumber;
};
