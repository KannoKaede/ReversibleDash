#include "3dSetting.h"

Camera::Camera(VECTOR pos, VECTOR look) {
	cameraPos = pos;
	lookPos = look;
}

void Camera::SetUp() {
	SetCameraNearFar(0, 100);
}

void Camera::Move(Player player) {
	SetCameraPositionAndTarget_UpVecY(cameraPos, lookPos);	// カメラの位置と注視点を設定
	if (isGameStop)return;

	// 加速ポイントを四回踏むまでカメラを移動させる
	if (player.GetChangeSpeedCount() <= 4) {
		cameraPos.x += player.GetSpeed();
		lookPos.x += player.GetSpeed();
	}
}
void Camera::Initialization() {
	// 位置と注視点を初期化
	cameraPos = START_CAMERA_POS;
	lookPos.x = START_CAMERA_POS.x;
}

Light::Light(VECTOR pos) {
	lightPos = pos;
}

void Light::SetUp() {
	// ライトを有効にして、光の角度を設定
	SetUseLighting(TRUE);
	SetLightDirection(VGet(0, -0.7f, 0.3f));
}

