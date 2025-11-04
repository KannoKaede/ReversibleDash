#include "Main.h"
#include"Stage.h"
#include "UI.h"

Stage stage;

void Stage::SetUp() {
	backStageHandle = MV1LoadModel("Resource/stage/city.mv1");
}

void Stage::Draw(Player& player) {
	// 背景ステージの描画、衝突判定を行う
	// メモ：障害物の描画と判定のfor文を追加
	DrawBackStage(player);
	IsCollision(player, ground, false);
	IsCollision(player, object, false);
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

void Stage::DrawBackStage(Player player) {
	// 車が動いているように見せるためにステージ背景を左側に動かす
	if (!base.isGameStop) {
		backDrawPos.x += 1.5f;
		if (player.GetPosition().x > goalPosition[base.stageNumber]) {
			backDrawPos.x -= 8;
		}
	}
	MV1SetPosition(backStageHandle, backDrawPos);
	MV1DrawModel(backStageHandle);
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

