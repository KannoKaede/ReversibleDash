#include "CameraLight.h"

void CameraLight::SetUp() {
	// カメラのクリップ距離を設定
	SetCameraNearFar(0, 100);
	// ライトを有効にして、光の角度を設定
	SetUseLighting(TRUE);
	SetLightDirection(VGet(0, -0.7f, 0.3f));
}

void CameraLight::CameraMove(Player& player) {
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraLookPos);	// カメラの位置と注視点を設定
	if (base.GetIsGameStop())return;	// ゲームが止まっているときは移動処理に進まない

	// 加速ポイントを四回踏むまでカメラを移動させる
	if (player.GetChangeSpeedCount() <= 4) {
		cameraPos.x += player.GetSpeed();
		cameraLookPos.x += player.GetSpeed();
	}
}
void CameraLight::Initialization() {
	// 位置と注視点を初期化
	cameraPos = START_CAMERA_POS;
	cameraLookPos.x = START_CAMERA_POS.x;
}
