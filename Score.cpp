#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
// 全体像が完成したらリファクタリングする（ハイスコアはセーブデータに保存するように変更）
int score;
int highScore[MAX_STAGE_NUM];
int inGameVewScore;
float jumpDistance;

/// <summary> スコアを計算する関数 </summary>
void ScoreCalculation(float speed) {
	if (CheckHitKeyDown(KEY_INPUT_SPACE) && currentScreenType == INGAME) {
		int plusScore = (400 - (int)jumpDistance) * 7 * (int)speed;
		if (plusScore > 0)score += plusScore;
		jumpDistance = 0;
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