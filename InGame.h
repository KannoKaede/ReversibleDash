#pragma once
#include "Main.h"
#include "Player.h"
#include <vector>
#ifndef INCLUDED_InGame_h
#define INCLUDED_InGame_h

#define CLEARCANGE_POS 1200
enum class OBJECTTYPE {
	NONE,
	SMALLCONE,
	BIGCONE
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
const int CORN_COLOR_TEST = GetColor(255, 0, 0);	// 仮の円錐の色
const float CORN_RADIUS = 40;	// 円錐の半径
const float CORN_HEIGHT = 40 * sqrt(3);	// 円錐の高さ
extern float ConePosX;	// 円錐を描画する際のX座標
const VECTOR TOP_DRAW_POS = VGet(-360, TOP_GROUND, 0);	// 上の円錐の底面座標
const VECTOR BOTTOM_DRAW_POS = VGet(-360, BOTTOM_GROUND, 0);	// 下の円数の底面座標


/// <summary> ステージを描画するメソッド </summary>
/// <param name="stageNum"> ステージ番号 </param>
/// <param name="player"> プレイヤーのインスタンス </param>
void DrawStage(int stageNum, Player player);

/// <summary> 円錐状の障害物を生成するメソッド </summary>
/// <param name="bottomCenterPos"> 円錐の底面中央座標 </param>
/// <param name="height"> 円錐の高さ </param>
void DrawCone(VECTOR bottomCenterPos, float height);

/// <summary> プレイヤーと円錐型の障害物の衝突判定 </summary>
/// <param name="coneApex">円錐の頂点座標</param>
/// <param name="coneHeight">円錐の高さ</param>
/// <param name="playerPos">プレイヤー座標</param>
/// <param name="playerHeight">プレイヤーの高さ</param>
/// <param name="playerRadius">プレイヤーの半径</param>
/// <returns>衝突判定</returns>
bool GetIsCollision(const VECTOR& coneApex, const float coneHeight, const VECTOR& playerPos, const float playerHeight, const float playerRadius);

/// <summary>
/// プレイヤーの中央座標と円錐の底面中央座標の距離を計算するメソッド
/// </summary>
/// <param name="p"> プレイヤーの中央座標 </param>
/// <param name="c"> 円錐底面中央座標 </param>
/// <returns> プレイヤーと円錐の距離 </returns>
float Distance(const VECTOR& p, const VECTOR& c);

/// <summary> プレイヤー中央と円錐底面を結ぶ線の中でプレイヤー内の長さを計算するメソッド </summary>
/// <param name="ortPA"> 架空の直角三角形のうちプレイヤー側の角度を計算 </param>
/// <returns> プレイヤー内の有効な距離 </returns>
float PlayerDistance(float ortPA);

/// <summary> プレイヤー中央と円錐底面を結ぶ線の中で円錐内の長さを計算するメソッド </summary>
/// <param name="ortCA"> 架空の直角三角形のうち円錐側の角度を計算 </param>
/// <returns> 円錐内の有効な距離 </returns>
float ConeDistance(float height, float ortCA);
#endif