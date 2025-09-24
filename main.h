#pragma once
#include  "Player.h"
// ゲームの制御に関する変数、関数をまとめたヘッダ
#ifndef INCLUDED_Main_h
#define INCLUDED_Main_h
/// <summary> ゲーム(exe)を終了するかのフラグ </summary>
extern bool isGameQuit;

extern int stageNumber;     // 現在のステージ番号
const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
extern int screenWidth;    // 画面の幅
extern int screenHeight;    // 画面の高さ

class Camera {
public:
	Camera(VECTOR startPos, VECTOR startTarget) {
		position = startPos;
		target = startTarget;
		SetCameraNearFar(0.1f, 999);
		SetCameraPositionAndTarget_UpVecY(position, target);
	}
	void SetPosition(VECTOR pos, VECTOR target) { SetCameraPositionAndTarget_UpVecY(pos, target); }
	VECTOR GetPosition() { return position; }
	VECTOR GetTarget() { return target; }
	void Move(float playerPos) {
		position.x = playerPos + 60;
		target.x = playerPos + 60;
	}
private:
	VECTOR position;
	VECTOR target;
};

class Light {
public:
	Light(VECTOR startPos) {
		position = startPos;
		SetUseLighting(TRUE);
		SetLightPosition(position);
		SetLightDirection(VGet(0.0f, 0.0f, 1.0f));  // 実際に適用
	}
	void SetPosition(VECTOR pos) {
		SetLightPosition(pos);
	}
	VECTOR GetPosition() { return position; }
	void Move(float speed) { position.x = speed + 60; }
private:
	VECTOR position;
};
#endif

// 明日
// フェードのリファクタリング
// 3D描画の下準備