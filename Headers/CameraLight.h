#pragma once
#include "DxLib.h"
#include "Player.h"

class CameraLight {
public:
	/// <summary> コンストラクタ</summary>
	CameraLight() :cameraPos(START_CAMERA_POS), cameraLookPos(START_CAMERA_LOOKPOS) {}

	/// <summary> カメラの初期設定メソッド </summary>
	void SetUp();

	/// <summary> カメラの移動処理 </summary>
	void CameraMove(const Player& _player);

	/// <summary> カメラのリセット処理</summary>
	void Initialization();
private:
	VECTOR					cameraPos;				// カメラの座標
	VECTOR					cameraLookPos;			// カメラの注視点
	static constexpr int	CAMERA_MOVE_LIMIT = 4;	// プレイヤーの加速カウントが指定の値を超えたらプレイヤーを追従しないようにする
	static constexpr VECTOR START_CAMERA_POS = { 350, 330, -600 };	// カメラの初期座標
	static constexpr VECTOR START_CAMERA_LOOKPOS = { 350, 320, 0 };	// カメラの初期注視点
};


