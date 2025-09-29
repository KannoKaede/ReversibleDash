#pragma once
#include "main.h"
#include "Player.h"
#ifndef INCLUDED_InGame_h
#define INCLUDED_InGame_h

extern bool isGameStop;
extern int stageNumber;     // 現在のステージ番号
const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
const float goalPosition[MAX_STAGE_NUM] = { 0,500,100,100,100,100,100 };

void DrawStage(int stageNum, Player player);

/// <summary> プレイヤーと円錐型の障害物の衝突判定 </summary>
/// <param name="coneApex">円錐の頂点座標</param>
/// <param name="coneHeight">円錐の高さ</param>
/// <param name="coneRadius">円錐の底面半径</param>
/// <param name="playerPos">プレイヤー座標</param>
/// <param name="playerHeight">プレイヤーの高さ</param>
/// <param name="playerRadius">プレイヤーの半径</param>
/// <returns>衝突判定</returns>
bool GetIsCollision(const VECTOR& coneApex, float coneHeight, float coneRadius, const VECTOR& playerPos, float playerHeight, float playerRadius);
#endif