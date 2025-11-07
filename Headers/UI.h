#pragma once
#include "DxLib.h"
#include "Player.h"
#include <string>

// タイトルシーンの描画処理を行うクラス
class TitleScene {
public:
	/// <summary> タイトルのUIを描画するクラス </summary>
	void Draw();
};

// ステージセレクトシーンの描画処理を行うクラス
class StageSelectScene {
public:
	/// <summary> ステージセレクトのUIを描画するクラス </summary>
	void Draw();
};

// ポーズシーンの描画処理を行うクラス
class PauseScene {
public:
	/// <summary> ポーズのUIを描画するクラス </summary>
	void Draw(Player player);
};

// インゲームシーンの描画処理を行うクラス
class InGameScene {
public:
	/// <summary> インゲームのUIを描画するクラス </summary>
	void Draw(Player player);
};

// ゲームオーバーシーンの描画処理を行うクラス
class GameOverScene {
public:
	/// <summary> ゲームオーバーのUIを描画するクラス </summary>
	void Draw();
};

// クリアシーンの描画処理を行うクラス
class ClearScene {
public:
	/// <summary> クリアのUIを描画するクラス </summary>
	void Draw();
};

enum SCREEN_TYPE	// 画面の状態を定義
{
	TITLE,	// タイトル
	STAGESELECT,	// ステージセレクト
	PAUSE,	// ポーズ
	GAMEOVER,	// ゲームオーバー
	CLEAR,	// クリア
	INGAME	// ゲーム中
};

class UIManager {
public:
	/// <summary> コンストラクタ </summary>
	UIManager() :currentScreen(), nextScreen(), keyWASD(), keySpace(), keyEscape() {}
	/// <summary> コンストラクタではできない初期化処理を行うメソッド </summary>
	void SetUp();

	/// <summary> 画面にあったUIを描画するメソッド </summary>
	/// <param name="player"> プレイヤーのインスタンス </param>
	void DrawUI(Player player);

	void DrawStartCountDown();

	/// <summary> ゲーム進捗率を描画するメソッド </summary>
	/// <param name="player"> プレイヤーのインスタンス </param>
	/// <param name="startPos"> バーの左端座標 </param>
	/// <param name="endPos"> バーの右端座標 </param>
	/// <param name="heightPos"> 描画するスクリーン座標Y（％） </param>
	void DrawProgressRateBar(const Player& player, float startPct, float endPct, float heightct);

	struct ImageData {	// 画像データ構造体
		int image;	// 画像ハンドル
		int width;	// 画像の幅
		int height;	// 画像の高さ
	};
	/// <summary> テキストを中央に描画するメソッド </summary>
	/// <param name="left"> 左端の座標 </param>
	/// <param name="top"> 上端の座標 </param>
	/// <param name="right"> 右端の座標 </param>
	/// <param name="bottom"> 下端の座標 </param>
	/// <param name="text"> 描画するテキスト </param>
	/// <param name="fontType"> どのフォントを使用するか </param>
	void DrawStringCenter(float left, float top, float right, float bottom, std::string text, int fontType);


	/// <summary> テキストを描画するメソッド：rightをleftの値より小さくしたらleftの位置で描画する。大きい場合は指定の枠の左右中央に描画 </summary>
	/// <param name="leftPct"> 左端の座標（％） </param>
	/// <param name="rightPct"> 右端の座標（％） </param>
	/// <param name="heightPct"> Y軸の描画座標（％） </param>
	/// <param name="text"> 描画するテキスト </param>
	/// <param name="font"> 使用するフォント </param>
	void DrawString(float leftPct, float rightPct, float heightPct, std::string text, int font);

	/// <summary> 画像を描画するメソッド </summary>
	/// <param name="leftPct"> 画像描画時の左上の座標X </param>
	/// <param name="topPct"> 画像描画時の左上の座標Y </param>
	/// <param name="image"> 画像のハンドル、幅高さが格納されている構造体 </param>
	void DrawImage(float leftPct, float topPct, ImageData image);


