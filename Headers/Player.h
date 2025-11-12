#pragma once
#include "DxLib.h"
#include "Main.h"

constexpr float BOTTOM_GROUND = 40.0f;	// 下側の地面の座標
constexpr float TOP_GROUND = 840.0f;	// 上側の地面の座標
constexpr float FIRST_SPEED = 7.0f;		// スタート時の速度
constexpr float GRAVITY = 0.7f;			// 重力
constexpr int JUMP_LOCK_TIME = 370;		// ジャンプ長押しが出来る時間
constexpr float JUMP_POWER = 10;		// ジャンプ力
constexpr VECTOR START_PLAYER_POS = { 0, BOTTOM_GROUND, 250 };
const VECTOR START_PLAYER_ROT = { 0, base.ChangeRadians(-90.0f), 0 };
constexpr VECTOR START_PLAYER_SCALE = { 30, 100, 0 };

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

	/// <summary> プレイヤーの角度を滑らかに変更するメソッド </summary>
	void Rotation();

	/// <summary> プレイヤーのジャンプ処理メソッド </summary>
	void Jump();

	/// <summary> アニメーションの再生を行うメソッド </summary>
	/// <param name="player"> プレイヤーのモデルデータ、アニメーションデータ </param>
	/// <param name="isLoop"> ループ再生するかのフラグ </param>
	void PlayAnimation(ModelData player, bool isLoop);

	/// <summary> プレイヤーのリセットメソッド </summary>
	void Initialization();

	bool CheckChangeJumpDis(float dis) {
		return jumpDis == 0 || dis < jumpDis;
	}

	// private変数を読み取り専用で渡すメソッド群
	int GetModel()const { return modelData[modelIndex].model; }
	VECTOR GetPosition()const { return transform.position; }
	VECTOR GetRotation()const { return transform.rotation; }
	VECTOR GetScale()const { return transform.scale; }
	float GetSpeed()const { return moveSpeed; }
	int GetChangeSpeedCount()const { return changeSpeedCount; }
	bool GetIsGravityBottom() { return isGravityBottom; }
	float GetJumpDis() { return jumpDis; }

	// private変数に値を書き込むメソッド群
	void SetPosition(VECTOR pos) { transform.position = pos; }
	void SetIsFall(bool state) { isFall = state; }
	void SetIsGround(bool state) { isGround = state; }
	void SetGroundPosY(float pos) { groundPosY = pos; }
	void SetJumpDis(float distance) { jumpDis = distance; }
private:
	ModelData modelData[3] = {};

	struct Transform {
		VECTOR position;	// プレイヤーの位置
		VECTOR rotation;	// プレイヤーの向き
		VECTOR scale;		// 衝突判定時に使用するプレイヤーの大きさ
	};
	Transform transform;

	// 移動で使用
	float moveSpeed;	// プレイヤーの移動速度を格納
	int changeSpeedCount = 1;	// 移動速度の変更回数を格納するカウンタ

	// ジャンプ、落下処理で使用
	int pressedMomentTime;
	float jumpPower = {};	// 実際のジャンプ力を入れる変数
	int modelIndex = {};		// 使用するモデルアニメーション
	bool isFall;		// 現在落下中か
	bool isGround;	// 現在ジャンプ中か判定
	bool isJumping;	// ジャンプしているか判定
	bool isGravityBottom;	// 上下どちらの地面にいるか判定
	float groundPosY;	// 接地した地面の座標Y
	float jumpDis;	// ジャンプ時の障害物までの距離を求める

	// アニメーション再生処理で使用
	float animePlayTime;	// アニメーションの再生するフレームを設定する
	int animePastModel = {};	// 前回再生していたアニメーションモデルを保存
	float animePlayTotalTime = {};	// 再生しているアニメーションのそう再生時間を保存
};