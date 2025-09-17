#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"

float 距離測定ライン = 5;
float 距離 = 2;
float 移動速度 = 4;
void ScoreCalculation() {
	if (CheckHitKey(KEY_INPUT_SPACE) && currentScreenType == INGAME) {
		score += ((距離測定ライン * 10) - (距離 * 10)) * 移動速度;
		score += 3;
	}
	InGameScoreView();
}

void InGameScoreView() {
	printfDx("SCORE:%06d\n", inGameVewScore);

	if (inGameVewScore >= score) {
		inGameVewScore = score;
		return;
	}

	int differenceScore = score - inGameVewScore;
	int addedPoint = (differenceScore < SCORE_ADDED_POINT) ? differenceScore : SCORE_ADDED_POINT;
	inGameVewScore += addedPoint;

}