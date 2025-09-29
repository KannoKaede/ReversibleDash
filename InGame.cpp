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
						if (GetIsCollision(VAdd(drawPos,VGet(0,CORN_HEIGHT,0)), 90, player.GetPosition(), 15, 7)) {	// 衝突判定を行う
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


bool GetIsCollision(const VECTOR& coneApex, float coneHeight, const VECTOR& playerPos, float playerHeight, float playerRadius)
{
	VECTOR coneBottomCenter = VGet(coneApex.x, coneApex.y - coneHeight, coneApex.z);    // 円錐の底面中心座標を取得　リファクタリング：変数for文で呼び出すのでその座標を引数で渡す

	// プレイヤーの上下座標を取得
	float playerTopPos = playerPos.y + playerHeight / 2.0f;
	float playerBottomPos = playerPos.y - playerHeight / 2.0f;

	// 円錐内での高さに応じた有効半径を算出
	float heightRatio = (coneApex.y - playerPos.y) / coneHeight;
	float coneCurrentRadius = CORN_RADIUS * (1.0f - heightRatio);

	// 高さが範囲外ならfalseを返す
	if (coneApex.y < playerPos.y || coneApex.y - coneHeight > playerPos.y)return false;

	// x方向の距離を計算
	float dx = playerPos.x - coneBottomCenter.x;
	float distX = fabsf(dx);

	// 衝突したか返す
	return (distX <= coneCurrentRadius + playerRadius);
}
