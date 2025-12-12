#pragma once
#include "Stage.h"
#include "Player.h"

class ScoreManager {
public:
	/// <summary> コンストラクタ </summary>
	ScoreManager() :viewScore(), score(), highScore{} {}

	/// <summary> 加算するスコアを計算 </summary>
	void	AddScoreCalculate(float _jumpDis, float _moveSpeed);

	/// <summary> 実スコアと表示スコアが一致するまで表示スコアに値を加算し続ける </summary>
	void	AddViewScore();

	/// <summary> スコアがハイスコアを更新しているか確認 </summary>
	void	CheckHighScore();

	/// <summary> ハイスコアをテキストファイルからロード </summary>
	void	LoadHighScore();

	/// <summary> ハイスコアをテキストファイルにセーブ </summary>
	void	SaveHighScore();

	/// <summary> スコアをリセットする </summary>
	void	Initialization();

	/// <summary> 表示スコアを返す </summary>
	int		GetViewScore()const			{ return viewScore; }
	/// <summary> 実スコアを返す </summary>
	int		GetScore()const				{ return score; }
	/// <summary> ステージのハイスコアを返す </summary>
	int		GetHighScore(int _stageNumber)const	{ return highScore[_stageNumber]; }
private:
	int		viewScore;					// ゲーム画面表示スコア
	int		score;						// 内部保存スコア
	int		highScore[MAX_STAGE_NUM];	// ハイスコア
	const std::vector<int> scoreSteps = { 200, 100, 10 };	// ViewSoreに加算する値
};

extern ScoreManager scoreManager;