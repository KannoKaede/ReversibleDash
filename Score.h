#pragma once
#include "Main.h"
#include "InGame.h"
	// クラスにリファクタリングする。もしくは関数でしっかりと作る
#ifndef INCLUDED_Score_h
#define INCLUDED_Score_h

#define ADD_SCORE_10 10
#define ADD_SCORE_100 100
#define ADD_SCORE_200 200
/// <summary> スコアを保存する </summary>
extern int score;
/// <summary> ハイスコアを保存する </summary>
extern int highScore[MAX_STAGE_NUM];
/// <summary>/// インゲーム表示用のスコア/// </summary>
extern int inGameVewScore;

/// <summary> スコアを計算する関数 </summary>
void ScoreCalculation(float speed);	// インゲームを実装したら引数を実装する

/// <summary> インゲームでスコアを表示する関数 </summary>
void InGameScoreView();

void HighScoreCheck();

extern float jumpDistance;

#endif