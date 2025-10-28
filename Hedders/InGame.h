#pragma once
#include "Main.h"
#include "Player.h"
#include <vector>
#ifndef INCLUDED_InGame_h
#define INCLUDED_InGame_h

#define CLEARCANGE_POS 1200
extern bool isGameStop;
extern int stageNumber;     // 現在のステージ番号
const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
const float goalPosition[MAX_STAGE_NUM] = { 0,7000,100,100,100,100,100 };	// ゴール座標:リファクタリング中の値をマップデータと円錐の半径を利用して代入したい


/// <summary> ステージを描画するメソッド </summary>
/// <param name="stageNum"> ステージ番号 </param>
/// <param name="player"> プレイヤーのインスタンス </param>
void DrawStage(int stageNum, Player player);
constexpr float OBJ_HEIGHT = 70.0f;
constexpr float OBJ_RADIUS = 40.0f;
struct ObjData {
	VECTOR position;
	float height;
	float radius;
};
extern ObjData obj;
/// <summary> プレイヤーとオブジェクトが衝突しているかを返すメソッド </summary>
/// <param name="player"> プレイヤーのインスタンス </param>
/// <param name="obj"> オブジェクトの構造体 </param>
/// <param name="isObstacles"> 障害物か足場、どちらで処理を行うか：true = 障害物 </param>
/// <returns> 衝突判定 </returns>
bool IsCollision(Player player, ObjData obj, bool isObstacles);




#endif