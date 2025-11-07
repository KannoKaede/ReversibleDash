#pragma once
#include "DxLib.h"
#include "Player.h"

constexpr int CAMERA_MOVE_LIMIT = 4;	// プレイヤーの加速カウントが一定になったらカメラが追従しなくなる
class CameraLight {
public:
	/// <summary> コンストラクタ</summary>
	CameraLight() :cameraPos(START_CAMERA_POS), cameraLookPos(START_CAMERA_LOOKPOS) {}

	/// <summary> カメラの初期設定メソッド </summary>
	void SetUp();

	/// <summary> カメラの移動メソッド </summary>
	/// <param name="moveAmount"> 移動量 </param>
	void CameraMove(Player& player);

	/// <summary> カメラのリセットメソッド</summary>
	void Initialization();

	const VECTOR START_CAMERA_POS = VGet(350, 340, -600);	// カメラの初期座標
	const VECTOR START_CAMERA_LOOKPOS = VGet(350, 340, 0);	// カメラの初期注視点
private:
	VECTOR cameraPos;	// カメラの座標
	VECTOR cameraLookPos;	// カメラの注視点
};


