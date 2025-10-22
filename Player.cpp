#include "Player.h"
#include "InGame.h"
#include "Input.h"
#include "main.h"
#include"Score.h"

int modelIndex = 0;

Player::Player(VECTOR startPos, VECTOR startDirection, float startSpeed) {
	position = startPos;
	direction = startDirection;
	moveSpeed = startSpeed;
	changeSpeedCount = 1;
}
void Player::SetUp() {
	modelHandle[0] = MV1LoadModel("Resource/Player_Run.mv1");
	animationIndex[0] = MV1AttachAnim(modelHandle[0], 1, -1);
	modelHandle[1] = MV1LoadModel("Resource/Player_JumpUp.mv1");
	animationIndex[1] = MV1AttachAnim(modelHandle[1], 1, -1);
	modelHandle[2] = MV1LoadModel("Resource/Player_JumpDown.mv1");
	animationIndex[2] = MV1AttachAnim(modelHandle[2], 1, -1);

	MV1SetPosition(modelHandle[modelIndex], position);
	MV1SetRotationXYZ(modelHandle[modelIndex], direction);
}
void Player::Move() {
	if (isGameStop)return;
	if (!isJumping) {
		modelIndex = 0;
		PlayAnimation(modelHandle[modelIndex],animationIndex[modelIndex],true);
	}
	MV1SetRotationXYZ(modelHandle[modelIndex], playerGround == BOTTOM ? VGet(0, -90 * DX_PI_F / 180, 0) : VGet(180 * DX_PI_F / 180, 90 * DX_PI_F / 180, 0));
	position.x += moveSpeed;
	MV1SetPosition(modelHandle[modelIndex], position);
	float speedUpPos = goalPosition[stageNumber] / 4;
}

void Player::ChangeSpeed() {
	float speedUpPos = goalPosition[stageNumber] / 4;
	if (position.x > speedUpPos * changeSpeedCount && changeSpeedCount <= 4) {
		moveSpeed = changeSpeedCount >= 3 ? FIRST_SPEED * (changeSpeedCount - 1) : FIRST_SPEED * (1 + 0.3f * changeSpeedCount);
		changeSpeedCount++;
	}
	else {
		return;
	}
}


float jumpPower;	// 実際のジャンプ力を入れる変数
bool isJumping;	// 現在ジャンプ中か判定		地面に付いたらfalse
int pressedMomentTime;	// Spaceを押した瞬間の時間を取得
bool isFall;	// 落下中かの判定
PLAYER_GROUND playerGround = BOTTOM;	// どちらの地面を走っているか
void Player::Jump() {
	if (isGameStop)return;
	if (isJumping) {
		position.y += jumpPower;
		jumpDistance = 0;
		if (!isFall) {
			modelIndex = 1;
			PlayAnimation(modelHandle[modelIndex], animationIndex[modelIndex], false);
		}
		else {
			if(fabsf(BOTTOM_GROUND-position.y)<100|| fabsf(TOP_GROUND - position.y) < 100)modelIndex = 2;	// リファクタリング　小ジャンプだとダウンアニメーションが不自然
			PlayAnimation(modelHandle[modelIndex], animationIndex[modelIndex], false);
			jumpPower += playerGround == BOTTOM ? -GRAVITY : GRAVITY;
		}
	}
	if (CheckHitKeyDown(KEY_INPUT_SPACE) && !isJumping) {	//ジャンプ中には入れない
		pressedMomentTime = GetNowCount();
		jumpPower = playerGround == BOTTOM ? JUMP_POWER : -JUMP_POWER;
		isJumping = true;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && isJumping) {
		if (pressedMomentTime + JUMP_LOCK_TIME <= GetNowCount() && !isFall) {
			isFall = true;
			playerGround = playerGround == BOTTOM ? TOP : BOTTOM;
		}
	}
	if (CheckHitKeyUp(KEY_INPUT_SPACE)) {	// ジャンプの値を初期化する
		pressedMomentTime = 0;
		isFall = true;
	}
	if (position.y < BOTTOM_GROUND || position.y>TOP_GROUND) {
		pressedMomentTime = 0;
		isJumping = false;
		isFall = false;
		jumpPower = 0;
		position.y = playerGround == BOTTOM ? BOTTOM_GROUND : 680;
	}
}

void Player::Initialization() {
	position = START_PLAYER_POS;
	moveSpeed = FIRST_SPEED;
	jumpPower = 0;
	changeSpeedCount = 1;
	playerGround = BOTTOM;
	MV1SetRotationXYZ(modelHandle[modelIndex], direction);
}

int Player::GetModelHandle() const {
	return modelHandle[modelIndex];
}

VECTOR Player::GetPosition()const {
	return position;
}

void Player::SetPosition(VECTOR pos) {
	position = pos;
}

VECTOR Player::GetDirection()const {
	return direction;
}

void Player::SetDirection(VECTOR dir) {
	direction = dir;
}

float Player::GetSpeed()const {
	return moveSpeed;
}

int Player::GetChangeSpeedCount()const {
	return changeSpeedCount;
}

float playTime;
int test;
float totalTime;
void Player::PlayAnimation(int model, int anime, bool isLoop) {
	if (test != model) {
		playTime = 0;
		test = model;
	}
	 totalTime = MV1GetAttachAnimTotalTime(modelHandle[modelIndex], animationIndex[modelIndex]);
	playTime += 0.7f;
	if (playTime >= totalTime)isLoop ? playTime = 0.0f : playTime = totalTime;
	MV1SetAttachAnimTime(modelHandle[modelIndex], animationIndex[modelIndex], playTime);
}
