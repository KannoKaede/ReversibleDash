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
	playerData[0].modelHandle = MV1LoadModel("Resource/PlayerModels/Player_Run.mv1");
	playerData[0].animeHandle = MV1AttachAnim(playerData[0].modelHandle, 1, -1);
	playerData[1].modelHandle = MV1LoadModel("Resource/PlayerModels/Player_JumpUp.mv1");
	playerData[1].animeHandle = MV1AttachAnim(playerData[1].modelHandle, 1, -1);
	playerData[2].modelHandle = MV1LoadModel("Resource/PlayerModels/Player_JumpDown.mv1");
	playerData[2].animeHandle = MV1AttachAnim(playerData[2].modelHandle, 1, -1);

	MV1SetPosition(playerData[modelIndex].modelHandle, position);
	MV1SetRotationXYZ(playerData[modelIndex].modelHandle, direction);
}

void Debug(VECTOR pos) {
	float height = isBottomGround ? PLAYER_HEIGHT : -PLAYER_HEIGHT;
	VECTOR topLeftFront = VGet(pos.x - PLAYER_RADIUS, pos.y + height, pos.z - PLAYER_RADIUS);
	VECTOR topRightFront = VGet(pos.x + PLAYER_RADIUS, pos.y + height, pos.z - PLAYER_RADIUS);
	VECTOR topLeftBack = VGet(pos.x - PLAYER_RADIUS, pos.y + height, pos.z + PLAYER_RADIUS);
	VECTOR topRightBack = VGet(pos.x + PLAYER_RADIUS, pos.y + height, pos.z + PLAYER_RADIUS);
	VECTOR bottomLeftFront = VGet(pos.x - PLAYER_RADIUS, pos.y, pos.z - PLAYER_RADIUS);
	VECTOR bottomRightFront = VGet(pos.x + PLAYER_RADIUS, pos.y, pos.z - PLAYER_RADIUS);
	VECTOR bottomLeftBack = VGet(pos.x - PLAYER_RADIUS, pos.y, pos.z + PLAYER_RADIUS);
	VECTOR bottomRightBack = VGet(pos.x + PLAYER_RADIUS, pos.y, pos.z + PLAYER_RADIUS);
	DrawLine3D(topLeftFront, topRightFront, GetColor(255, 0, 0));
	DrawLine3D(topRightFront, topRightBack, GetColor(255, 0, 0));
	DrawLine3D(topRightBack, topLeftBack, GetColor(255, 0, 0));
	DrawLine3D(topLeftBack, topLeftFront, GetColor(255, 0, 0));
	DrawLine3D(bottomLeftFront, bottomRightFront, GetColor(255, 0, 0));
	DrawLine3D(bottomRightFront, bottomRightBack, GetColor(255, 0, 0));
	DrawLine3D(bottomRightBack, bottomLeftBack, GetColor(255, 0, 0));
	DrawLine3D(bottomLeftBack, bottomLeftFront, GetColor(255, 0, 0));
	DrawLine3D(topLeftFront, bottomLeftFront, GetColor(255, 0, 0));
	DrawLine3D(topRightFront, bottomRightFront, GetColor(255, 0, 0));
	DrawLine3D(topLeftBack, bottomLeftBack, GetColor(255, 0, 0));
	DrawLine3D(topRightBack, bottomRightBack, GetColor(255, 0, 0));
}

void Player::Move() {

	Debug(position);
	if (isGameStop)return;
	if (isGround) {
		modelIndex = 0;
		PlayAnimation(playerData[modelIndex].modelHandle, playerData[modelIndex].animeHandle, true);
	}
	MV1SetRotationXYZ(playerData[modelIndex].modelHandle, isBottomGround ? VGet(0, -90 * DX_PI_F / 180, 0) : VGet(180 * DX_PI_F / 180, 90 * DX_PI_F / 180, 0));
	position.x += moveSpeed;
	MV1SetPosition(playerData[modelIndex].modelHandle, position);
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
bool isGround;	// 現在ジャンプ中か判定
int pressedMomentTime;	// Spaceを押した瞬間の時間を取得
bool isFall;	// 落下中かの判定
bool isBottomGround = true;	// 上下どちらに居るか判定
void Player::Jump() {
	if (isGameStop)return;
	if (CheckHitKeyDown(KEY_INPUT_SPACE) && isGround) {
		pressedMomentTime = GetNowCount();
		isGround = false;
		jumpPower = isBottomGround?JUMP_POWER:-JUMP_POWER;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && !isGround) {
		if (!isFall) {
			if (pressedMomentTime + JUMP_LOCK_TIME < GetNowCount()) {
				isFall = true;
				isBottomGround = !isBottomGround;
			}
			else {
				jumpPower = isBottomGround ? JUMP_POWER : -JUMP_POWER;
			}
		}
	}
	if (CheckHitKeyUp(KEY_INPUT_SPACE) && !isFall) {
		isFall = true;
	}
	if (position.y < BOTTOM_GROUND) {
		position.y = BOTTOM_GROUND;
		isGround = true;
	}
	if (position.y > TOP_GROUND) {
		position.y = TOP_GROUND;
		isGround = true;
	}
	if (isGround) {
		jumpPower = 0;
		isFall = false;
		pressedMomentTime = 0;
	}
	if (!isGround) {
		jumpPower -= isBottomGround ?GRAVITY:-GRAVITY;
	}
	position.y += jumpPower;
}

void Player::Initialization() {
	position = START_PLAYER_POS;
	moveSpeed = FIRST_SPEED;
	jumpPower = 0;
	changeSpeedCount = 1;
	isBottomGround = true;
	MV1SetRotationXYZ(playerData[modelIndex].modelHandle, direction);
}

int Player::GetModelHandle() const {
	return playerData[modelIndex].modelHandle;
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
	totalTime = MV1GetAttachAnimTotalTime(playerData[modelIndex].modelHandle, playerData[modelIndex].animeHandle);
	playTime += 0.7f;
	if (playTime >= totalTime)isLoop ? playTime = 0.0f : playTime = totalTime;
	MV1SetAttachAnimTime(playerData[modelIndex].modelHandle, playerData[modelIndex].animeHandle, playTime);
}
