#pragma once
#include "Stage.h"

extern float jumpDistance;	// メモ　プレイヤークラスに入れる


class ScoreManager {
public:
	/// <summary> コンストラクタ </summary>
	ScoreManager() :viewScore(), score(), highScore() {}

	/// <summary> 加算するスコアを計算するメソッド </summary>
	/// <param name="moveSpeed"> プレイヤーの移動速度 </param>
	void AddScoreCalculate(float moveSpeed);

	/// <summary> 実スコアと表示スコアが一致するまで表示スコアに値を加算し続けるメソッド </summary>
	void AddViewScore();

	/// <summary> スコアがハイスコアを更新しているか確認するメソッド </summary>
	void CheckHighScore();

	/// <summary> ハイスコアをテキストファイルからロードするメソッド </summary>
	void LoadHighScore();

	/// <summary> ハイスコアをテキストファイルにセーブするメソッド </summary>
	void SaveHighScore();

	// private変数を読み取り専用で渡すメソッド群
	int GetViewScore(){ return viewScore; }
	int GetScore() { return score; }
	int GetHighScore(int num) { return highScore[num]; }

	void SetScore(int num) { score = num; }
	void SetViewScore(int num) { viewScore = num; }

	// 定数群
	const int ADD_SCORE_10 = 10;	// viewScoreに加算するスコアの値
	const int ADD_SCORE_100 = 100;	// viewScoreに加算するスコアの値
	const int ADD_SCORE_200 = 200;	// viewScoreに加算するスコアの値
private:
	int viewScore;	// ゲーム画面表示スコア
	int score;	// 内部保存スコア
	int highScore[MAX_STAGE_NUM];	// ハイスコア
};

extern ScoreManager scoreManager;