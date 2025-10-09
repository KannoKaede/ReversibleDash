#pragma once

#ifndef INCLUDED_Main_h
#define INCLUDED_Main_h
extern bool isGameQuit;		// ゲームを終了するかのフラグ
extern int screenWidth;    // 画面の幅
extern int screenHeight;    // 画面の高さ
extern int bigFontHandle;	// フォント大
extern int normalFontHandle;	// フォント中
extern int smallFontHandle;	// フォント小

/// <summary> ゲームの最初に必要な情報を取得、設定する </summary>
void GameSetUp();
#endif
