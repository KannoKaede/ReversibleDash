#include "Audio.h"
#include "Main.h"
#include "Stage.h"
#include "UI.h"

StageManager stageManager;

void StageManager::SetUp() {
	cityHandle = MV1LoadModel("Resource/Stages/city.mv1");
	carHandle[0] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_1.mv1");
	carHandle[1] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_2.mv1");
	carHandle[2] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_3.mv1");
	carHandle[3] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_4.mv1");
	carHandle[4] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_1.mv1");
	carHandle[5] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_2.mv1");
	carHandle[6] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_3.mv1");
	carHandle[7] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_4.mv1");

	cloudHandle[0] = MV1LoadModel("Resource/Stages/Clouds/Cloud_1.mv1");
	cloudHandle[1] = MV1LoadModel("Resource/Stages/Clouds/Cloud_2.mv1");
	cloudHandle[2] = MV1LoadModel("Resource/Stages/Clouds/Cloud_3.mv1");
	cloudHandle[3] = MV1LoadModel("Resource/Stages/Clouds/Cloud_4.mv1");
	cloudHandle[4] = MV1LoadModel("Resource/Stages/Clouds/Cloud_5.mv1");


	// コンストラクタでモデルを設定できないのでここでモデルを設定する
	for (int i = 1; i < MAX_STAGE_NUM; i++) {
		for (int j = 0; j < carArray[i].size(); j++) {
			carArray[i][j].SetCarHandle(carHandle[carArray[i][j].GetCarHandle()]);
		}
		for (int k = 0; k < cloudArray[i].size(); k++) {
			cloudArray[i][k].SetCloudHandle(cloudHandle[cloudArray[i][k].GetCloudHandle()]);
		}
	}

	// モデルの光の当たり方を設定：DXライブラリの初期設定のままだと暗すぎるので明るくする
	for (int i = 0; i < MV1GetMaterialNum(cityHandle); i++)	// ステージのモデル
	{
		MV1SetMaterialDifColor(cityHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
		MV1SetMaterialAmbColor(cityHandle, i, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
		MV1SetMaterialSpcColor(cityHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
		MV1SetMaterialEmiColor(cityHandle, i, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
		MV1SetMaterialSpcPower(cityHandle, i, 3.0f);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < MV1GetMaterialNum(carHandle[i]); j++) {
			MV1SetMaterialDifColor(carHandle[i], j, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
			MV1SetMaterialAmbColor(carHandle[i], j, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
			MV1SetMaterialSpcColor(carHandle[i], j, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
			MV1SetMaterialEmiColor(carHandle[i], j, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
			MV1SetMaterialSpcPower(carHandle[i], j, 3.0f);
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < MV1GetMaterialNum(cloudHandle[i]); j++) {
			MV1SetMaterialDifColor(cloudHandle[i], j, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
			MV1SetMaterialAmbColor(cloudHandle[i], j, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
			MV1SetMaterialSpcColor(cloudHandle[i], j, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
			MV1SetMaterialEmiColor(cloudHandle[i], j, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
			MV1SetMaterialSpcPower(cloudHandle[i], j, 3.0f);
		}
	}
}



void StageManager::Draw(Player& player) {
	bool test = false;
	// 背景ステージの描画と衝突判定の設定
	MV1DrawModel(cityHandle);
	if (IsCollision(player, VGet(12000, 0, 0), 40, 20000, false, false))test = true;	// リファクタリング：ステージを全部作り終わったら定数に変更
	// 車の描画
	if (!base.GetIsGameStop()) carMoveX += -7;	// 車を左に移動させていく
	for (int i = 0; i < carArray[base.GetStageNumber()].size(); i++) {
		Car car = carArray[base.GetStageNumber()][i];	// 描画用に一時的に取得
		VECTOR drawPos = VAdd(car.GetPosition(), VGet(carMoveX, 0, 0));
		MV1SetPosition(car.GetCarHandle(), drawPos);	// 車の座標を更新
		MV1DrawModel(car.GetCarHandle());
		// 衝突したらゲームオーバーに設定
		if (!base.GetIsGameStop() && IsCollision(player, drawPos, car.GetHeight(), car.GetRadius(), true, false)) {
			fadeManager.ChangeUIState(GAMEOVER, fadeManager.NOTFADE);
			audioManager.PlaySE(audioManager.JINGLE_GAMEOVER);
		}
	}

	// 雲の描画

	for (int j = 0; j < cloudArray[base.GetStageNumber()].size(); j++) {
		Cloud cloud = cloudArray[base.GetStageNumber()][j];
		MV1SetPosition(cloud.GetCloudHandle(), cloud.GetPosition());
		MV1DrawModel(cloud.GetCloudHandle());
		if (IsCollision(player, cloud.GetPosition(), cloud.GetHeight(), cloud.GetRadius(), false, cloud.GetIsScoreAdd())) {
			test = true;
		}
	}

	player.SetIsGround(test);
}

bool StageManager::IsCollision(Player& player, VECTOR objPos, float height, float radius, bool isObstacles, bool isCloudScoreAdd) {
	VECTOR playerPos = player.GetPosition();
	VECTOR playerScale = player.GetScale();
	bool collisionX = (playerPos.x + playerScale.x > objPos.x - radius) && (playerPos.x - playerScale.x < objPos.x + radius);	// X軸でプレイヤーがオブジェクトに衝突しているか判定
	bool collisionY = (player.GetIsGravityBottom() && playerPos.y <= objPos.y + height && playerPos.y + playerScale.y >= objPos.y) ||	// 下のオブジェクトならオブジェ上側よりプレイヤーが下か、上のオブジェクトならオブジェ下側よりプレイヤー上に居るか判定
		(!player.GetIsGravityBottom() && playerPos.y >= objPos.y + height && playerPos.y - playerScale.y <= objPos.y);

	//足場の判定
	if (!isObstacles) {
		// プレイヤーがobj.xの範囲内にいてobj.yの範囲内にもいる場合設置判定を有効にする
		if (collisionX && collisionY) {
			player.SetGroundPosY(objPos.y + height);	// 足場となる座標を保存
			float objRightDis = base.ClampNumF((objPos.x + radius) - playerPos.x, 0, 500);
			if (isCloudScoreAdd && player.CheckChangeJumpDis(objRightDis)) {
				player.SetJumpDis(objRightDis);
			}
			return true;
		}
		// obj.yの範囲内にいるがobj.xの範囲外にいる場合はそのまま落下する
		else if (!collisionX && collisionY) {
			return false;
		}
	}
	// 車の判定
	else {
		float objLeftDis = base.ClampNumF((objPos.x - radius) - playerPos.x,0,500);
		if (collisionX && collisionY) return true;	// 車の中にプレイヤーが侵入したら
		else if (!collisionX && collisionY && player.CheckChangeJumpDis(objLeftDis)) {
			player.SetJumpDis(objLeftDis);
		}
	}
	return false;
}

bool StageManager::IsClear(float playerPosX) {
	return playerPosX >= GOAL_POS_X[base.GetStageNumber()] + CLEAR_CHANGE_DIS;	// ゴール後一定以上進んだらクリア画面の遷移を可能にするフラグをtrueにする
}

void StageManager::Initialization() {
	carMoveX = 0;	// 車の移動座標の初期化
	// 背景ステージの座標をステージに合わせて変更
	cityDrawPos.z = CITY_POS_Z[base.GetStageNumber()];
	MV1SetPosition(cityHandle, cityDrawPos);
}