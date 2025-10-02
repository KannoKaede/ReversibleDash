#include"DxLib.h"
#include"InGame.h"
#include "Player.h"
#include "UI.h"
#include <Math.h>
#include <cmath>
bool isGameStop;	// ゲームが止まっているか
int stageNumber;	// ステージ番号
MAPDATA mapDataArray[MAX_STAGE_NUM][2][50] = {	// マップデータ：奇数=円錐の描画する回数 偶数= 何も描画しないする回数：リファクタリングこのやり方だと一種類しか描画できない
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
void DrawStage(int stageNum, Player player) {	// リファクタリング：一個しか描画できないのでα版が終わったら書き直す
	//VECTOR drawPos = VAdd( BOTTOM_DRAW_POS, VGet(500, 0, 0));	// 描画する座標を指定の値ずらす
	//	DrawCone(drawPos, CORN_HEIGHT);
	//	if (GetIsCollision(drawPos,  CORN_HEIGHT, player.GetPosition(), 150, 50)) {	// 衝突判定を行う
	//		nextScreenType = GAMEOVER;
	//		fadeState = SCREENSETUP;
	//	}
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
							if (GetIsCollision(drawPos, y == 0 ? -CORN_HEIGHT : CORN_HEIGHT, player.GetPosition(), y == 0 ? -150 : 150, 8)) {	// 衝突判定を行う
								nextScreenType = GAMEOVER;
								fadeState = SCREENSETUP;
							}
							drawConePosX += CORN_RADIUS * 2;
						}
						if (mapDataArray[stageNumber][y][x].objectType == OBJECTTYPE::BIGCONE) {
							DrawCone(drawPos, y == 0 ? -CORN_HEIGHT * 4 : CORN_HEIGHT * 4);
							if (GetIsCollision(drawPos, y == 0 ? -CORN_HEIGHT * 4 : CORN_HEIGHT * 4, player.GetPosition(), y == 0 ? -150 : 150, 8)) {	// 衝突判定を行う
								nextScreenType = GAMEOVER;
								fadeState = SCREENSETUP;
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



bool GetIsCollision(const VECTOR& coneBottom, const float coneHeight, const VECTOR& playerPos, const float playerHeight, const float playerRadius)	// リファクタリング　現在は底面でしか計算が行われていない
{
	//VECTOR playerCenterPos = VAdd(playerPos, VGet(0, playerHeight / 2, playerPos.z));	// プレイヤー中央座標
	//float distance = Distance(playerCenterPos, coneBottom);	// 二点間の距離を計算
	//DrawLine3D(playerCenterPos, coneBottom, GetColor(0, 0, 255));	//	debag
	//float x = atan2(playerCenterPos.x - coneBottom.x, playerCenterPos.y - coneBottom.y) ;	// 二点の角度を計算
	//DrawTriangle3D(playerCenterPos, coneBottom, playerPos, GetColor(0, 0, 255), TRUE);	// debug
	//VECTOR dir = VSub(playerCenterPos, coneBottom); // 方向ベクトル
	//float theta = atan2f(dir.y, dir.x); // XY平面上の角度（ラジアン）
	//printfDx("%f", theta);

	//return false;
		float coneApexY = coneBottom.y + coneHeight;	// 引数を頂点から底面座標に変更するために頂点座標yを取得VECTORでもいい
		float playerHeadPos = playerPos.y + playerHeight;	// プレイヤーの頂点の高さ
		float coneMaxY = fmaxf(coneApexY, coneBottom.y);	// 円錐の低い方の座標を取得
		float coneMinY = fminf(coneApexY, coneBottom.y);	// 円錐の高い方の座標を取得
		bool isUpward = coneMinY == coneBottom.y;	// 円錐の向きを判定：上 = true/下 = false

		if (fabsf(playerPos.x - coneBottom.x) > CORN_RADIUS)return false;	// 円錐の半径よりも外側にいたらfalse
		if (coneMinY > playerPos.y || coneMaxY < playerPos.y)return false;	// 円錐の高さの範囲外にいたらfalse

		
	// 円錐内での高さに応じた有効半径を算出
	float heightRatio{};
	if (isUpward) {
		heightRatio = (coneMaxY - playerPos.y) / coneHeight;
	}
	else {
		heightRatio = (coneMinY - playerPos.y) / coneHeight;
	}
	float coneCurrentRadius = CORN_RADIUS * heightRatio;

	// x方向の距離を計算
	float dx = playerPos.x - coneBottom.x;
	float distX = fabsf(dx);

	// 衝突したか返す
	return (distX <= coneCurrentRadius + playerRadius);
}

float Distance(const VECTOR& a, const VECTOR& b) {
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