	/// <summary> 現在の画面が指定の画面と等しいかを返すメソッド </summary>
	/// <param name="screen"> 指定の画面 </param>
	/// <returns> 現在の画面と指定の画面が等しいか </returns>
	bool IsEqualCurrenScreen(SCREEN_TYPE screen) { return currentScreen == screen; }

	ImageData GetImageDASD() { return keyWASD; }
	ImageData GetImageSpace() { return keySpace; }
	ImageData GetImageEscape() { return keyEscape; }
	SCREEN_TYPE GetCurrentScreen() { return currentScreen; }
	SCREEN_TYPE GetNextScreen() { return nextScreen; }

	void SetCurrentScreen(SCREEN_TYPE current) { currentScreen = current; }
	void SetNextScreen(SCREEN_TYPE next) { nextScreen = next; }
	void SetIsStartCountDown(bool state) { isStartCountDown = state; }
private:
	SCREEN_TYPE currentScreen;	// 現在の画面の状態
	SCREEN_TYPE nextScreen;	// 次の画面の状態
	// 画像データ群
	ImageData keyWASD;
	ImageData keySpace;
	ImageData keyEscape;

	// 描画するシーン群
	TitleScene titleScene;
	StageSelectScene stageSelectScene;
	PauseScene pauseScene;
	InGameScene inGameScene;
	GameOverScene gameOverScene;
	ClearScene clearScene;

	int startTime = 0;	// 待機を開始したタイミングを保持
	int waitTime = 0;	// 何秒待機するかの値
	int drawCount = 0;	// 描画する文字のカウント
	const int START_WAITTIME[2] = { 1000,1000 };	// 待機時間
	const std::string DRAW_TEXT[2] = {"READY..." ,"GO!!!"};	// 描画する文字
	const int TEXT_FADE_SPEED[2][2] = { { 30,-5 }, { 30,-10 } };	// 文字をフェードさせるスピード
	int textFadeSpeed = 0;	// 文字のalpha値を変更するための変数
	bool isFadeStart = true;	// 文字のフェードが始めか終わりかの判定
	bool isStartCountDown = true;	// スタートカウントダウンの描画が終了しているか
};

extern UIManager uiManager;


class FadeManager {
public:
	FadeManager() :fadeState(FADEIN), isFading(true), alphaValue(255), fadeStartCount() {}

	enum FADE_STATE {	// フェードの状態を定義
		FADEOUT,	// フェードアウト
		FADEIN,		// フェードイン
		FADEWAIT,	// フェード待機
		NOTFADE,	// 画面切り替え
		NONE,	// 何もしない
	};
	/// <summary> 描画する座標を変更するメソッド </summary>
	/// <param name="screen"> 次に表示するUI </param>
	/// <param name="fade"> フェードの状態を設定 </param>
	void ChangeUIState(SCREEN_TYPE screen, FADE_STATE fade);

	/// <summary> フェード処理を管理するメソッド </summary>
	void DrawFadeController();

	/// <summary> フェード処理を行うメソッド </summary>
	/// <param name="fadeSpeed"> フェード処理の速度 </param>
	void DrawFade(int fadeSpeed);

	void DrawTextFade(std::string text, int font, int value);

	/// <summary> 画面切り替えをする際に座標やデータを初期化するメソッド </summary>
	void ChangeScene();

	bool GetIsFading() { return isFading; }
	int GetAlphaValue() { return alphaValue; }
private:
	const int FADE_SPEED = 6;	// フェード速度
	const int FADE_WAIT_TIME = 500;	// フェードの待機時間
	FADE_STATE fadeState;	// 現在のフェードの状態
	bool isFading;
	int alphaValue;	// フェードのα値
	int fadeStartCount;	// フェードの待機開始タイミングを保存
	

};
extern FadeManager fadeManager;