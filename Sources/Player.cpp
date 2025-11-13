#include "Audio.h"
#include "Input.h"
#include "Player.h"
#include "Score.h"
#include "Stage.h"
#include "UI.h"

void Player::SetUp() {
	// モデルの読み込みとアニメーションの設定
	modelData[0].model = MV1LoadModel("Resource/PlayerModels/Player_Run.mv1");
	modelData[0].anime = MV1AttachAnim(modelData[0].model, 1, -1);
	modelData[1].model = MV1LoadModel("Resource/PlayerModels/Player_JumpUp.mv1");
	modelData[1].anime = MV1AttachAnim(modelData[1].model, 1, -1);
	modelData[2].model = MV1LoadModel("Resource/PlayerModels/Player_JumpDown.mv1");
	modelData[2].anime = MV1AttachAnim(modelData[2].model, 1, -1);

	// モデルの光の当たり方を設定：DXライブラリの初期設定のままだと暗すぎるので明るくする
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < MV1GetMaterialNum(modelData[i].model); j++)	// プレイヤーのモデル
		{
			MV1SetMaterialDifColor(modelData[i].model, j, GetColorF(0.3f, 0.3f, 0.3f, 1.0f));
			MV1SetMaterialAmbColor(modelData[i].model, j, GetColorF(1, 1, 1, 1));
			MV1SetMaterialSpcColor(modelData[i].model, j, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
			MV1SetMaterialEmiColor(modelData[i].model, j, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
			MV1SetMaterialSpcPower(modelData[i].model, j, 3.0f);
		}
	}
}

void Player::Move() {
	// モデルの座標更新と描画を先に行う
	MV1SetPosition(modelData[modelIndex].model, transform.position);
	Rotation();
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

void Player::Rotation() {
	// 回転し終わった時の目標を設定
	VECTOR targetRot = isGravityBottom ? VGet(0, base.ChangeRadians(-90.0f), 0) : VGet(base.ChangeRadians(180), base.ChangeRadians(90), 0);

	// 補間率を設定し適用する
	float lerpRate = 0.1f;
	transform.rotation.x += (targetRot.x - transform.rotation.x) * lerpRate;
	transform.rotation.y += (targetRot.y - transform.rotation.y) * lerpRate;
	MV1SetRotationXYZ(modelData[modelIndex].model, transform.rotation);
}

int pressedMomentTime;	// Spaceを押した瞬間の時間を取得
void Player::Jump() {
	if (base.GetIsGameStop())return;
	// 入力制御
	if (input.KeyDown(KEY_INPUT_SPACE) && isGround) {	// キーを押した最初の1フレームの処理
		// ジャンプ力を加えて地面との設置判定を無くす
		jumpPower = isGravityBottom ? JUMP_POWER : -JUMP_POWER;
		isGround = false;
		isJumping = true;
		scoreManager.AddScoreCalculate(jumpDis, moveSpeed);
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
		jumpDis = 0;
	}

	if (isGround) {
		// 地面に接地していたらプレイヤー座標を一度だけ地面に合わせる
		transform.position.y = groundPosY;
		jumpPower = 0;
		isFall = false;
		isJumping = false;
	}
	else if (!isJumping) {
		isFall = true;
	}
	if (isFall) {	// 落下処理
		jumpDis = 0;
		jumpPower -= isGravityBottom ? GRAVITY : -GRAVITY;	// ジャンプパワーにグラビティを加算し続け加速しながら落下していく
		// 落下アニメーションを再生
		if (fabsf(BOTTOM_GROUND - transform.position.y) < 100 || fabsf(TOP_GROUND - 70 - transform.position.y) < 100) {		//リファクタリング
			modelIndex = 2;
			PlayAnimation(modelData[modelIndex], false);
		}
		// 画面上部からはみ出たらゲームオーバー
		if (transform.position.y > 1500) {
			fadeManager.ChangeUIState(GAMEOVER, NOTFADE);
			audioManager.PlaySE(audioManager.JINGLE_GAMEOVER);
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
	modelIndex = 0;
	animePlayTime = 0;
	jumpDis = 0;
	MV1SetAttachAnimTime(modelData[modelIndex].model, modelData[modelIndex].anime, animePlayTime);
	MV1SetAttachAnimTime(modelData[modelIndex].model, modelData[modelIndex].anime, animePlayTime);
	MV1SetRotationXYZ(modelData[modelIndex].model, transform.rotation);
}

void Player::PlayAnimation(ModelData _modelData, bool _isLoop) {
	if (animePastModel != _modelData.model) {	// モデルが変わったら再生時間をリセット
		animePlayTime = 0;
		animePastModel = _modelData.model;
	}
	// アニメーションのそう再生時間を取得し、それを超えるまでアニメーションを進める
	animePlayTotalTime = MV1GetAttachAnimTotalTime(modelData[modelIndex].model, modelData[modelIndex].anime);
	animePlayTime += 0.7f;

	// ループする場合は最初に戻し、しない場合は最後のフレームで止める
	if (animePlayTime >= animePlayTotalTime)_isLoop ? animePlayTime = 0.0f : animePlayTime = animePlayTotalTime;
	MV1SetAttachAnimTime(modelData[modelIndex].model, modelData[modelIndex].anime, animePlayTime);
}