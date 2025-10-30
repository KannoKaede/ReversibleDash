#include"DxLib.h"
#include"InGame.h"
#include "Player.h"
#include"Score.h"
#include "UI.h"
#include <Math.h>
#include <cmath>
bool isGameStop;	// ゲームが止まっているか
int stageNumber;	// ステージ番号
ObjData obj;
ObjData ground;
int stageHandle;

void StageSetUp() {
	stageHandle = MV1LoadModel("Resource/stage/city.mv1");
}
void DrawStage(Player player) {
	DrawBackStage(player);
	ground = { VGet(0,0,0),40,10000 };
	obj = { VGet(200,TOP_GROUND,0),-70,5000 };
	IsCollision(player, obj, false);
	IsCollision(player, ground, false);
	DrawLine3D(VGet(obj.position.x + obj.radius, obj.position.y + obj.height, obj.position.z - obj.radius), VGet(obj.position.x - obj.radius, obj.position.y + obj.height, obj.position.z - obj.radius), GetColor(0, 0, 0));
	DrawLine3D(VGet(obj.position.x + obj.radius, obj.position.y + obj.height, obj.position.z + obj.radius), VGet(obj.position.x - obj.radius, obj.position.y + obj.height, obj.position.z + obj.radius), GetColor(0, 0, 0));
	DrawLine3D(VGet(obj.position.x + obj.radius, obj.position.y + obj.height, obj.position.z + obj.radius), VGet(obj.position.x + obj.radius, obj.position.y + obj.height, obj.position.z - obj.radius), GetColor(0, 0, 0));
	DrawLine3D(VGet(obj.position.x - obj.radius, obj.position.y + obj.height, obj.position.z + obj.radius), VGet(obj.position.x - obj.radius, obj.position.y + obj.height, obj.position.z - obj.radius), GetColor(0, 0, 0));
	DrawLine3D(VGet(ground.position.x + ground.radius, ground.position.y + ground.height, ground.position.z - ground.radius), VGet(ground.position.x - ground.radius, ground.position.y + ground.height, ground.position.z - ground.radius), GetColor(0, 0, 0));
	DrawLine3D(VGet(ground.position.x + ground.radius, ground.position.y + ground.height, ground.position.z + ground.radius), VGet(ground.position.x - ground.radius, ground.position.y + ground.height, ground.position.z + ground.radius), GetColor(0, 0, 0));
	DrawLine3D(VGet(ground.position.x + ground.radius, ground.position.y + ground.height, ground.position.z + ground.radius), VGet(ground.position.x + ground.radius, ground.position.y + ground.height, ground.position.z - ground.radius), GetColor(0, 0, 0));
	DrawLine3D(VGet(ground.position.x - ground.radius, ground.position.y + ground.height, ground.position.z + ground.radius), VGet(ground.position.x - ground.radius, ground.position.y + ground.height, ground.position.z - ground.radius), GetColor(0, 0, 0));
}


bool IsCollision(Player player, ObjData obj, bool isObstacles) {
	VECTOR playerPos = player.GetPosition();
	VECTOR playerScale = player.GetScale();
	bool collisionX = (playerPos.x + playerScale.x > obj.position.x - obj.radius) && (playerPos.x - playerScale.x < obj.position.x + obj.radius);	// X軸でプレイヤーがオブジェクトに衝突しているか判定
	bool collisionY = (isGravityBottom && playerPos.y <= obj.position.y + obj.height && playerPos.y + playerScale.y >= obj.position.y) ||	// 下のオブジェクトならオブジェ上側よりプレイヤーが下か、上のオブジェクトならオブジェ下側よりプレイヤー上に居るか判定
		(!isGravityBottom && playerPos.y >= obj.position.y + obj.height && playerPos.y - playerScale.y <= obj.position.y);

	// 足場の判定
	if (!isObstacles) {
		// プレイヤーがobj.xの範囲内にいてobj.yの範囲内にもいる場合設置判定を有効にする
		if (collisionX && collisionY) {
			groundPosY = obj.position.y + obj.height;	// 足場となる座標を保存
			isGround = true;
		}
		// obj.yの範囲内にいるがobj.xの範囲外にいる場合はそのまま落下する
		else if (!collisionX && collisionY) {
			isGround = false;
			isFall = true;
		}
	}
	else {
		if (collisionX && collisionY) {
			return true;
		}
	}
	return false;
}

VECTOR drawPos = {};
void DrawBackStage(Player player) {
	// 車が動いているように見せるためにステージ背景を左側に動かす
	if (!isGameStop && player.GetPosition().x <= goalPosition[stageNumber])drawPos.x -= 6;
	else if (!isGameStop && player.GetPosition().x >= goalPosition[stageNumber])drawPos.x -= 14;
	MV1SetPosition(stageHandle, drawPos);
	MV1DrawModel(stageHandle);
}

void StageInitialization() {
	drawPos = VGet(DRAW_BACKSTAGE_X, 0, DRAW_BACKSTAGE_Z[stageNumber]);
}

