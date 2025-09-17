#pragma once
#include "Main.h"

#ifndef INCLUDED_Score_h
#define INCLUDED_Score_h
/// <summary> スコアを保存する </summary>
extern int score;
/// <summary> ハイスコアを保存する </summary>
extern int highScore[MAX_STAGE_NUM];
/// <summary>/// インゲーム表示用のスコア/// </summary>
extern int inGameVewScore;
/// <summary> スコア加算量 </summary>
const int SCORE_ADDED_POINT = 10;

/// <summary> スコアを計算する関数 </summary>
void ScoreCalculation();	// インゲームを実装したら引数を実装する

/// <summary> インゲームでスコアを表示する関数 </summary>
void InGameScoreView();

void HighScoreCheck();

#endif