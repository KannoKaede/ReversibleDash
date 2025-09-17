#pragma once

/// <summary> スコアを保存する </summary>
__declspec(selectany) int score;
/// <summary> ハイスコアを保存する </summary>
__declspec(selectany) int highScore;
/// <summary>/// インゲーム表示用のスコア/// </summary>
__declspec(selectany) int inGameVewScore;
/// <summary> スコア加算量 </summary>
const int SCORE_ADDED_POINT = 10;

/// <summary> インゲームでスコアを表示する関数 </summary>
void InGameScoreView();

/// <summary> スコアを計算する関数 </summary>
void ScoreCalculation();	// インゲームを実装したら引数を実装する