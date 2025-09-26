#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
// 全体像が完成したらリファクタリングする（ハイスコアはセーブデータに保存するように変更）
int score;
int highScore[MAX_STAGE_NUM];
int inGameVewScore;
//ここら辺は仮で置いておくインゲームを作り出したら消す
float 距離測定ライン = 5;
float 距離 = 2;
float 移動速度 = 4;

/// <summary> スコアを計算する関数 </summary>
void ScoreCalculation() {
	if (CheckHitKey(KEY_INPUT_SPACE) && currentScreenType == INGAME) {
		score += (((int)距離測定ライン * 10) - ((int)距離 * 10)) * (int)移動速度;
	}
	InGameScoreView();
}

/// <summary> インゲームでスコアを表示する関数 </summary>
void InGameScoreView() {
	if (inGameVewScore > score) {
		inGameVewScore = score;
		return;
	}

	// 実スコアと表示用スコアの差が一定より小さかったらその値を加算する。それ以外は一定の値を加算し続ける
	int differenceScore = score - inGameVewScore;
	int addedPoint = (differenceScore < SCORE_ADDED_POINT) ? differenceScore : SCORE_ADDED_POINT;
	inGameVewScore += addedPoint;
}

void HighScoreCheck() {
	if (highScore[stageNumber] < score) {
		highScore[stageNumber] = score;
	}
}