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

	if (CheckHitKeyDown(KEY_INPUT_SPACE) && currentScreenType == INGAME&&jumpDistance<400) {
		if (jumpDistance == 0)return;
		int plusScore = (400 - (int)jumpDistance) * 7 * (int)speed;
		score += plusScore;
		jumpDistance = 0;
	}
	InGameScoreView();
}

/// <summary> インゲームでスコアを表示する関数 </summary>
void InGameScoreView() {
	int differenceScore = score - inGameVewScore;
	if (differenceScore == 0)return;
	int addedPoint = differenceScore < ADD_SCORE_10 ? differenceScore : ADD_SCORE_10;
	addedPoint = differenceScore< ADD_SCORE_100? differenceScore : ADD_SCORE_100;
	addedPoint = differenceScore< ADD_SCORE_200? differenceScore : ADD_SCORE_200;
	inGameVewScore += addedPoint;
}

void HighScoreCheck() {
	if (highScore[stageNumber] < score) {
		highScore[stageNumber] = score;
	}
}