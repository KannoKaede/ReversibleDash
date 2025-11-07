#include "Score.h"
#include "Stage.h"
#include <fstream>
#include "UI.h"

float jumpDistance;
ScoreManager scoreManager;

void ScoreManager::AddScoreCalculate(float moveSpeed) {
	if (uiManager.IsEqualCurrenScreen(INGAME) && jumpDistance < 400) {
		score += (400 - (int)jumpDistance) * 7 * (int)moveSpeed;
		jumpDistance = 0;
	}
}

void ScoreManager::AddViewScore() {
	int differenceScore = score - viewScore;	// 表示スコアと実際のスコアの差分
	if (differenceScore == 0)return;

	// 差分が一定より大きい場合は加算するスコアを大きくする
	int addedPoint = differenceScore < ADD_SCORE_10 ? differenceScore : ADD_SCORE_10;
	addedPoint = differenceScore < ADD_SCORE_100 ? differenceScore : ADD_SCORE_100;
	addedPoint = differenceScore < ADD_SCORE_200 ? differenceScore : ADD_SCORE_200;

	viewScore += addedPoint;
}

void ScoreManager::CheckHighScore() {
	// ステージのハイスコアより高い場合は更新する
	if (highScore[base.GetStageNumber()] < score) highScore[base.GetStageNumber()] = score;
}

void ScoreManager::LoadHighScore() {
	// テキストファイルからハイスコアを読み込み値を代入する
	std::ifstream file("Resource/HighScore_Data.txt");

	// 一行ずつ読み込み、配列に代入する
	for (int i = 0; i < MAX_STAGE_NUM; i++) {
		if (!(file >> highScore[i])) {	// 読み込み失敗時は0を代入
			highScore[i] = 0;
		}
	}

	file.close();
}

void ScoreManager::SaveHighScore() {
	std::ofstream file("Resource/HighScore_Data.txt", std::ios::trunc);

	for (int i = 0; i < MAX_STAGE_NUM; i++) {	// ファイルにハイスコアを書き込む
		file << highScore[i] << "\n";
	}

	file.close();
}