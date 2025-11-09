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
#define CloudRandom rand()%5

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

// 雲の情報をまとめたクラス
class Cloud {
public:
	Cloud(int type, float drawPosX) :cloudHandle(type), height(-50), radius(120), position(VGet(drawPosX, 700, 250)) {}
	int GetCloudHandle() { return cloudHandle; }
	float GetHeight() { return height; }
	float GetRadius() { return radius; }
	VECTOR GetPosition() { return position; }
	void SetCloudHandle(int handle) { cloudHandle = handle; }
private:
	int cloudHandle;
	float height;
	float radius;
	VECTOR position;
};


// ステージ描画を管理するクラス
class StageManager {
public:
	/// <summary> コンストラクタ </summary>
	StageManager() :cityHandle(), cityDrawPos(VGet(23700, 0, 0)), carHandle(), cloudHandle(), carMoveX() {}

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
	int cloudHandle[5];	// 雲のモデルデータ
	const float CITY_POS_Z[MAX_STAGE_NUM] = { 0,32100,24100,16100,12100,6100,100 };	// ステージごとのステージ背景の描画開始座標Z
	const float GOAL_POS_X[MAX_STAGE_NUM] = { 0,14000,14800,14000,100000,100000,100000 };	// ゴール座標
	const float CLEAR_CHANGE_DIS = 1500;	// ゴール後にクリア画面に移動するまでに必要な距離
	const int COLLISION_DISTANCE = 155;		// 雲の衝突判定を行うか判定する距離
	float carMoveX;
	std::vector<Car> carArray[MAX_STAGE_NUM] = {	// ステージごとの車の情報を格納
		{},	// ステージ0は存在しないので空 車4500足したらいい感じ	選択してる車で来てる、上の雲出来てない
		// ステージ1
		{
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,2000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,3500),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,5000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,9000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,10500),
			Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,13000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,13900),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,14600),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,15300),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,16000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,16700),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,17400),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,18100),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,18800),
		},
		// ステージ2
		{
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,1500),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,3000),
			Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,5000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,5700),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,6300),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,7000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,7700),
			Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,11500),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,12200),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,12900),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,13600),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,14300),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,15000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,15700),
			Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,19000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,19700),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,20400),
		},
		// ステージ3
		{
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,2500),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,4000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,5500),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,7000),
			Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,10000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,13000),
			Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,16400),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,20000),
		},
		// ステージ4
		{
			Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,5000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,8000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,10000),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,11500),
			Car(LargeRandom,L_CAR_HEIGHT,L_CAR_RADIUS,13500),
			Car(SmallRandom,S_CAR_HEIGHT,S_CAR_RADIUS,15000),
		},
		// ステージ5
		{
		
		},
		// ステージ6
		{
		
		},
	};
	std::vector<Cloud> cloudArray[MAX_STAGE_NUM] = {
		{},
		// ステージ1
		{
			Cloud(CloudRandom,7240),
			Cloud(CloudRandom,7480),
			Cloud(CloudRandom,7720),
			Cloud(CloudRandom,7960),
			Cloud(CloudRandom,8200),
			Cloud(CloudRandom,8440),
			Cloud(CloudRandom,8680),
			// 隙間
			Cloud(CloudRandom,9320),
			Cloud(CloudRandom,9560),
			Cloud(CloudRandom,9800),
			Cloud(CloudRandom,10040),
			Cloud(CloudRandom,10280),
			Cloud(CloudRandom,10520),
			// 隙間
			Cloud(CloudRandom,11160),
			Cloud(CloudRandom,11400),
			Cloud(CloudRandom,11640),
			// 隙間
			Cloud(CloudRandom,11800),
			Cloud(CloudRandom,12040),
			Cloud(CloudRandom,12280),
			Cloud(CloudRandom,12520),
			Cloud(CloudRandom,12760),
			Cloud(CloudRandom,13000),
			Cloud(CloudRandom,13240),
			Cloud(CloudRandom,13480),
		},
		// ステージ2
		{
			Cloud(CloudRandom,2440),
			Cloud(CloudRandom,2680),
			Cloud(CloudRandom,2920),
			Cloud(CloudRandom,3160),
			Cloud(CloudRandom,3400),
			Cloud(CloudRandom,3640),
			Cloud(CloudRandom,3880),
			// 隙間
			Cloud(CloudRandom,4520),
			Cloud(CloudRandom,4760),
			Cloud(CloudRandom,5000),
			// 隙間
			Cloud(CloudRandom,6360),
			Cloud(CloudRandom,6500),
			Cloud(CloudRandom,6740),
			Cloud(CloudRandom,6980),
			Cloud(CloudRandom,7220),
			// 隙間
			Cloud(CloudRandom,7860),
			Cloud(CloudRandom,8100),
			Cloud(CloudRandom,8340),
			// 隙間
			Cloud(CloudRandom,8980),
			Cloud(CloudRandom,9220),
			Cloud(CloudRandom,9460),
			Cloud(CloudRandom,9700),
			// 隙間
			Cloud(CloudRandom,11000),
			Cloud(CloudRandom,11240),
			Cloud(CloudRandom,11480),
			Cloud(CloudRandom,11720),
			Cloud(CloudRandom,11960),
			Cloud(CloudRandom,12200),
			// 隙間
			Cloud(CloudRandom,12840),
			Cloud(CloudRandom,13080),
			Cloud(CloudRandom,13320),
			Cloud(CloudRandom,13560),
			Cloud(CloudRandom,13800),
		},
		// ステージ3
		{
			Cloud(CloudRandom,5500),
			Cloud(CloudRandom,5740),
			Cloud(CloudRandom,5980),
			Cloud(CloudRandom,6220),
			Cloud(CloudRandom,6460),
			Cloud(CloudRandom,6700),
			// 隙間
			Cloud(CloudRandom,7340),
			Cloud(CloudRandom,7580),
			Cloud(CloudRandom,7820),
			Cloud(CloudRandom,8060),
			// 隙間
			Cloud(CloudRandom,9200),
			Cloud(CloudRandom,9440),
			Cloud(CloudRandom,9680),
			Cloud(CloudRandom,9920),
			// 隙間
			Cloud(CloudRandom,10540),
			Cloud(CloudRandom,10780),
			Cloud(CloudRandom,11020),
			Cloud(CloudRandom,11260),
			Cloud(CloudRandom,11500),
		},
		// ステージ4
		{
		Cloud(CloudRandom,2500),
		Cloud(CloudRandom,2740),
		Cloud(CloudRandom,2980),
		Cloud(CloudRandom,3220),
		Cloud(CloudRandom,3460),
		Cloud(CloudRandom,3700),
		// 隙間
		Cloud(CloudRandom,4340),
		Cloud(CloudRandom,4580),
		Cloud(CloudRandom,4820),
		Cloud(CloudRandom,5060),
		// 隙間
		Cloud(CloudRandom,7500),
		Cloud(CloudRandom,7740),
		Cloud(CloudRandom,7980),
		Cloud(CloudRandom,8220),
		Cloud(CloudRandom,8460),
		// 隙間
		Cloud(CloudRandom,9100),
		Cloud(CloudRandom,9340),
		Cloud(CloudRandom,9580),
		Cloud(CloudRandom,9820),
		// 隙間
		},
		// ステージ5
		{
		
		},
		// ステージ6
		{
		
		},
	};
};
extern StageManager stageManager;	// StageManagerのインスタンス
