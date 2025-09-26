#include "Player.h"
#include "DxLib.h"
#include "UI.h"
#include "InGame.h"
#include "Main.h"


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

void Player::Jump() {
	static int jumpHoldFrame = 0; 
	const int shortJumpFrame = 15;
	const int midJumpFrame = 30;

	if (position.y == 0 && jumpPower == 0) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			jumpPower = 3.5f;
			jumpHoldFrame = 0;
		}
	}

	if (jumpPower > 0 || position.y > 0) {
		if (jumpPower > 0 && CheckHitKey(KEY_INPUT_SPACE)) {
			jumpHoldFrame++;

			if (jumpHoldFrame == shortJumpFrame) {
				jumpPower += 2.0f;
			}
			else if (jumpHoldFrame == midJumpFrame) {
				jumpPower += 1.5f;
			}
		}

		position.y += jumpPower;
		jumpPower -= 0.2f;

		if (position.y < 0) {
			position.y = 0;
			jumpPower = 0;
			jumpHoldFrame = 0;
		}
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