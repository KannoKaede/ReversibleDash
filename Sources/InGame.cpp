#include"DxLib.h"
#include"InGame.h"
#include "Player.h"
#include"Score.h"
#include "UI.h"
#include <Math.h>
#include <cmath>
bool isGameStop;	// ゲームが止まっているか
int stageNumber;	// ステージ番号
MAPDATA mapDataArray[MAX_STAGE_NUM][2][50] = {
   {{} ,{}},	// ステージ0は無いので何もない
   //{	// ステージ1
   //	{1,43,9,1,10,1,5,1,10,1},
   //	{12,1,5,1,5,1,10,1,5,1,5,32,10,1}
   //},
   {	// ステージ1
	   {{OBJECTTYPE::NONE,1},{OBJECTTYPE::SMALLCONE,43},{OBJECTTYPE::NONE,9},{OBJECTTYPE::SMALLCONE,1},{OBJECTTYPE::NONE,10},{OBJECTTYPE::SMALLCONE,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::SMALLCONE,1},{OBJECTTYPE::NONE,10},{OBJECTTYPE::BIGCONE,1}},
	   {{OBJECTTYPE::NONE,12},{OBJECTTYPE::SMALLCONE,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::SMALLCONE,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::SMALLCONE,1},{OBJECTTYPE::NONE,10},{OBJECTTYPE::SMALLCONE,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::SMALLCONE,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::BIGCONE,1},{OBJECTTYPE::SMALLCONE,31},{OBJECTTYPE::NONE,10},{OBJECTTYPE::BIGCONE,1}}
   },
   {// ステージ2
	   {},
	   {}
   },
   {// ステージ3
	   {},
	   {}
   },
   {// ステージ4
	   {},
	   {}
   },
   {// ステージ5
	   {},
	   {}
   },
   {// ステージ6
	   {},
	   {}
   }
};

float drawConePosX;
void DrawStage(int stageNum, Player player) {
	//VECTOR drawPos = VAdd(BOTTOM_DRAW_POS, VGet(500, 0, 0));	// 描画する座標を指定の値ずらす
	//DrawCone(drawPos, CORN_HEIGHT);
	//if (GetIsCollision(drawPos, CORN_HEIGHT, player.GetPosition(), 150, 50)) {	// 衝突判定を行う
	//	nextScreenType = GAMEOVER;
	//	fadeState = SCREENSETUP;
	//}
	for (int y = 0; y < 2; y++) {
		drawConePosX = 0;	// 初期描画座標Xを初期化する
		for (int x = 0; x < 50; x++) {	// 30を配列の要素数分回せるようにリファクタリング
			if (mapDataArray[stageNumber][y][x].putNum != 0) {
				if (mapDataArray[stageNumber][y][x].objectType == OBJECTTYPE::NONE) {	// 描画しない
					drawConePosX += CORN_RADIUS * 2 * mapDataArray[stageNumber][y][x].putNum;	// 円錐の直系分座標をずらす
				}
				else {	// 円錐描画
					for (int j = 0; j < mapDataArray[stageNumber][y][x].putNum; j++) {
						VECTOR drawPos = VAdd(y == 0 ? TOP_DRAW_POS : BOTTOM_DRAW_POS, VGet(drawConePosX, 0, 0));	// 描画する座標を指定の値ずらす
						if (mapDataArray[stageNumber][y][x].objectType == OBJECTTYPE::SMALLCONE) {
							DrawCone(drawPos, y == 0 ? -CORN_HEIGHT : CORN_HEIGHT);
							if (GetIsCollision(drawPos, y == 0.0f ? -CORN_HEIGHT : CORN_HEIGHT, player.GetPosition(), y == 0 ? -150.0f : 150.0f, 8.0f)) {	// 衝突判定を行う
								nextScreenType = GAMEOVER;
								fadeState = SCREENSETUP;
								isGameStop = true;
							}
							drawConePosX += CORN_RADIUS * 2;
						}
						if (mapDataArray[stageNumber][y][x].objectType == OBJECTTYPE::BIGCONE) {
							DrawCone(drawPos, y == 0 ? -CORN_HEIGHT * 4 : CORN_HEIGHT * 4);
							if (GetIsCollision(drawPos, y == 0.0f ? -CORN_HEIGHT * 4 : CORN_HEIGHT * 4, player.GetPosition(), y == 0 ? -150.0f : 150.0f, 8.0f)) {	// 衝突判定を行う
								nextScreenType = GAMEOVER;
								fadeState = SCREENSETUP;
								isGameStop = true;
							}
							drawConePosX += CORN_RADIUS * 2;
						}
					}
				}
			}
		}
	}
}

