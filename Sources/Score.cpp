#include "Score.h"
#include "Stage.h"
#include <fstream>
#include "UI.h"

int score;
int highScore[MAX_STAGE_NUM];
int vewScore;
float jumpDistance;

/// <summary> スコアを計算する関数 </summary>
void ScoreCalculation(float speed) {

	if (currentScreenType == INGAME && jumpDistance < 400) {
		if (jumpDistance == 0)return;
		int plusScore = (400 - (int)jumpDistance) * 7 * (int)speed;
		score += plusScore;
		jumpDistance = 0;
	}
	InGameScoreView();
}

/// <summary> インゲームでスコアを表示する関数 </summary>
void InGameScoreView() {
	int differenceScore = score - vewScore;	// 表示スコアと実際のスコアの差分
	if (differenceScore == 0)return;

	// 差分が一定より大きい場合は加算するスコアを大きくする
	int addedPoint = differenceScore < ADD_SCORE_10 ? differenceScore : ADD_SCORE_10;
	addedPoint = differenceScore < ADD_SCORE_100 ? differenceScore : ADD_SCORE_100;
	addedPoint = differenceScore < ADD_SCORE_200 ? differenceScore : ADD_SCORE_200;

	vewScore += addedPoint;
}

void HighScoreCheck() {
	// ステージのハイスコアより高い場合は更新する
	if (highScore[base.stageNumber] < score) {
		highScore[base.stageNumber] = score;
	}
}

void LoadHighScore() {
	// テキストファイルからハイスコアを読み込み値を代入する
	std::ifstream file(SCORE_FILEPATH);

	// 一行ずつ読み込み、配列に代入する
	for (int i = 0; i < MAX_STAGE_NUM; i++) {
		if (!(file >> highScore[i])) {	// 読み込み失敗時は0を代入
			highScore[i] = 0;
		}
	}

	file.close();
}

void SaveHighScore() {
	std::ofstream file(SCORE_FILEPATH, std::ios::trunc); 

	for (int i = 0; i < MAX_STAGE_NUM; i++) {	// ファイルにハイスコアを書き込む
		file << highScore[i] << "\n";
	}

	file.close();
}
