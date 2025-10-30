#include "3dSetting.h"

Camera::Camera(VECTOR pos, VECTOR look) {
	cameraPos = pos;
	lookPos = look;
}

void Camera::SetUp() {
	SetCameraNearFar(0, 1000);
}

void Camera::Move(float moveAmount) {
	cameraPos.x += moveAmount;
	lookPos.x += moveAmount;
}
void Camera::Initialization() {
	cameraPos = START_CAMERA_POS;
	lookPos.x = START_CAMERA_POS.x;
}

VECTOR Camera::GetCameraPos() {
	return cameraPos;
}

VECTOR Camera::GetLookPos() {
	return lookPos;
}

Light::Light(VECTOR pos) {
	lightPos = pos;
}

void Light::SetUp() {
	SetUseLighting(TRUE);
	SetLightDirection(VGet(0, -0.7f, 0.3f));
}

void Light::Move(float moveAmount) {
	lightPos.x += moveAmount;
}

void Light::Initialization() {
	lightPos = START_LIGHT_POS;
}

VECTOR Light::GetLightPos() {
	return lightPos;
}