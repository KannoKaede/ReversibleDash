#pragma once
#include "DxLib.h"
#include "Player.h"
#include <vector>

const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
constexpr float S_CAR_HEIGHT = 110;	// オブジェクトの高さ
constexpr float S_CAR_RADIUS = 130;	// オブジェクトの半径
constexpr float L_CAR_HEIGHT = 220;	// オブジェクトの高さ
constexpr float L_CAR_RADIUS = 320;	// オブジェクトの半径
#define SmallRandom rand() % 4
#define LargeRandom rand() % 4 + 4

// 車の情報をまとめたクラス
class Car {
public:
	/// <summary> コンストラクタ </summary>
	/// <param name="type"> モデルデータはまだ入れられないのでモデルデータの要素数を入れる </param>
	/// <param name="_height"> 車の高さ </param>
	/// <param name="_radius"> 車の半径 </param>
	/// <param name="posX"> 車の描画座標X </param>
	Car(int type, float _height, float _radius, float posX) :carHandle(type), height(_height), radius(_radius), position(VGet(posX, 40, 250)) {}

	// private変数を読み取り専用で渡すメソッド群
	int GetCarHandle() { return carHandle; }
	float GetHeight() { return height; }
	float GetRadius() { return radius; }
	VECTOR GetPosition() { return position; }

	// private変数に値を書き込むメソッド
	void  SetCarHandle(int handle) { carHandle = handle; }
private:
	int carHandle;	// モデルデータ
	float height;	// 高さ
	float radius;	// 半径
	VECTOR position;	// 座標
};


// ステージ描画を管理するクラス
class StageManager {
public:
	/// <summary> コンストラクタ </summary>
	StageManager() :cityHandle(), cityDrawPos(VGet(23700, 0, 0)), carHandle(), carMoveX() {}

	/// <summary> コンストラクタでは設定できないモデルデータをロードするメソッド </summary>
	void SetUp();

	/// <summary> ステージを描画するメソッド </summary>
	/// <param name="player"> プレイヤーのインスタンス </param>
	void Draw(Player& player);

	/// <summary>
	/// 衝突判定を返すメソッド
	/// </summary>
	/// <param name="player"> プレイヤーのインスタンス </param>
	/// <returns> 衝突判定 </returns>
	bool IsCollision(Player& player, VECTOR objPos, float height, float radius, bool isObstacles);

	/// <summary> ゴール後にクリア画面に遷移出来るか返すメソッド </summary>
	/// <param name="playerPosX"> プレイヤーの座標X </param>
	/// <returns> クリア画面に遷移可能か </returns>
	bool IsClear(float playerPosX);

	/// <summary> 書き換えたデータをリセットするメソッド </summary>
	void Initialization();

	// private変数を読み取り専用で渡すメソッド群
	int GetCityHandle() { return cityHandle; }
	int GetCarHandle(int number) { return carHandle[number]; }
	float GetGoalPosition(int number) { return GOAL_POS_X[number]; }

	// private変数に値を書き込むメソッド
	void SetCarArray(int stageNum, Car car) { carArray[stageNum].push_back(car); }
private:
	int cityHandle;	// 背景ステージのモデルデータ
	VECTOR cityDrawPos;	// 背景ステージの座標
	int carHandle[8];	// 車のモデルデータ
	const float CITY_POS_Z[MAX_STAGE_NUM] = { 0,32100,24100,16100,12100,6100,100 };	// ステージごとのステージ背景の描画開始座標Z
	const float GOAL_POS_X[MAX_STAGE_NUM] = { 0,7000,100,100,100,100,100 };	// ゴール座標
	const float CLEAR_CHANGE_DIS = 1500;	// ゴール後にクリア画面に移動するまでに必要な距離
	float carMoveX;
	std::vector<Car> carArray[MAX_STAGE_NUM] = {	// ステージごとの車の情報を格納
		{},	// ステージ0は存在しないので空
		// ステージ1
		{Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,1000),Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,3000)},
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
};
extern StageManager stageManager;	// StageManagerのインスタンス
