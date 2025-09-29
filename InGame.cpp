#include"DxLib.h"
#include"InGame.h"
#include "Player.h"
#include "UI.h"
#include <cmath>
bool isGameStop;
int stageNumber;

void DrawStage(int stageNum, Player player) {
	DrawCone3D(VGet(430, 70, 40), VGet(430, -20, 40), 50, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	if (GetIsCollision(VGet(430, 70, 0), 90, 50, player.GetPosition(), 15, 7)) {
		nextScreenType = GAMEOVER;
		fadeState = SCREENSETUP;
	}
}


bool GetIsCollision(const VECTOR& coneApex, float coneHeight, float coneRadius, const VECTOR& playerPos, float playerHeight, float playerRadius)
{
	VECTOR coneBottomCenter = VGet(coneApex.x, coneApex.y - coneHeight, coneApex.z);    // 円錐の底面中心座標を取得　リファクタリング：変数for文で呼び出すのでその座標を引数で渡す

	// プレイヤーの上下座標を取得
	float playerTopPos = playerPos.y + playerHeight / 2.0f;
	float playerBottomPos = playerPos.y - playerHeight / 2.0f;

	// 円錐内での高さに応じた有効半径を算出
	float heightRatio = (coneApex.y - playerPos.y) / coneHeight;
	float coneCurrentRadius = coneRadius * (1.0f - heightRatio);

	// x方向の距離を計算
	float dx = playerPos.x - coneBottomCenter.x;
	float distX = fabsf(dx);

	// 衝突したか返す
	return (distX <= coneCurrentRadius + playerRadius);
}
