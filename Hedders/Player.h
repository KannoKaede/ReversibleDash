#pragma once
#include "Main.h"

constexpr float BOTTOM_GROUND = 40.0f;	// 下側の地面の座標
constexpr float TOP_GROUND = 840.0f;	// 上側の地面の座標
constexpr float FIRST_SPEED = 10.0f;		// スタート時の速度
constexpr float GRAVITY = 0.7f;			// 重力
constexpr int JUMP_LOCK_TIME = 370;		// ジャンプ長押しが出来る時間
constexpr float JUMP_POWER = 10;		// ジャンプ力
const VECTOR START_PLAYER_POS = VGet(0, BOTTOM_GROUND, 250);
const VECTOR START_PLAYER_ROT = VGet(0, ChangeRadians(-90.0f), 0);
const VECTOR START_PLAYER_SCALE = VGet(30, 100, 0);
class Player {
public:
	struct ModelData {
		int model;
		int anime;
	};
	Player(VECTOR startPos, VECTOR startDirection, VECTOR startScale, float startSpeed);

	/// <summary> プレイヤーの初期設定メソッド </summary>
	void SetUp();

	/// <summary> プレイヤーの移動メソッド </summary>
	void Move();

	/// <summary> プレイヤーのジャンプ処理メソッド </summary>
	void Jump();

	/// <summary> プレイヤーのリセットメソッド </summary>
	void Initialization();

	/// <summary> modelHandleを返すメソッド </summary>
	/// <returns> modelHandle </returns>
	int GetModel()const;

	/// <summary> positionを返すメソッド </summary>
	/// <returns> position </returns>
	VECTOR GetPosition()const;

	/// <summary> positionをセットするメソッド </summary>
	/// <param name="pos"> セットする座標 </param>
	void SetPosition(VECTOR pos);

	/// <summary> rotationを返すメソッド </summary>
	/// <returns> rotation </returns>
	VECTOR GetRotation()const;

	/// <summary> scaleを返すメソッド </summary>
	/// <returns> scale </returns>
	VECTOR GetScale()const;

	/// <summary> moveSpeedを返すメソッド </summary>
	/// <returns> moveSpeed </returns>
	float GetSpeed()const;

	/// <summary> changeSpeedCountを返すメソッド </summary>
	/// <returns> changeSpeedCount </returns>
	int GetChangeSpeedCount()const;

	void PlayAnimation(ModelData player, bool isLoop);
private:
	ModelData modelData[3] = {};

	struct Transform {
		VECTOR position;	// プレイヤーの位置
		VECTOR rotation;	// プレイヤーの向き
		VECTOR scale;		// 衝突判定時に使用するプレイヤーの大きさ
	};
	Transform transform;

	float moveSpeed;	// プレイヤーの移動速度を格納
	int changeSpeedCount = 1;	// 移動速度の変更回数を格納するカウンタ
	float jumpPower = {};	// 実際のジャンプ力を入れる変数
	int modelIndex = {};		// 使用するモデルアニメーション
};
extern bool isFall;		// 現在落下中か
extern bool isGround;	// 現在ジャンプ中か判定
extern bool isGravityBottom;	// 上下どちらの地面にいるか判定
extern float groundPosY;	// 接地した地面の座標Y