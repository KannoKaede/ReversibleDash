#pragma once
#include  "Player.h"
// ゲームの制御に関する変数、関数をまとめたヘッダ
#ifndef INCLUDED_Main_h
#define INCLUDED_Main_h
/// <summary> ゲーム(exe)を終了するかのフラグ </summary>
extern bool isGameQuit;

extern int stageNumber;     // 現在のステージ番号
const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
extern int screenWidth;    // 画面の幅
extern int screenHeight;    // 画面の高さ

#endif

// 明日
// フェードのリファクタリング
// 3D描画の下準備