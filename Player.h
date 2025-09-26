#pragma once
#include "DxLib.h"
#include "UI.h"
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
	int modelHandle;	// プレイヤーモデル
	VECTOR position;	// プレイヤーの位置
	VECTOR direction;	// プレイヤーの向き
	float moveSpeed;	// プレイヤーの移動速度を格納
	int changeSpeedCount;	// 移動速度の変更回数を格納するカウンタ
	float jumpPower = 0;	// ジャンプ力

};
#endif