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

// 文字のフェード処理実装：画面のフェード処理と合体させてもいいかも
// ボタン操作の対応キーを増やした
// メインの関数呼び出しを整理

// 明日フェードのリファクタリング
// コメントを入れて
// 3D描画の下準備
// 画面描画をforにする
// const_cast<char*>(drawText.c_str())これを画面配置のところに入れる：これはstring用のもの