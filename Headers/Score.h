#pragma once
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


/// <summary> ハイスコアをロードするメソッド </summary>
void LoadHighScore();
/// <summary> ハイスコアをセーブするメソッド </summary>
void SaveHighScore();

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