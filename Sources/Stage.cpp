#include "Main.h"
#include"Stage.h"
#include "UI.h"

StageManager stageManager;

void StageManager::SetUp() {
	cityHandle = MV1LoadModel("Resource/Stages/city.mv1");
	carHandle[0] = MV1LoadModel("Resource/Stages/SmallCar/SmallCar_1.mv1");
	carHandle[1] = MV1LoadModel("Resource/Stages/SmallCar/SmallCar_2.mv1");
	carHandle[2] = MV1LoadModel("Resource/Stages/SmallCar/SmallCar_3.mv1");
	carHandle[3] = MV1LoadModel("Resource/Stages/SmallCar/SmallCar_4.mv1");
	carHandle[4] = MV1LoadModel("Resource/Stages/LargeCar/LargeCar_1.mv1");
	carHandle[5] = MV1LoadModel("Resource/Stages/LargeCar/LargeCar_2.mv1");
	carHandle[6] = MV1LoadModel("Resource/Stages/LargeCar/LargeCar_3.mv1");
	carHandle[7] = MV1LoadModel("Resource/Stages/LargeCar/LargeCar_4.mv1");
	
	// コンストラクタでモデルを設定できないのでここでモデルを設定する
	for (int i = 1; i < MAX_STAGE_NUM; i++) {
		for (size_t j = 0; j < carArray[i].size(); j++) {
			carArray[i][j].SetCarHandle(carHandle[carArray[i][j].GetCarHandle()]);
		}
	}
}

void StageManager::Draw(Player& player) {
	// 背景ステージの描画と衝突判定の設定
	MV1DrawModel(cityHandle);
	IsCollision(player, VGet(12000, 0, 0), 40, 20000, false);

	// 車の描画
	if (!base.GetIsGameStop()) carMoveX += -7;	// 車を左に移動させていく
	for (size_t i = 0; i < carArray[base.GetStageNumber()].size(); i++) {
		Car car = carArray[base.GetStageNumber()][i];	// 書きやすい用に使うインスタンスを格納
		VECTOR drawPos = VAdd(car.GetPosition(), VGet(carMoveX, 0, 0));
		MV1SetPosition(car.GetCarHandle(),drawPos);	// 車の座標を更新
		MV1DrawModel(car.GetCarHandle());
		// 衝突したらゲームオーバーに設定
		if (!base.GetIsGameStop() && IsCollision(player, drawPos, car.GetHeight(), car.GetRadius(), true))ChangeUIState(GAMEOVER, SCREENSETUP);
	}
}

bool StageManager::IsCollision(Player& player, VECTOR objPos, float height, float radius, bool isObstacles) {
	VECTOR playerPos = player.GetPosition();
	VECTOR playerScale = player.GetScale();
	bool collisionX = (playerPos.x + playerScale.x > objPos.x - radius) && (playerPos.x - playerScale.x < objPos.x + radius);	// X軸でプレイヤーがオブジェクトに衝突しているか判定
	bool collisionY = (player.isGravityBottom && playerPos.y <= objPos.y + height && playerPos.y + playerScale.y >= objPos.y) ||	// 下のオブジェクトならオブジェ上側よりプレイヤーが下か、上のオブジェクトならオブジェ下側よりプレイヤー上に居るか判定
		(!player.isGravityBottom && playerPos.y >= objPos.y + height && playerPos.y - playerScale.y <= objPos.y);
	// 衝突判定デバッグ用ライン　判定枠の表示
	/*float z = 70;
	DrawLine3D(VGet(objPos.x + radius, objPos.y, objPos.z + z), VGet(objPos.x + radius, objPos.y, objPos.z - z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x - radius, objPos.y, objPos.z + z), VGet(objPos.x - radius, objPos.y, objPos.z - z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x + radius, objPos.y, objPos.z + z), VGet(objPos.x - radius, objPos.y, objPos.z + z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x + radius, objPos.y, objPos.z - z), VGet(objPos.x - radius, objPos.y, objPos.z - z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x + radius, objPos.y + height, objPos.z + z), VGet(objPos.x + radius, objPos.y + height, objPos.z - z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x - radius, objPos.y + height, objPos.z + z), VGet(objPos.x - radius, objPos.y + height, objPos.z - z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x + radius, objPos.y + height, objPos.z + z), VGet(objPos.x - radius, objPos.y + height, objPos.z + z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x + radius, objPos.y + height, objPos.z - z), VGet(objPos.x - radius, objPos.y + height, objPos.z - z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x + radius, objPos.y, objPos.z + z), VGet(objPos.x + radius, objPos.y + height, objPos.z + z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x - radius, objPos.y, objPos.z + z), VGet(objPos.x - radius, objPos.y + height, objPos.z + z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x + radius, objPos.y, objPos.z + z), VGet(objPos.x + radius, objPos.y + height, objPos.z + z), GetColor(255, 255, 255));
	DrawLine3D(VGet(objPos.x + radius, objPos.y, objPos.z - z), VGet(objPos.x + radius, objPos.y + height, objPos.z - z), GetColor(255, 255, 255));*/
	 //足場の判定
	if (!isObstacles) {
		// プレイヤーがobj.xの範囲内にいてobj.yの範囲内にもいる場合設置判定を有効にする
		if (collisionX && collisionY) {
			player.groundPosY = objPos.y + height;	// 足場となる座標を保存
			player.isGround = true;
		}
		// obj.yの範囲内にいるがobj.xの範囲外にいる場合はそのまま落下する
		else if (!collisionX && collisionY) {
			player.isGround = false;
			player.isFall = true;
		}
	}
	// 車の判定
	else {
		if (collisionX && collisionY) return true;	// 車の中にプレイヤーが侵入したら
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