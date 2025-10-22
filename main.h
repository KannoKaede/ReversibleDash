#pragma once
#include"DxLib.h"
#include "Audio.h"
#include"Input.h"
#include<vector>
#include<string>

#ifndef INCLUDED_Main_h
#define INCLUDED_Main_h


#define TARGET_FPS 60
#define FRAME_TIME 1000 / TARGET_FPS // 1フレーム = 約16ms

extern bool isGameQuit;		// ゲームを終了するかのフラグ
extern int screenWidth;    // 画面の幅
extern int screenHeight;    // 画面の高さ
extern int bigFontHandle;	// フォント大
extern int normalFontHandle;	// フォント中
extern int smallFontHandle;	// フォント小
extern int exampleFont;
extern int bigFontSize;
extern int normalFontSize;
extern int smallFontSize;
extern int exampleFontSize;

/// <summary> ゲームの最初に必要な情報を取得、設定する </summary>
void GameSetUp();

float ClampNum(float num, float min, float max);

float ScreenDrawPosF(int screenSize, float drawPosPercent);

int ScreenDrawPosI(int screenSize, float drawPosPercent);
int TextDrawCenterPosX(float left, float right, std::string text, int font);
int TextDrawCenterPosY(float top, float bottom, int fontSize, std::string text, int font);
void WaitFrameRate();
#endif
