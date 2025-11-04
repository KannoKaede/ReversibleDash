#include "Main.h"
#include"Stage.h"
#include "UI.h"

Stage stage;
int car;
void Stage::SetUp() {
	backStageHandle = MV1LoadModel("Resource/Stages/city.mv1");
	smallCarHandle[0] = MV1LoadModel("Resource/Stages/SmallCar/SmallCar_1.mv1");
	smallCarHandle[1] = MV1LoadModel("Resource/Stages/SmallCar/SmallCar_2.mv1");
	smallCarHandle[2] = MV1LoadModel("Resource/Stages/SmallCar/SmallCar_3.mv1");
	smallCarHandle[3] = MV1LoadModel("Resource/Stages/SmallCar/SmallCar_4.mv1");
	largeCarHandle[0] = MV1LoadModel("Resource/Stages/LargeCar/LargeCar_1.mv1");
	largeCarHandle[1] = MV1LoadModel("Resource/Stages/LargeCar/LargeCar_2.mv1");
	largeCarHandle[2] = MV1LoadModel("Resource/Stages/LargeCar/LargeCar_3.mv1");
	largeCarHandle[3] = MV1LoadModel("Resource/Stages/LargeCar/LargeCar_4.mv1");

}

void Stage::Draw(Player& player) {
	MV1SetPosition(backStageHandle, backDrawPos);
	MV1DrawModel(backStageHandle);
	// 背景ステージの描画、衝突判定を行う
	// メモ：障害物の描画と判定のfor文を追加
	for (int i = 0; i < 50; i++) {
		// モデルデータが存在しない場合はモデルデータを設定
		if (drawCarData[base.stageNumber][i].model == 0) {
			drawCarData[base.stageNumber][i].model = drawCarData[base.stageNumber][i].isLarge ?
				largeCarHandle[drawCarData[base.stageNumber][i].type] :
				smallCarHandle[drawCarData[base.stageNumber][i].type];
		}
		if (drawCarData[base.stageNumber][i].drawPosX == 0) break;	// 描画座標を定義していなかった場合は処理を抜ける

		if (!base.isGameStop) drawCarData[base.stageNumber][i].drawPosX -= 7;	// 車を前に進める
		VECTOR drawPos = VGet(drawCarData[base.stageNumber][i].drawPosX, 40, 250);
		MV1SetPosition(drawCarData[base.stageNumber][i].model, drawPos);
		MV1DrawModel(drawCarData[base.stageNumber][i].model);
	}
	IsCollision(player, ground, false);	// 地面衝突判定
	IsCollision(player, object, false);	// 空の衝突判定（テスト用）
}
bool Stage::IsGoal(float playerX) {
	// プレイヤー座標がゴール座標＋クリア画面に移動するための距離を超えたらtrueを返す
	return playerX >= goalPosition[base.stageNumber] + CLEARCANGE_POS;
}
int Stage::GetBackStageHandle()const {
	return backStageHandle;
}

void Stage::Initialization() {
	// 背景ステージの描画座標をステージ番号に合わせてリセット
	backDrawPos = VGet(DRAW_BACKSTAGE_X, 0, DRAW_BACKSTAGE_Z[base.stageNumber]);
}

bool Stage::IsCollision(Player& player, ObjData obj, bool isObstacles) {
	VECTOR playerPos = player.GetPosition();
	VECTOR playerScale = player.GetScale();
	bool collisionX = (playerPos.x + playerScale.x > obj.position.x - obj.radius) && (playerPos.x - playerScale.x < obj.position.x + obj.radius);	// X軸でプレイヤーがオブジェクトに衝突しているか判定
	bool collisionY = (player.isGravityBottom && playerPos.y <= obj.position.y + obj.height && playerPos.y + playerScale.y >= obj.position.y) ||	// 下のオブジェクトならオブジェ上側よりプレイヤーが下か、上のオブジェクトならオブジェ下側よりプレイヤー上に居るか判定
		(!player.isGravityBottom && playerPos.y >= obj.position.y + obj.height && playerPos.y - playerScale.y <= obj.position.y);

	// 足場の判定
	if (!isObstacles) {
		// プレイヤーがobj.xの範囲内にいてobj.yの範囲内にもいる場合設置判定を有効にする
		if (collisionX && collisionY) {
			player.groundPosY = obj.position.y + obj.height;	// 足場となる座標を保存
			player.isGround = true;
		}
		// obj.yの範囲内にいるがobj.xの範囲外にいる場合はそのまま落下する
		else if (!collisionX && collisionY) {
			player.isGround = false;
			player.isFall = true;
		}
	}
	else {
		if (collisionX && collisionY) {
			return true;
		}
	}
	return false;
}

