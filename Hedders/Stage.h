#pragma once
#include "DxLib.h"
#include "Player.h"
#include <vector>

constexpr float CLEARCANGE_POS = 1500;	// ゴール後にクリア画面に移動するまでに必要な距離
const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
const float goalPosition[MAX_STAGE_NUM] = { 0,7000,100,100,100,100,100 };	// ゴール座標
constexpr float DRAW_BACKSTAGE_X = 23700;	// ステージ背景の描画開始座標X
constexpr float DRAW_BACKSTAGE_Z[MAX_STAGE_NUM] = { 0,32100,24100,16100,12100,6100,100 };	// ステージごとのステージ背景の描画開始座標Z
constexpr float OBJ_HEIGHT = 70.0f;	// オブジェクトの高さ
constexpr float OBJ_RADIUS = 40.0f;	// オブジェクトの半径

const VECTOR START_CAR_POS = VGet(2000, BOTTOM_GROUND, 250);
class Stage {
public:
	/// <summary> コンストラクタ </summary>
	Stage() :object({ VGet(200,TOP_GROUND,0),-70,5000 }), ground({ VGet(0,0,0),40,10000 }) {}

	/// <summary> ステージ初期設定メソッド </summary>
	void SetUp();

	/// <summary> ステージ描画メソッド </summary>
	/// <param name="player"> プレイヤーインスタンス </param>
	void Draw(Player& player);

	/// <summary> クリア画面に遷移出来るかを返すメソッド </summary>
	/// <param name="x"> プレイヤーのX座標 </param>
	/// <returns> クリア画面に遷移するか否か </returns>
	bool IsGoal(float playerX);

	/// <summary> 背景ステージのモデルを返すメソッド </summary>
	/// <returns> backStageHandle </returns>
	int GetBackStageHandle()const;

	/// <summary> ステージリセットメソッド </summary>
	void Initialization();
private:
	int backStageHandle = {};	// 背景ステージのモデルハンドル
	struct ObjData {	// オブジェクトのデータ構造体
		VECTOR position;	// 座標
		float height;	// 高さ
		float radius;	// 半径
	};
	ObjData object;	// テスト：地面のオブジェクト
	ObjData ground;	// テスト上のオブジェクト
	VECTOR backDrawPos = {};	// 背景ステージの描画座標

	int smallCarHandle[4] = {};
	int largeCarHandle[4] = {};
	struct DrawCarData {
		bool isLarge;
		int type;
		float drawPosX;
		int model;
	};
	DrawCarData drawCarData[MAX_STAGE_NUM][50] = {
		{},
		// ステージ1
		{
			{false,rand() % 4,1000,0},
			{true,rand()%4,2000,0}
		},
		// ステージ2
		{},
		// ステージ3
		{},
		// ステージ4
		{},
		// ステージ5
		{},
		// ステージ6
		{},
	};



	/// <summary> オブジェクトとプレイヤーの衝突判定を返すメソッド </summary>
	/// <param name="player"> プレイヤーのインスタンス </param>
	/// <param name="obj"> 判定を行うオブジェクト </param>
	/// <param name="isObstacles"> 地面として判定するか障害物として判定するかのフラグ：障害物 = true </param>
	/// <returns> 衝突しているか否か </returns>
	bool IsCollision(Player& player, ObjData obj, bool isObstacles);
};
extern Stage stage;
