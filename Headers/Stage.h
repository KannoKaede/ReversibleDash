#pragma once
#include "DxLib.h"
#include "Player.h"
#include <vector>
#include <random>


static constexpr int	MAX_STAGE_NUM = 7;			//ステージの最大数：配列で使用するためステージ数＋１

// 車の情報をまとめたクラス
class Car {
public:
	/// <summary> コンストラクタ </summary>
	/// <param name="type"> モデルデータはまだ入れられないのでモデルデータの要素数を入れる </param>
	Car(int type, float _height, float _radius, float posX) :carHandle(type), height(_height), radius(_radius), position(VGet(posX, 40, 250)) {}

	/// <summary> 車のモデルデータを返す </summary>
	int		GetCarHandle()const			{ return carHandle; }
	/// <summary> 車の高さを返す </summary>
	float	GetHeight()const			{ return height; }
	/// <summary> 車の半径を返す </summary>
	float	GetRadius()const			{ return radius; }
	/// <summary> 車の座標を返す </summary>
	VECTOR	GetPosition()const			{ return position; }

	/// <summary> 車のモデルデータを設定する </summary>
	void	SetCarHandle(int handle)	{ carHandle = handle; }
private:
	int		carHandle;		// モデルデータ
	float	height;			// 高さ
	float	radius;			// 半径
	VECTOR	position;		// 座標
};

// 雲の情報をまとめたクラス
class Cloud {
public:
	/// <summary> コンストラクタ </summary>
	/// <param name="type"> モデルデータはまだ入れられないのでモデルデータの要素数を入れる </param>
	Cloud(int type, float drawPosX, bool scoreAdd = false) :cloudHandle(type), height(-50), radius(120), position(VGet(drawPosX, 700, 250)), isScoreAdd(scoreAdd) {}
	
	/// <summary> 雲のモデルデータを返す </summary>
	int		GetCloudHandle()const				{ return cloudHandle; }
	/// <summary> 雲の高さを返す </summary>
	float	GetHeight()const					{ return height; }
	/// <summary> 雲の半径を返す </summary>
	float	GetRadius()const					{ return radius; }
	/// <summary> 雲の座標を返す </summary>
	VECTOR	GetPosition()const					{ return position; }
	/// <summary> ジャンプした際にスコアを加点するかのフラグを返す </summary>
	bool	GetIsScoreAdd()const				{ return isScoreAdd; }
	 

	/// <summary> 雲のモデルデータを設定する </summary>
	void	 SetCloudHandle(int _cloudHandle)	{ cloudHandle = _cloudHandle; }
private:
	int		cloudHandle;	// モデルデータ
	float	height;			// 雲の高さ
	float	radius;			// 雲の半径
	VECTOR	position;		// 雲の座標
	bool	isScoreAdd;		// ジャンプ時にスコアを加点するか
};


// ステージ描画を管理するクラス
class StageManager {
public:
	/// <summary> コンストラクタ </summary>
	StageManager() :cityHandle(), cityDrawPos(VGet(23700, 0, 0)), carHandle{}, cloudHandle{}, carMoveX() {}

	/// <summary> コンストラクタでは設定できないモデルデータをロードするメソッド </summary>
	void SetUp();

	/// <summary> ステージに配置する車の座標やモデルなどを設定する </summary>
	void CarsSetUp();

	/// <summary> ステージに配置する雲の座標やモデルなどを設定する </summary>
	void CloudsSetUp();

	/// <summary> ステージの描画 </summary>
	void Draw(Player& _player);

	/// <summary> プレイヤーと障害物の衝突判定を計算 </summary>
	/// <param name="_isObstacles"> 障害物として判定するか足場として判定するか </param>
	/// <param name="_isCloudScoreAdd"> 雲でジャンプしたときにスコアの計算を行うか </param>
	bool IsCollision(Player& _player, const VECTOR& _objPos, float _height, float _radius, bool _isObstacles, bool _isCloudScoreAdd);

	/// <summary> ゴール後にクリア画面に遷移するか判定 </summary>
	bool IsClear(float _playerPosX);

	/// <summary> 書き換えたデータをリセット </summary>
	void Initialization();

	/// <summary> 車(小)のモデルデータを設定する際に使用する配列の要素を返す </summary>
	int		SmallCarModelRandom()const { return base.Random(0,3); }
	/// <summary> 車(大)のモデルデータを設定する際に使用する配列の要素を返す </summary>
	int		LargeCarModelRandom()const { return base.Random(4,7); }
	/// <summary> 雲のモデルデータを設定する際に使用する配列の要素を返す </summary>
	int		CloudModelRandom()const { return base.Random(0,4); }

	/// <summary> 背景ステージのモデルデータを返す </summary>
	int		GetCityHandle()const { return cityHandle; }
	/// <summary> 車のモデルデータを返す </summary>
	int		GetCarHandle(int _stageNumber)const { return carHandle[_stageNumber]; }
	/// <summary> 雲のモデルデータを返す </summary>
	int		GetCloudHandle(int _stageNumber)const { return cloudHandle[_stageNumber]; }
	/// <summary> 現在のステージのゴール座標を返す </summary>
	float	GetGoalPosition(int _stageNumber)const { return GOAL_POS_X[_stageNumber]; }
private:
	int						cityHandle;					// 背景ステージのモデルデータ
	VECTOR					cityDrawPos;				// 背景ステージの座標
	int						carHandle[8];				// 車のモデルデータ
	int						cloudHandle[5];				// 雲のモデルデータ
	float					carMoveX;					// 車の移動座標
	std::vector<Car>		carArray[MAX_STAGE_NUM];	// ステージごとの車のインスタンス
	std::vector<Cloud>		cloudArray[MAX_STAGE_NUM];	// ステージごとの雲のインスタンス

	static constexpr float S_CAR_HEIGHT = 110;														// 車(小)の高さ
	static constexpr float S_CAR_RADIUS = 130;														// 車(小)の半径
	static constexpr float L_CAR_HEIGHT = 220;														// 車(大)の高さ
	static constexpr float L_CAR_RADIUS = 320;														// 車(大)の半径
	static constexpr float CITY_POS_Z[MAX_STAGE_NUM] = { 0,32100,24100,16100,12100,6100,100 };		// ステージごとのステージ背景の描画開始座標Z
	static constexpr float GOAL_POS_X[MAX_STAGE_NUM] = { 0,14000,17000,14000,15000,14500,18000 };	// ゴール座標
	static constexpr float CLEAR_CHANGE_DIS = 1500;													// ゴール後にクリア画面に移動するまでに必要な距離
};
extern StageManager stageManager;