#pragma once
// ゲームの制御に関する変数、関数をまとめたヘッダ
#ifndef INCLUDED_Main_h
#define INCLUDED_Main_h
/// <summary> ゲーム(exe)を終了するかのフラグ </summary>
extern bool isGameQuit;

extern int stageNumber;
const int MAX_STAGE_NUM = 7;
extern int screenWidth;
extern int screenHeight;
#endif