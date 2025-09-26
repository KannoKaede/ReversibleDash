#include "Player.h"
#include "InGame.h"
#include "Input.h"


Player::Player(VECTOR startPos, VECTOR startDirection, float startSpeed) {
	position = startPos;
	direction = startDirection;
	moveSpeed = startSpeed;
	changeSpeedCount = 1;
}
void Player::StartUp() {
	modelHandle = MV1LoadModel("Resource/PlayerModel.mv1");
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, direction);
}
void Player::Move() {
	position.x += moveSpeed;
	MV1SetPosition(modelHandle, position);
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
bool isJumping;	// 現在ジャンプ中か判定		地面に付いたらtrue
int pressedMomentTime;	// Spaceを押した瞬間の時間を取得
bool isFall;	// 落下中かの判定
PLAYER_GROUND playerGround = BOTTOM;	// どちらの地面を走っているか
void Player::Jump() {
	if (CheckHitKeyDown(KEY_INPUT_SPACE) && !isJumping) {	//ジャンプ中には入れない
		pressedMomentTime = GetNowCount();
		jumpPower = playerGround == BOTTOM ? MIN_JUMP_POWER : -MIN_JUMP_POWER;
		isJumping = true;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && isJumping) {
		if (pressedMomentTime + SECOND_JUMP_TIMING <= GetNowCount()&&!isFall) {
			isFall = true;
			playerGround = playerGround == BOTTOM ? TOP : BOTTOM;
			MV1SetRotationXYZ(modelHandle, playerGround == BOTTOM ? VGet(0, -90 * DX_PI_F / 180, 0): VGet(180 * DX_PI_F / 180, 90 * DX_PI_F / 180, 0));
				
		}
	}
	if (CheckHitKeyUp(KEY_INPUT_SPACE)) {	// ジャンプの値を初期化する
		pressedMomentTime = 0;
		isFall = true;
	}
	if (isJumping) {
		position.y += jumpPower;
		if (isFall)
			jumpPower += playerGround == BOTTOM ? -GRAVITY : GRAVITY;
	}
	if (position.y < 0|| position.y>680) {
		pressedMomentTime = 0;
		isJumping = false;
		isFall = false;
		jumpPower = 0;
		position.y = playerGround == BOTTOM ? 0 : 680;
	}
}

void Player::Initialization() {
	position = VGet(0, 0, 0);
	moveSpeed = FIRST_SPEED;
	changeSpeedCount = 1;
}

int Player::GetModelHandle() {
	return modelHandle;
}

VECTOR Player::GetPosition() {
	return position;
}

void Player::SetPosition(VECTOR pos) {
	position = pos;
}

float Player::GetSpeed() {
	return moveSpeed;
}

int Player::GetChangeSpeedCount() {
	return changeSpeedCount;
}