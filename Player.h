#pragma once
#include "DxLib.h"
#ifndef INCLUDED_Player_h
#define INCLUDED_Player_h

const float FIRST_SPEED = 1;
class Player {
public:

	Player(VECTOR startPos, VECTOR startDirection, float startSpeed);

	/// <summary> プレイヤーの初期設定メソッド </summary>
	void StartUp();

	/// <summary> プレイヤーの移動メソッド </summary>
	void Move();

	/// <summary> プレイヤーの移動速度変更メソッド </summary>
	void ChangeSpeed();

	/// <summary> プレイヤーのジャンプ処理メソッド </summary>
	void Jump();

	/// <summary> プレイヤーのリセットメソッド </summary>
	void Initialization();

	/// <summary> modelHandleを返すメソッド </summary>
	/// <returns> modelHandle </returns>
	int GetModelHandle();

	/// <summary> positionを返すメソッド </summary>
	/// <returns> position </returns>
	VECTOR GetPosition();

	/// <summary> positionをセットするメソッド </summary>
	/// <param name="pos"> セットする座標 </param>
	void SetPosition(VECTOR pos);

	/// <summary> moveSpeedを返すメソッド </summary>
	/// <returns> moveSpeed </returns>
	float GetSpeed();

	/// <summary> changeSpeedCountを返すメソッド </summary>
	/// <returns> changeSpeedCount </returns>
	int GetChangeSpeedCount();
private:
	int modelHandle = 0;	// プレイヤーモデル
	VECTOR position;	// プレイヤーの位置
	VECTOR direction;	// プレイヤーの向き
	float moveSpeed;	// プレイヤーの移動速度を格納
	int changeSpeedCount;	// 移動速度の変更回数を格納するカウンタ
};

extern float jumpPower;	// 実際のジャンプ力を入れる変数
extern bool isFall;
const float MIN_JUMP_POWER = 15;	// 最低ジャンプ力
const int  SECOND_JUMP_TIMING= 250;	// 二番目のジャンプ力に変更するタイミング
const int THIRD_JUMP_TIMING = 500;	// 三番目のジャンプ力に変更するタイミング
extern bool isJumping;	// 現在ジャンプ中か判定
const float GRAVITY = 0.7f;	// 重力
enum PLAYER_GROUND {
	TOP,
	BOTTOM
};
extern PLAYER_GROUND playerGround;	// 上下どちらにいるのか
#endif