#pragma once
#include "DxLib.h"
#include <string>

const int COLOR_WHITEGRAY = GetColor(230, 230, 230);	// 背景ボックスで使用する色
const int COLOR_MINTGREEN = GetColor(230, 200, 50);  // 選択中のボタンの色
const int COLOR_LIGHTGRAY = GetColor(185, 185, 185);    // 非選択時のボタンの色
const int COLOR_BLACK = GetColor(0, 0, 0);   // テキストで使用する色
const int COLOR_WHITE = GetColor(255, 255, 255);   // テキストで使用する色

// フォントの種類と数を定義
enum FONT_TYPE {
	EXTRALARGE,				// 見出し用
	LARGE,					// ボタン用
	MEDIUM,					// スコア、ボタン用
	SMALL,					// 操作説明用
	FONT_TYPE_NUM			// フォントの種類
};

// 画面サイズの情報をまとめた構造体
struct ScreenSize {
	int width;				// 画面の幅
	int height;				// 画面の高さ
};

// フォントデータを格納する構造体
struct FontData {
	int handle;				// フォントデータ
	int size;				// フォントサイズ
};
struct VECTOR2 {
	float x;				// 横座標
	float y;				// 縦座標
};

class Base {
public:
	Base() :screen(), fontData{}, stageNumber(), isGameStop(true) {}	// コンストラクタ

	/// <summary> プロジェクト全体の初期設定を行う </summary>
	void SetUp();

	/// <summary> フォントの初期設定を行う </summary>
	void FontSetUp();

	/// <summary> ゲームの画面サイズを設定する </summary>
	void SetScreenSize();

	/// <summary> プロヘクト全体のリセット処理を行う </summary>
	void Initialization();

	/// <summary> exeを閉じる際にメモリの解放等を行う </summary>
	void CleanUp();

	/// <summary> 値を指定の範囲にint型で収めて返す </summary>
	int ClampNumI(int _num, int _min, int _max)const;

	/// <summary> 値を指定の範囲にfloat型で収めて返す </summary>
	float ClampNumF(float _num, float _min, float _max)const;

	/// <summary> 描画座標をint型で返す </summary>
	int ScreenDrawPosI(int _screenSize, float _drawPosPct);

	/// <summary> 描画座標をfloat型で返す </summary>
	float ScreenDrawPosF(int _screenSize, float _drawPosPct);

	/// <summary> テキストを左右中央に配置するための座標を返す</summary>
	int TextDrawCenterPosX(float _left, float _right, const std::string& _text, int _font);

	/// <summary> テキストを上下中央に配置するための座標を返す </summary>
	int TextDrawCenterPosY(float _top, float _bottom, int _fontSize, const std::string& _text);

	/// <summary> インゲームのステージを描画するかを返す </summary>
	bool IsDrawInGame();

	/// <summary> 度数法をラジアンに変換して返す </summary>
	constexpr float ChangeRadians(float _num) { return _num * DX_PI_F / 180; }

	/// <summary> 乱数を生成 </summary>
	int Random(int _min, int _max);

	/// <summary> 画面サイズを返す </summary>
	ScreenSize GetScreen()const					{ return screen; }
	/// <summary> フォントデータを返す </summary>
	FontData GetFontData(int _fontType)const	{ return fontData[_fontType]; }
	/// <summary> 現在のステージ番号を返す </summary>
	int GetStageNumber()const					{ return stageNumber; }
	/// <summary> 現在ゲームが止まっているかを返す </summary>
	bool GetIsGameStop()const					{ return isGameStop; }


	/// <summary> 現在のステージ番号を設定 </summary>
	void SetStageNumber(int _stageNumber)		{ stageNumber = _stageNumber; }
	/// <summary> ゲームの停止フラグを設定 </summary>
	void SetIsGameStop(bool _isGameStop)		{ isGameStop = _isGameStop; }
private:
	ScreenSize	screen;						// 画面サイズ情報
	FontData	fontData[FONT_TYPE_NUM];	// フォント情報
	int			stageNumber;				// ステージ番号
	bool		isGameStop;					// ゲームが停止しているかのフラグ
};

extern Base base;

// タイトル画面　Escapeを押したらゲーム説明画面を表示
// ジャンプゲージの実装
