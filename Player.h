#pragma once
#include "DxLib.h"
#include "UI.h"
#ifndef INCLUDED_Player_h
#define INCLUDED_Player_h

const float FIRST_SPEED = 0.5f;
class Player {
public:

	int modelHandle;
	const float MODEL_SCALE = 0.2f;
	Player(VECTOR startPos, VECTOR startDirection, float startSpeed) {
		position = startPos;
		direction = startDirection;
		moveSpeed = startSpeed;
		changeSpeedCount = 1;

		modelHandle = MV1LoadModel("Resource/PlayerModel.mv1");
		MV1SetScale(modelHandle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
		MV1SetPosition(modelHandle, position);
		MV1SetRotationXYZ(modelHandle, direction);
	}
	void Move();
	void Jump();
	void ChangeSpeed();
	VECTOR GetPosition() { return position; }
	void SetPosition(VECTOR pos) { position = pos; }
	float GetSpeed() { return moveSpeed; }
	void SetSpeed(float speed) { moveSpeed = speed; }
	int GetChangeSpeedCount() { return changeSpeedCount; }
	void SetChangeSpeedCount(int count) { changeSpeedCount = count; }
private:
	VECTOR position;	// プレイヤーの位置
	VECTOR direction;	// プレイヤーの向き
	float moveSpeed;	// プレイヤーの移動速度を格納
	int changeSpeedCount;	// 移動速度の変更回数を格納するカウンタ
	float jumpPower = 0;

};
#endif