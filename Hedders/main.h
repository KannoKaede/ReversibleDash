#pragma once
#include"DxLib.h"
#include"Audio.h"
#include"Input.h"
#include<iostream>
#include<vector>
#include<string>

#ifndef INCLUDED_Main_h
#define INCLUDED_Main_h
constexpr int TARGET_FPS = 60;		// 目標フレームレート
constexpr int FRAME_TIME = 1000 / TARGET_FPS;	// 1フレームの時間(ms)

extern bool isGameQuit;		// exe終了フラグ
extern int screenWidth, screenHeight;	// 画面サイズ

struct FONT {
	int fontHandle;
	int fontSize;
};
extern FONT fontData[4];
#define FONT_EXTRALARGE 0
#define FONT_LARGE 1
#define FONT_MEDIUM 2
#define FONT_SMALL 3

/// <summary> ゲームの初期設定を行うメソッド </summary>
void GameSetUp();

/// <summary> 値を指定の範囲に収めるメソッド </summary>
/// <param name="num"> 指定の値に収めたい変数 </param>
/// <param name="min"> 収める際の最小値 </param>
/// <param name="max"> 収める際の最大値 </param>
/// <returns> 指定の範囲に収められた値 </returns>
float ClampNum(float num, float min, float max);

float ScreenDrawPosF(int screenSize, float drawPosPercent);

int ScreenDrawPosI(int screenSize, float drawPosPercent);
int TextDrawCenterPosX(float left, float right, std::string text, int font);
int TextDrawCenterPosY(float top, float bottom, int fontSize, std::string text, int font);
void WaitFrameRate();
#endif

// ハイスコア　エクセルorメモで管理
// 起動時　車の中で外を眺めているムービーを作成
// タイトル画面　Escapeを押したらゲーム説明画面を表示
// プレイヤー　ジャンプアニメーションを1つにまとめて変更
// 衝突判定　全て四角形で行う
// ステージ　上側のステージを障害物ではなく足場に変更
