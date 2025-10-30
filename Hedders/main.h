#pragma once
#include"DxLib.h"
#include"Audio.h"
#include"Input.h"
#include<iostream>
#include <fstream>
#include<vector>
#include<cmath>
#include<string>


// 画面サイズを格納する構造体
struct SCREEN_SIZE {
	int width;				// 画面の幅
	int height;				// 画面の高さ
};

extern SCREEN_SIZE screen;	// 画面サイズ

// フォントの種類と数を定義
enum FONT_TYPE {
	EXTRALARGE,				// 見出し用
	LARGE,					// ボタン用
	MEDIUM,					// スコア、ボタン用
	SMALL,					// 操作説明用
	FONT_TYPE_NUM			// フォントの種類
};

// フォントデータを格納する構造体
struct FONT_DATA {
	int fontHandle;			// フォントデータ
	int fontSize;			// フォントサイズ
};

extern FONT_DATA fontData[FONT_TYPE_NUM];	// フォントデータとサイズ

extern bool isDrawInGame;

/// <summary> ゲームの初期設定を行うメソッド </summary>
void GameSetUp();

/// <summary> 値を指定の範囲に収めるメソッド </summary>
/// <param name="num"> 指定の値に収めたい変数 </param>
/// <param name="min"> 収める際の最小値 </param>
/// <param name="max"> 収める際の最大値 </param>
/// <returns> 指定の範囲に収められた値 </returns>
float ClampNumF(float num, float min, float max);
int ClampNumI(int num, int min, int max);

float ScreenDrawPosF(int screenSize, float drawPosPercent);

int ScreenDrawPosI(int screenSize, float drawPosPercent);
int TextDrawCenterPosX(float left, float right, std::string text, int font);
int TextDrawCenterPosY(float top, float bottom, int fontSize, std::string text, int font);
bool IsDrawInGame();

float ChangeRadians(float num);

// 起動時　車の中で外を眺めているムービーを作成
// タイトル画面　Escapeを押したらゲーム説明画面を表示
// プレイヤー　ジャンプアニメーションを1つにまとめて変更
// ステージ　上側のステージを障害物ではなく足場に変更
