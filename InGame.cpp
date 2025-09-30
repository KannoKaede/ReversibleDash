#include"DxLib.h"
#include"InGame.h"
#include "Player.h"
#include "UI.h"
bool isGameStop;	// ゲームが止まっているか
int stageNumber;	// ステージ番号
int mapDataArray[MAX_STAGE_NUM][2][256] = {	// マップデータ：奇数=円錐の描画する回数 偶数= 何も描画しないする回数：リファクタリングこのやり方だと一種類しか描画できない
	{{} ,{}},	// ステージ0は無いので何もない
	{	// ステージ1
		{1,43,9,1,10,1,5,1,10,1},
		{12,1,5,1,5,1,10,1,5,1,5,32,10,1}
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
	for (int y = 0; y < 2; y++) {
		drawConePosX = 0;	// 初期描画座標Xを初期化する
		for (int x = 0; x < 30; x++) {	// 30を配列の要素数分回せるようにリファクタリング
			if (mapDataArray[stageNumber][y][x] != 0) {
				if (x % 2 == 0) {	// 描画しない
					drawConePosX += CORN_RADIUS * 2 * mapDataArray[stageNumber][y][x];	// 円錐の直系分座標をずらす
				}
				else {	// 円錐描画
					for (int j = 0; j < mapDataArray[stageNumber][y][x]; j++) {
						VECTOR drawPos = VAdd(y == 0 ? TOP_DRAW_POS : BOTTOM_DRAW_POS, VGet(drawConePosX, 0, 0));	// 描画する座標を指定の値ずらす
						DrawCone(drawPos, y == 0 ? -CORN_HEIGHT : CORN_HEIGHT);
						if (GetIsCollision(drawPos, y == 0 ? -CORN_HEIGHT : CORN_HEIGHT, player.GetPosition(), 15, 7)) {	// 衝突判定を行う
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

void DrawCone(VECTOR bottomCenterPos, float height) {
	VECTOR topCenterPos = VAdd(bottomCenterPos, VGet(0, height, 0));
	DrawCone3D(topCenterPos, bottomCenterPos, CORN_RADIUS, 64, CORN_COLOR_TEST, CORN_COLOR_TEST, TRUE);
}


bool GetIsCollision(const VECTOR& coneBottom, const float coneHeight, const VECTOR& playerPos, const float playerHeight, const float playerRadius)
{
	float coneApexY = coneBottom.y + coneHeight;	// 引数を頂点から底面座標に変更するために頂点座標yを取得VECTORでもいい
	float playerTopY = playerPos.y + playerHeight * 0.5f;	// プレイヤーの頂点の高さ
	float playerBottomY = playerPos.y - playerHeight * 0.5f;	// プレイヤーの底面の高さ
	float coneMaxY = fmaxf(coneApexY, coneBottom.y);	// 円錐の低い方の座標を取得
	float coneMinY = fminf(coneApexY, coneBottom.y);	// 円錐の高い方の座標を取得
	bool isUpward = coneMinY == coneBottom.y;	// 円錐の向きを判定：上 = true/下 = false
	if (fabsf(playerPos.x - coneBottom.x) > CORN_RADIUS)return false;	// 円錐の半径よりも外側にいたらfalse
	if (coneMinY > playerTopY || coneMaxY < playerBottomY)return false;	// 円錐の高さの範囲外にいたらfalse

	// 円錐内での高さに応じた有効半径を算出
	float heightRatio{};
	if (isUpward) {
		heightRatio = (coneMaxY - playerTopY) / coneHeight;
	}
	else {
		heightRatio = (coneMinY - playerBottomY) / coneHeight;
	}
	float coneCurrentRadius = CORN_RADIUS * heightRatio;

	// x方向の距離を計算
	float dx = playerPos.x - coneBottom.x;
	float distX = fabsf(dx);

	// 衝突したか返す
	return (distX <= coneCurrentRadius + playerRadius);
}
