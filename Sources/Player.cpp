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
	modelHandle[0] = MV1LoadModel("Resource/PlayerModels/Player_Run.mv1");
	animationIndex[0] = MV1AttachAnim(modelHandle[0], 1, -1);
	modelHandle[1] = MV1LoadModel("Resource/PlayerModels/Player_JumpUp.mv1");
	animationIndex[1] = MV1AttachAnim(modelHandle[1], 1, -1);
	modelHandle[2] = MV1LoadModel("Resource/PlayerModels/Player_JumpDown.mv1");
	animationIndex[2] = MV1AttachAnim(modelHandle[2], 1, -1);

	MV1SetPosition(modelHandle[modelIndex], position);
	MV1SetRotationXYZ(modelHandle[modelIndex], direction);
}
void Player::Move() {
	if (isGameStop)return;
	if (isGround) {
		modelIndex = 0;
		PlayAnimation(modelHandle[modelIndex], animationIndex[modelIndex], true);
	}
	MV1SetRotationXYZ(modelHandle[modelIndex], isGravityBottom ? VGet(0, -90 * DX_PI_F / 180, 0) : VGet(180 * DX_PI_F / 180, 90 * DX_PI_F / 180, 0));
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
bool isGround;	// 現在ジャンプ中か判定		地面に付いたらfalse
int pressedMomentTime;	// Spaceを押した瞬間の時間を取得
bool isFall;	// 落下中かの判定
bool isGravityBottom;
float groundPosY;
void Player::Jump() {
	if (isGameStop)return;

	// 入力制御
	if (CheckHitKeyDown(KEY_INPUT_SPACE) && isGround) {	// キーを押した最初の1フレームの処理
		// ジャンプ力を加えて地面との設置判定を無くす
		jumpPower = isGravityBottom ? JUMP_POWER : -JUMP_POWER;
		isGround = false;
		pressedMomentTime = GetNowCount();	// 長押し時間を判定するために押したタイミングを保存
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && !isGround && !isFall) {	// キーを押している間の処理
		// ジャンプ上昇アニメーションの再生
		modelIndex = 1;
		PlayAnimation(modelHandle[modelIndex], animationIndex[modelIndex], false);

		if (pressedMomentTime + JUMP_LOCK_TIME < GetNowCount()) {	// 一定時間キーを押し込んでいたら落下を開始する
			isFall = true;
			pressedMomentTime = 0;
			isGravityBottom = !isGravityBottom;	// 重力を反対側にする
		}
	}
	if (CheckHitKeyUp(KEY_INPUT_SPACE) && !isGround && !isFall) {	// キーを離したときの処理
		// まだ落下していなかったら落下を開始
		isFall = true;
		pressedMomentTime = 0;
	}

	if (!isGround) {
		if (isFall) {	// 落下処理
			jumpPower -= isGravityBottom ? GRAVITY : -GRAVITY;	// ジャンプパワーにグラビティを加算し続け加速しながら落下していく
			// 落下アニメーションを再生
			if (fabsf(BOTTOM_GROUND - position.y) < 100 || fabsf(TOP_GROUND - 70 - position.y) < 100) {		//リファクタリング
				modelIndex = 2;
				PlayAnimation(modelHandle[modelIndex], animationIndex[modelIndex], false);
			}
		}
		position.y += jumpPower;
	}
	else {
		// 地面に接地していたらプレイヤー座標を一度だけ地面に合わせる
			position.y = groundPosY;
			jumpPower = 0;
			isFall = false;
	}
}

void Player::Initialization() {
	position = START_PLAYER_POS;
	moveSpeed = FIRST_SPEED;
	jumpPower = 0;
	changeSpeedCount = 1;
	isGravityBottom = true;
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
