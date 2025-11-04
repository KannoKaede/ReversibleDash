#include "3dSetting.h"



void Camera::SetUp() {
	SetCameraNearFar(0, 100);
}

void Camera::Move(Player player) {
	SetCameraPositionAndTarget_UpVecY(cameraPos, lookPos);	// カメラの位置と注視点を設定
	if (base.isGameStop)return;

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


void Light::SetUp() {
	// ライトを有効にして、光の角度を設定
	SetUseLighting(TRUE);
	SetLightDirection(VGet(0, -0.7f, 0.3f));
}

