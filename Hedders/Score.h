#pragma once
#include <string>
#include "Stage.h"

constexpr int ADD_SCORE_10 = 10;	// viewScoreに加算するスコアの値
constexpr int ADD_SCORE_100 = 100;	// viewScoreに加算するスコアの値
constexpr int ADD_SCORE_200 = 200;	// viewScoreに加算するスコアの値

extern int score;	// 現在のスコアを保存
extern int highScore[MAX_STAGE_NUM];	// ハイスコアを保存する配列
extern int vewScore;	// インゲームで表示するスコア

/// <summary> スコアを計算する関数 </summary>
void ScoreCalculation(float speed);	// インゲームを実装したら引数を実装する

/// <summary> インゲームでスコアを表示する関数 </summary>
void InGameScoreView();

/// <summary> ハイスコアをチェックして代入するメソッド </summary>
void HighScoreCheck();

const std::string SCORE_FILEPATH = "Resource/HighScore_Data.txt";	// ハイスコアを保存するテキストファイルのパス

/// <summary> ハイスコアをロードするメソッド </summary>
void LoadHighScore();
/// <summary> ハイスコアをセーブするメソッド </summary>
void SaveHighScore();

extern float jumpDistance;
