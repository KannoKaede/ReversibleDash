#pragma once
#include"Main.h"
#include "Player.h"
#ifndef _3dSetting_h
#define _3dSetting_h

const VECTOR START_CAMERA_POS = VGet(350, 340, -600);	// カメラの初期座標
const VECTOR START_CAMERA_LOOK = VGet(350, 340, 0);	// カメラの初期注視点
class Camera {
public:
	/// <summary> カメラの初期化コンストラクタ</summary>
	/// <param name="pos"> カメラの座標 </param>
	/// <param name="look"> 注視点 </param>
	Camera(VECTOR pos, VECTOR look);

	/// <summary> カメラの初期設定メソッド </summary>
	void SetUp();

	/// <summary> カメラの移動メソッド </summary>
	/// <param name="moveAmount"> 移動量 </param>
	void Move(Player player);

	/// <summary> カメラのリセットメソッド</summary>
	void Initialization();

	/// <summary> cameraPosを返すメソッド </summary>
	/// <returns> cameraPos </returns>
	VECTOR GetCameraPos();

	/// <summary> lookPosを返すメソッド </summary>
	/// <returns> lookPos </returns>
	VECTOR GetLookPos();
private:
	VECTOR cameraPos;	// カメラの座標
	VECTOR lookPos;	// カメラの注視点
};

const VECTOR START_LIGHT_POS = VGet(60, 0, -50);	// ライトの初期座標
class Light {
public:
	/// <summary> ライトの初期化コンストラクタ </summary>
	/// <param name="pos"> ライトの座標 </param>
	Light(VECTOR pos);

	/// <summary> ライトの初期設定メソッド </summary>
	void SetUp();

	/// <summary> ライトのリセットメソッド </summary>
	void Initialization();

	/// <summary> lightPosを返すメソッド </summary>
	/// <returns> lightPos </returns>
	VECTOR GetLightPos();
private:
	VECTOR lightPos;	// ライトの座標
};

#endif // !3dSetting_h

