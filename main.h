#pragma once

#ifndef INCLUDED_Main_h
#define INCLUDED_Main_h
extern bool isGameQuit;		// ゲームを終了するかのフラグ
extern int screenWidth;    // 画面の幅
extern int screenHeight;    // 画面の高さ
extern int bigFontHandle;	// フォント大
extern int normalFontHandle;	// フォント中
extern int smallFontHandle;	// フォント小
extern int bigFontSize;
extern int normalFontSize;
extern int smallFontSize;

/// <summary> ゲームの最初に必要な情報を取得、設定する </summary>
void GameSetUp();

/// <summary> 描画座標を返すメソッド </summary>
/// <param name="screenSize"> 基準にする画面サイズ</param>
/// <param name="drawPosPercent"> 描画したい場所（％）</param>
/// <returns> 描画座標 </returns>
float ScreenDrawPos(int screenSize, float drawPosPercent);
#endif
