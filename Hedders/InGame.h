#pragma once
#include "Main.h"
#include "Player.h"
#include <vector>
#ifndef INCLUDED_InGame_h
#define INCLUDED_InGame_h

#define CLEARCANGE_POS 1500

const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
const float goalPosition[MAX_STAGE_NUM] = { 0,7000,100,100,100,100,100 };	// ゴール座標
constexpr float DRAW_BACKSTAGE_X = 23700;	// ステージ背景の描画開始座標X
constexpr float DRAW_BACKSTAGE_Z[MAX_STAGE_NUM] = { 0,32100,24100,16100,12100,6100,100 };	// ステージごとのステージ背景の描画開始座標Z
class Stage {
public:

private:

};
/// <summary> ステージを描画するメソッド </summary>
/// <param name="stageNum"> ステージ番号 </param>
/// <param name="player"> プレイヤーのインスタンス </param>
void DrawStage(Player player);
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


extern int stageHandle;
void StageSetUp();
void DrawBackStage(Player player);
void StageInitialization();

#endif