#pragma once
#include "Main.h"
#include "Player.h"
#include <vector>
#ifndef INCLUDED_InGame_h
#define INCLUDED_InGame_h

extern bool isGameStop;
extern int stageNumber;     // 現在のステージ番号
const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
const float goalPosition[MAX_STAGE_NUM] = { 0,500,100,100,100,100,100 };	// ゴール座標
extern int mapDataArray[MAX_STAGE_NUM][2][256];		// マップデータ
const int CORN_COLOR_TEST = GetColor(255, 0, 0);	// 仮の円錐の色
const float CORN_RADIUS = 40;	// 円錐の半径
const float CORN_HEIGHT = 70;	// 円錐の高さ
extern float ConePosX;
const VECTOR TOP_DRAW_POS = VGet(-360, 700, 40);
const VECTOR BOTTOM_DRAW_POS = VGet(-360, -20, 40);



void DrawStage(int stageNum, Player player);

void DrawCone(VECTOR bottomCenterPos, float height);

/// <summary> プレイヤーと円錐型の障害物の衝突判定 </summary>
/// <param name="coneApex">円錐の頂点座標</param>
/// <param name="coneHeight">円錐の高さ</param>
/// <param name="playerPos">プレイヤー座標</param>
/// <param name="playerHeight">プレイヤーの高さ</param>
/// <param name="playerRadius">プレイヤーの半径</param>
/// <returns>衝突判定</returns>
bool GetIsCollision(const VECTOR& coneApex, float coneHeight, const VECTOR& playerPos, float playerHeight, float playerRadius);
#endif