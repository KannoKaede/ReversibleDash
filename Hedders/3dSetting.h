#pragma once
#include "DxLib.h"
#include "Player.h"

class Camera {
public:
	const VECTOR START_CAMERA_POS = VGet(350, 340, -600);	// カメラの初期座標
	const VECTOR START_CAMERA_LOOK = VGet(350, 340, 0);	// カメラの初期注視点

	/// <summary> カメラの初期化コンストラクタ</summary>
	/// <param name="pos"> カメラの座標 </param>
	/// <param name="look"> 注視点 </param>
	Camera() :cameraPos(START_CAMERA_POS), lookPos(START_CAMERA_LOOK) {}

	/// <summary> カメラの初期設定メソッド </summary>
	void SetUp();

	/// <summary> カメラの移動メソッド </summary>
	/// <param name="moveAmount"> 移動量 </param>
	void Move(Player player);

	/// <summary> カメラのリセットメソッド</summary>
	void Initialization();
private:
	VECTOR cameraPos;	// カメラの座標
	VECTOR lookPos;	// カメラの注視点
};

class Light {
public:
	const VECTOR START_LIGHT_POS = VGet(60, 0, -50);	// ライトの初期座標

	/// <summary> ライトの初期化コンストラクタ </summary>
	/// <param name="pos"> ライトの座標 </param>
	Light() :lightPos(START_LIGHT_POS) {}

	/// <summary> ライトの初期設定メソッド </summary>
	void SetUp();

private:
	VECTOR lightPos;	// ライトの座標
};