void DrawCone(VECTOR bottomCenterPos, float height) {
	VECTOR topCenterPos = VAdd(bottomCenterPos, VGet(0, height, 0));
	DrawCone3D(topCenterPos, bottomCenterPos, CORN_RADIUS, 64, CORN_COLOR_TEST, CORN_COLOR_TEST, TRUE);
}

bool GetIsCollision(const VECTOR& coneBottom, const float coneHeight, const VECTOR& playerPos, const float playerHeight, const float playerRadius)
{
	if (currentScreenType != INGAME)return false;
	if (playerPos.y == coneBottom.y && playerPos.x < coneBottom.x) {
		float distanceX = coneBottom.x - playerPos.x;
		if (distanceX == 0 || jumpDistance > distanceX)  jumpDistance = distanceX; 
		if (jumpDistance == 0) jumpDistance = distanceX; 
		if (distanceX < jumpDistance) { jumpDistance = distanceX; printfDx("%f", jumpDistance); };
	}
	if (fabsf(playerPos.x - coneBottom.x) > CORN_RADIUS + playerRadius)return false;
	VECTOR playerCenterPos = VAdd(playerPos, VGet(0, playerHeight / 2, playerPos.z));	// プレイヤー中央座標
	float distance = Distance(playerCenterPos, coneBottom);	// 二点間の距離を計算
	//DrawLine3D(playerCenterPos, coneBottom, GetColor(0, 255, 0));	// プレイヤー中央と円錐底面を結ぶ線を描画
	float bottomPosXXY_playerPosY = Distance(coneBottom, VGet(coneBottom.x, playerCenterPos.y, playerCenterPos.z));	// 二点をが垂直に交わる座標と円錐の底面座標の距離
	float ortPlayerAngle = (bottomPosXXY_playerPosY / distance) * 180 / DX_PI_F;	// 架空の直角三角形のうちプレイヤー側の角度を計算
	float ortConeAngle = 180 - 90 - ortPlayerAngle;	// 架空の直角三角形のうち円錐側の角度を計算
	float coneLength = ConeDistance(coneHeight, ortConeAngle);
	float playerLength = PlayerDistance(ortPlayerAngle);
	return distance < coneLength + playerLength;
}

float Distance(const VECTOR& p, const VECTOR& c) {
	return sqrtf((p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y) + (p.z - c.z) * (p.z - c.z));
}

float PlayerDistance(float ortPA) {
	float playerBottomDirection = 180 - 90 - ortPA;	// プレイヤー中央から円錐底面に向かう線と側面の角度
	return 50 / (playerBottomDirection / 180 * DX_PI_F);
}

float ConeDistance(float height, float ortCA) {
	float coneDownDirection = 90 - ortCA;	// プレイヤー中央から円錐底面に向かう線と底辺の角度
	float coneTopDirection = 180 - 60 - coneDownDirection;	// プレイヤー中央から円錐底面に向かう辺と円錐の外側の辺の角度：現在は正三角形なので60度
	float seigenA = CORN_RADIUS / (coneTopDirection / 180 * DX_PI_F);
	return seigenA * 60 / 180 * DX_PI_F;
}

