#include "Score.h"
#include "Stage.h"
#include <fstream>
#include "UI.h"

ScoreManager scoreManager;

void ScoreManager::AddScoreCalculate(float dis,float moveSpeed) {
	if (uiManager.CheckScreen(INGAME) && dis < 500) {
		float addScore = (500.0f - dis) * moveSpeed * 4.7f;
		score += (int)addScore;
	}
}

void ScoreManager::AddViewScore() {
	int differenceScore = score - viewScore;	// 表示スコアと実際のスコアの差分
	if (differenceScore == 0)return;

	// ViewScoreに加算する値をスコアとの差に合わせて変更
	int addedPoint = differenceScore;
	for (int step : scoreSteps) {
		if (differenceScore >= step) {
			addedPoint = step;
			break;
		}
	}

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
	if (!file.is_open())return;

	for (int i = 0; i < MAX_STAGE_NUM; i++) {	// ファイルにハイスコアを書き込む
		file << highScore[i] << "\n";
	}

	file.close();
}