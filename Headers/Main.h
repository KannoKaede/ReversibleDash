#pragma once
#include "DxLib.h"
#include <string>

const int COLOR_WHITEGRAY = GetColor(230, 230, 230);	// 背景ボックスで使用する色
const int COLOR_MINTGREEN = GetColor(230, 200, 50);  // 選択中のボタンの色
const int COLOR_LIGHTGRAY = GetColor(185, 185, 185);    // 非選択時のボタンの色
const int COLOR_BLACK = GetColor(0, 0, 0);   // テキストで使用する色
const int COLOR_WHITE = GetColor(255, 255, 255);   // テキストで使用する色
struct ScreenSize {
	int width;				// 画面の幅
	int height;				// 画面の高さ
};
// フォントの種類と数を定義
enum FONT_TYPE {
	EXTRALARGE,				// 見出し用
	LARGE,					// ボタン用
	MEDIUM,					// スコア、ボタン用
	SMALL,					// 操作説明用
	FONT_TYPE_NUM			// フォントの種類
};
// フォントデータを格納する構造体
struct FontData {
	int handle;			// フォントデータ
	int size;			// フォントサイズ
};
struct VECTOR2 {
	float x;
	float y;
};

class Base {
public:
	Base() :screen(), fontData(), stageNumber(0), isGameStop(true) {}	// コンストラクタ

	void SetScreenSize();
	void SetUp();
	void FontSetUp();
	void Initialization();
	void CleanUp();

	/// <summary> 値を指定の範囲にint型で収めて返すメソッド </summary>
	/// <param name="num"> 指定の値に収めたい変数 </param>
	/// <param name="min"> 収める際の最小値 </param>
	/// <param name="max"> 収める際の最大値 </param>
	/// <returns> 指定の範囲に収められた値 </returns>
	int ClampNumI(int num, int min, int max);

	/// <summary> 値を指定の範囲にfloat型で収めて返すメソッド </summary>
	/// <param name="num"> 指定の値に収めたい変数 </param>
	/// <param name="min"> 収める際の最小値 </param>
	/// <param name="max"> 収める際の最大値 </param>
	/// <returns> 指定の範囲に収められた値 </returns>
	float ClampNumF(float num, float min, float max);

	/// <summary> 描画座標をint型で返すメソッド </summary>
	/// <param name="screenSize"> ウィンドウサイズ（縦横どちらか） </param>
	/// <param name="drawPosPercent"> 描画したい場所（％） </param>
	/// <returns> スクリーン描画座標 </returns>
	int ScreenDrawPosI(int screenSize, float drawPosPercent);

	/// <summary> 描画座標をfloat型で返すメソッド </summary>
	/// <param name="screenSize"> ウィンドウサイズ（縦横どちらか） </param>
	/// <param name="drawPosPercent"> 描画したい場所（％） </param>
	/// <returns> スクリーン描画座標 </returns>
	float ScreenDrawPosF(int screenSize, float drawPosPercent);

	/// <summary> テキストを左右中央に配置するための座標を返すメソッド </summary>
	/// <param name="left"> 収めたい枠の左端座標 </param>
	/// <param name="right"> 収めたい枠の右端座標 </param>
	/// <param name="text"> 表示するテキスト </param>
	/// <param name="font"> 使用するフォント </param>
	/// <returns> 左右中央に配置するための座標X </returns>
	int TextDrawCenterPosX(float left, float right, std::string text, int font);

	/// <summary> テキストを上下秋桜に配置するための座標を返すメソッド </summary>
	/// <param name="top"> 収めたい枠の上部座標 </param>
	/// <param name="bottom"> 収めたい枠の下部座標 </param>
	/// <param name="fontSize"> 使用するフォントのサイズ </param>
	/// <param name="text"> 表示するテキスト </param>
	/// <returns> 上下中央に配置するための座標Y </returns>
	int TextDrawCenterPosY(float top, float bottom, int fontSize, std::string text);

	/// <summary> インゲームのステージやプレイヤーを表示するかのフラグを返すメソッド </summary>
	/// <returns> インゲームを描画するかのフラグ </returns>
	bool IsDrawInGame();

	/// <summary> 度数法をラジアンに変換して返すメソッド </summary>
	/// <param name="num"> 度数法での角度 </param>
	/// <returns> ラジアンに変換された角度 </returns>
	constexpr float ChangeRadians(float num);

	// private変数を読み取り専用で渡すメソッド群
	ScreenSize GetScreen() { return screen; }
	FontData GetFontData(int fontType) { return fontData[fontType]; }
	int GetStageNumber() { return stageNumber; }
	bool GetIsGameStop() { return isGameStop; }

	// private変数に値を書き込むメソッド
	void SetStageNumber(int num) { stageNumber = num; }
	void SetIsGameStop(bool _isGameStop) { isGameStop = _isGameStop; }
private:
	ScreenSize screen;	// 画面サイズ情報
	FontData fontData[FONT_TYPE_NUM];	// フォント情報
	int stageNumber;	// ステージ番号
	bool isGameStop;	// ゲームが停止しているかのフラグ
};

extern Base base;

// タイトル画面　Escapeを押したらゲーム説明画面を表示
// ジャンプゲージの実装
