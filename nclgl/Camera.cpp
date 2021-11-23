#include "Camera.h"
#include "Window.h"
#include <algorithm>

#include "Markers.h"
#include "../Coursework/Renderer.h"

Camera::Camera(float pitch, float yaw, Vector3 position) 
{
	this->pitch = pitch;
	this->yaw = yaw;
	this->position = position;

	float by = 0.05f;
	Markers* markers = new Markers();
}

void Camera::UpdateCamera(bool autoCam, float dt) {
	pitch = std::min(pitch, 90.0f);
	pitch = std::max(pitch, -90.0f);

	if (yaw < 0) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}

	float speed = 120.0f * dt;
	float rotSpeed = 30.0f * dt;
	//pick way points


	Matrix4 rotation = Matrix4::Rotation(yaw, Vector3(0, 1, 0));

	Vector3 forward = rotation * Vector3(0, 0, -1);
	Vector3 right = rotation * Vector3(1, 0, 0);

	if(autoCam){
		std::vector<Vector3> waypoints = markers->GetMarkers();

		Vector3 travel = end - start;
		//Vector3 travel = waypoints[waypointNumber + 1] - waypoints[waypointNumber];

		if (cmpr(end.x, position.x, 1.0f)) {
			waypointNumber++;
			if(waypointNumber > waypoints.size()){ autoCam = false; }
			return; }
		
		travel.Normalise();
		position += travel * speed;
		yaw += 10*dt;
	}
	else
	{
		pitch -= (Window::GetMouse()->GetRelativePosition().y);
		yaw -= (Window::GetMouse()->GetRelativePosition().x);

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			position += forward * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			position -= forward * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
			position -= right * speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			position += right * speed;
		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
			position.y += speed;
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
			position.y -= speed;
		}
	}
}

Matrix4 Camera::BuildViewMatrix() {
	return Matrix4::Rotation(-pitch, Vector3(1, 0, 0)) * Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) * Matrix4::Translation(-position);
}
