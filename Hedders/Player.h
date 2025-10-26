#pragma once
#include "DxLib.h"
#ifndef INCLUDED_Player_h
#define INCLUDED_Player_h

constexpr float PLAYER_RADIUS = 30.0f;	// プレイヤーの半径
constexpr float PLAYER_HEIGHT = 120.0f;	// プレイヤーの高さ
constexpr float BOTTOM_GROUND = 40;				// 下側の地面の座標
constexpr float TOP_GROUND = 680;				// 上側の地面の座標
constexpr float FIRST_SPEED = 4;				// スタート時の速度
constexpr float GRAVITY = 0.7f;			// 重力
constexpr int JUMP_LOCK_TIME = 300;				// ジャンプ長押しが出来る時間
constexpr float JUMP_POWER = 10.0f;				// ジャンプ力

const VECTOR START_PLAYER_POS = VGet(0, BOTTOM_GROUND, 0);
class Player {
public:

	Player(VECTOR startPos, VECTOR startDirection, float startSpeed);

	/// <summary> プレイヤーの初期設定メソッド </summary>
	void SetUp();

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
	int GetModelHandle()const;

	/// <summary> positionを返すメソッド </summary>
	/// <returns> position </returns>
	VECTOR GetPosition()const;

	/// <summary> positionをセットするメソッド </summary>
	/// <param name="pos"> セットする座標 </param>
	void SetPosition(VECTOR pos);

	VECTOR GetDirection()const;
	void SetDirection(VECTOR dir);

	/// <summary> moveSpeedを返すメソッド </summary>
	/// <returns> moveSpeed </returns>
	float GetSpeed()const;

	/// <summary> changeSpeedCountを返すメソッド </summary>
	/// <returns> changeSpeedCount </returns>
	int GetChangeSpeedCount()const;

	void PlayAnimation(int model, int anime, bool isLoop);
private:
	struct ModelData {
		int modelHandle;
		int animeHandle;
	};
	ModelData playerData[3];	// プレイヤーのモデルデータを格納する構造体
	VECTOR position;	// プレイヤーの位置
	VECTOR direction;	// プレイヤーの向き
	float moveSpeed;	// プレイヤーの移動速度を格納
	int changeSpeedCount;	// 移動速度の変更回数を格納するカウンタ
};

extern int modelIndex;
extern float jumpPower;	// 実際のジャンプ力を入れる変数
extern bool isFall;
extern bool isGround;	// 現在ジャンプ中か判定
extern bool isBottomGround;	// 上下どちらに居るか判定
#endif