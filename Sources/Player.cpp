#include "Input.h"
#include "Player.h"
#include "Score.h"
#include "Stage.h"

int modelIndex = 0;

Player::Player(VECTOR startPos, VECTOR startRot, VECTOR startScale, float startSpeed) {
	transform.position = startPos;
	transform.rotation = startRot;
	transform.scale = startScale;
	moveSpeed = startSpeed;
}
void Player::SetUp() {
	// モデルの読み込みとアニメーションの設定
	modelData[0].model = MV1LoadModel("Resource/PlayerModels/Player_Run.mv1");
	modelData[0].anime = MV1AttachAnim(modelData[0].model, 1, -1);
	modelData[1].model = MV1LoadModel("Resource/PlayerModels/Player_JumpUp.mv1");
	modelData[1].anime = MV1AttachAnim(modelData[1].model, 1, -1);
	modelData[2].model = MV1LoadModel("Resource/PlayerModels/Player_JumpDown.mv1");
	modelData[2].anime = MV1AttachAnim(modelData[2].model, 1, -1);
}
void Player::Move() {
	// モデルの座標更新と描画を先に行う
	MV1SetPosition(modelData[modelIndex].model, transform.position);
	MV1SetRotationXYZ(modelData[modelIndex].model, isGravityBottom ? VGet(0, base.ChangeRadians(-90.0f), 0) : VGet(base.ChangeRadians(180), base.ChangeRadians(90), 0));
	MV1DrawModel(modelData[modelIndex].model);
	if (base.GetIsGameStop())return;
	if (isGround) {	// 地面にいる場合は走るアニメーションを再生
		modelIndex = 0;
		PlayAnimation(modelData[modelIndex], true);
	}
	transform.position.x += moveSpeed;

	// 速度変更処理：ゴール地点の1/4ごとに速度を上げていく
	float speedUpPos = stageManager.GetGoalPosition(base.GetStageNumber()) / 4;
	if (transform.position.x > speedUpPos * changeSpeedCount && changeSpeedCount <= 4) {
		moveSpeed = changeSpeedCount >= 3 ? FIRST_SPEED * (changeSpeedCount - 1) : FIRST_SPEED * (1 + 0.3f * changeSpeedCount);
		changeSpeedCount++;
	}
}

float jumpPower;	// 実際のジャンプ力を入れる変数
bool isGround;	// 現在ジャンプ中か判定		地面に付いたらfalse
int pressedMomentTime;	// Spaceを押した瞬間の時間を取得
bool isFall;	// 落下中かの判定
bool isGravityBottom;
float groundPosY;
void Player::Jump() {
	if (base.GetIsGameStop())return;

	// 入力制御
	if (input.KeyDown(KEY_INPUT_SPACE) && isGround) {	// キーを押した最初の1フレームの処理
		printfDx("Jump!\n");
		// ジャンプ力を加えて地面との設置判定を無くす
		jumpPower = isGravityBottom ? JUMP_POWER : -JUMP_POWER;
		isGround = false;
		scoreManager.AddScoreCalculate(moveSpeed);
		pressedMomentTime = GetNowCount();	// 長押し時間を判定するために押したタイミングを保存
	}
	if (input.KeyPushing(KEY_INPUT_SPACE) && !isGround && !isFall) {	// キーを押している間の処理
		// ジャンプ上昇アニメーションの再生
		modelIndex = 1;
		PlayAnimation(modelData[modelIndex], false);
		if (pressedMomentTime + JUMP_LOCK_TIME < GetNowCount()) {	// 一定時間キーを押し込んでいたら落下を開始する
			isFall = true;
			pressedMomentTime = 0;
			isGravityBottom = !isGravityBottom;	// 重力を反対側にする
		}
	}
	if (input.KeyUp(KEY_INPUT_SPACE) && !isGround && !isFall) {	// キーを離したときの処理
		// まだ落下していなかったら落下を開始
		isFall = true;
		pressedMomentTime = 0;
	}

	if (isGround) {
		// 地面に接地していたらプレイヤー座標を一度だけ地面に合わせる
		transform.position.y = groundPosY;
		jumpPower = 0;
		isFall = false;
		return;	// 設置している場合は落下処理に入らない
	}
	if (isFall) {	// 落下処理
		jumpPower -= isGravityBottom ? GRAVITY : -GRAVITY;	// ジャンプパワーにグラビティを加算し続け加速しながら落下していく
		// 落下アニメーションを再生
		if (fabsf(BOTTOM_GROUND - transform.position.y) < 100 || fabsf(TOP_GROUND - 70 - transform.position.y) < 100) {		//リファクタリング
			modelIndex = 2;
			PlayAnimation(modelData[modelIndex], false);
		}
	}
	transform.position.y += jumpPower;
}

void Player::Initialization() {
	// 座標、速度、状態の初期化
	transform.position = START_PLAYER_POS;
	moveSpeed = FIRST_SPEED;
	jumpPower = 0;
	changeSpeedCount = 1;
	isGravityBottom = true;
	MV1SetRotationXYZ(modelData[modelIndex].model, transform.rotation);
}

int Player::GetModel() const {
	return modelData[modelIndex].model;
}

VECTOR Player::GetPosition()const {
	return transform.position;
}

void Player::SetPosition(VECTOR pos) {
	transform.position = pos;
}

VECTOR Player::GetRotation()const {
	return transform.rotation;
}

VECTOR Player::GetScale()const {
	return transform.scale;
}

float Player::GetSpeed()const {
	return moveSpeed;
}

int Player::GetChangeSpeedCount()const {
	return changeSpeedCount;
}

float playTime;
int previousModel;
float totalTime;
void Player::PlayAnimation(ModelData player, bool isLoop) {
	if (previousModel != player.model) {	// モデルが変わったら再生時間をリセット
		playTime = 0;
		previousModel = player.model;
	}
	// アニメーションのそう再生時間を取得し、それを超えるまでアニメーションを進める
	totalTime = MV1GetAttachAnimTotalTime(modelData[modelIndex].model, modelData[modelIndex].anime);
	playTime += 0.7f;

	// ループする場合は最初に戻し、しない場合は最後のフレームで止める
	if (playTime >= totalTime)isLoop ? playTime = 0.0f : playTime = totalTime;
	MV1SetAttachAnimTime(modelData[modelIndex].model, modelData[modelIndex].anime, playTime);
}