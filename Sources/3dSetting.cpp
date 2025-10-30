#include "3dSetting.h"

Camera::Camera(VECTOR pos, VECTOR look) {
	cameraPos = pos;
	lookPos = look;
}

void Camera::SetUp() {
	SetCameraNearFar(0, 1000);
}

void Camera::Move(Player player) {
	SetCameraPositionAndTarget_UpVecY(cameraPos, lookPos);
	if (isGameStop)return;
	if (player.GetChangeSpeedCount() <= 4) {
		cameraPos.x += player.GetSpeed();
		lookPos.x += player.GetSpeed();
	}
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


void Light::Initialization() {
	lightPos = START_LIGHT_POS;
}

VECTOR Light::GetLightPos() {
	return lightPos;
}