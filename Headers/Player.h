#pragma once
#include "DxLib.h"
#include "Main.h"

// モデルデータ、アニメーションデータをまとめたデータ
struct ModelData {
	int model;			// モデルデータ
	int anime;			// アニメーションデータ
};

// 座標、角度、大きさをまとめたデータ
struct Transform {
	VECTOR position;	// プレイヤーの位置
	VECTOR rotation;	// プレイヤーの向き
	VECTOR scale;		// 衝突判定時に使用するプレイヤーの大きさ
};

static constexpr float	BOTTOM_GROUND = 40.0f;										// 下側の地面の座標
static constexpr VECTOR START_PLAYER_POS = { 0, BOTTOM_GROUND, 250 };				// スタート時のプレイヤー座標
static constexpr VECTOR START_PLAYER_ROT = { 0, base.ChangeRadians(-90.0f), 0 };	// スタート時のプレイヤー角度
static constexpr VECTOR PLAYER_SCALE = { 30, 100, 0 };						// プレイヤーのサイズ（半径、高さ）
static constexpr float	FIRST_SPEED = 7.0f;											// スタート時の速度
static constexpr int	JUMP_LOCK_TIME = 370;	// ジャンプ長押しが出来る時間

class Player {
public:
	/// <summary> コンストラクタ </summary>
	Player(VECTOR _position, VECTOR _rotation, VECTOR _scale, float _moveSpeed) :transform{ _position ,_rotation,_scale},moveSpeed(_moveSpeed){};

	/// <summary> プレイヤーの初期設定を行う </summary>
	void	SetUp();

	/// <summary> プレイヤーの移動処理を行う </summary>
	void	Move();

	/// <summary> プレイヤーの角度を滑らかに変更する </summary>
	void	Rotation();

	/// <summary> プレイヤーのジャンプ処理 </summary>
	void	Jump();

	/// <summary> アニメーションの再生を行う </summary>
	/// <param name="isLoop"> ループ再生するかのフラグ </param>
	void	PlayAnimation(ModelData _modelData, bool _isLoop);

	/// <summary> プレイヤーのリセット処理 </summary>
	void	Initialization();

	/// <summary> ジャンプディスタンスに値を代入可能か返す </summary>
	bool	CheckChangeJumpDis(float dis)	{ return jumpDis == 0 || dis < jumpDis; }

	/// <summary> モデルデータを返す </summary>
	int		GetModel()const					{ return modelData[modelIndex].model; }
	/// <summary> プレイヤーの座標を返す </summary>
	VECTOR	GetPosition()const				{ return transform.position; }
	/// <summary> プレイヤーの角度を返す </summary>
	VECTOR	GetRotation()const				{ return transform.rotation; }
	/// <summary> プレイヤーの高さ、半径情報を返す</summary>
	VECTOR	GetScale()const					{ return transform.scale; }
	/// <summary> プレイヤーの現在の速度を返す </summary>
	float	GetSpeed()const					{ return moveSpeed; }
	/// <summary> 何回加速したかを返す </summary>
	int		GetChangeSpeedCount()const		{ return changeSpeedCount; }
	/// <summary> 落下方向が下かを返す </summary>
	bool	GetIsGravityBottom()			{ return isGravityBottom; }
	/// <summary> オブジェクトとプレイヤーの距離を返す </summary>
	float	GetJumpDis()const				{ return jumpDis; }
	int		GetPressedJump()const			{ return pressedJump; }

	/// <summary> 座標を設定 </summary>
	void	SetPosition(VECTOR _position)	{ transform.position = _position; }
	/// <summary> 落下しているかを設定 </summary>
	void	SetIsFall(bool _isFall)			{ isFall = _isFall; }
	/// <summary> 地面についているかを設定 </summary>
	void	SetIsGround(bool _isGround)		{ isGround = _isGround; }
	/// <summary> プレイヤーが接地している地面の座標を設定 </summary>
	void	SetGroundPosY(float _position)	{ groundPosY = _position; }
	/// <summary> オブジェクトとプレイヤーの距離を設定 </summary>
	void	SetJumpDis(float _jumpDis)		{ jumpDis = _jumpDis; }
private:
	ModelData	modelData[3] = {};	// モデルデータ、アニメーションデータ
	Transform	transform;	// 座標、角度、大きさを設定

	// 移動で使用
	float		moveSpeed;					// プレイヤーの移動速度を格納
	int			changeSpeedCount = 1;		// 移動速度の変更回数を格納するカウンタ

	// ジャンプ、落下処理で使用

	int			pressedJump = 0;			// Spaceを押している時間を取得
	int			pressedMomentTime = 0;		// Spaceを押した瞬間の時間を取得
	float		jumpPower = 0;				// 実際のジャンプ力を入れる変数
	int			modelIndex = 0;				// 使用するモデルアニメーション
	bool		isFall = false;				// 現在落下中か
	bool		isGround = true;			// 現在ジャンプ中か判定
	bool		isJumping = false;			// ジャンプしているか判定
	bool		isGravityBottom = true;		// 上下どちらの地面にいるか判定
	float		groundPosY = 0;				// 接地した地面の座標Y
	float		jumpDis = 0;				// ジャンプ時の障害物までの距離を求める

	int playerCarModel = {};
	Transform playerCar = {};

	// アニメーション再生処理で使用
	float		animePlayTime = 0;			// アニメーションの再生するフレームを設定する
	int			animePastModel = 0;			// 前回再生していたアニメーションモデルを保存
	float		animePlayTotalTime = 0;		// 再生しているアニメーションのそう再生時間を保存

	static constexpr float	TOP_GROUND = 840.0f;	// 上側の地面の座標
	static constexpr float	GRAVITY = 0.7f;			// 重力
	static constexpr float	JUMP_POWER = 10;		// ジャンプ力

};