#pragma once
#include "Main.h"
#include "Player.h"
#include <vector>
#ifndef INCLUDED_InGame_h
#define INCLUDED_InGame_h

#define CLEARCANGE_POS 1200
enum class OBJECTTYPE {
	NONE,
	SMALL_CAR,
	LARGE_CAR,

};
struct MAPDATA {
	OBJECTTYPE objectType;	// 配置する障害物の種類
	int putNum;	// 配置する数
};
extern bool isGameStop;
extern int stageNumber;     // 現在のステージ番号
const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
const float goalPosition[MAX_STAGE_NUM] = { 0,7000,100,100,100,100,100 };	// ゴール座標:リファクタリング中の値をマップデータと円錐の半径を利用して代入したい
extern MAPDATA mapDataArray[MAX_STAGE_NUM][2][50];		// マップデータ

struct OBJECT_DATA {
	VECTOR  position;	// 障害物の座標
	float radius;	// 障害物の半径
	float height;	// 障害物の高さ
};
extern float objectDrawPosX;	// 障害物の描画位置X座標
constexpr float SMALL_CAR_RADIUS = 40.0f;
constexpr float SMALL_CAR_HEIGHT = 70.0f;
constexpr float LARGE_CAR_RADIUS = 120.0f;
constexpr float LARGE_CAR_HEIGHT = 210.0f;
constexpr float OBJECT_START_X = -360.0f;	// 障害物の描画開始X座標


/// <summary> ステージを描画するメソッド </summary>
/// <param name="stageNum"> ステージ番号 </param>
/// <param name="player"> プレイヤーのインスタンス </param>
void DrawStage(int stageNum, Player player);

void IsCollision(Player player, OBJECT_DATA obj,bool isTest);

#endif