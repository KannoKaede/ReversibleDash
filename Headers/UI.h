#pragma once
#include "DxLib.h"
#include "Player.h"
#include <string>

enum SCREEN_TYPE	// 画面の状態を定義
{
	TITLE,			// タイトル
	STAGESELECT,	// ステージセレクト
	PAUSE,			// ポーズ
	GAMEOVER,		// ゲームオーバー
	STAGECLEAR,		// ステージクリア（最後のステージ意外）
	GAMECLEAR,		// ステージクリア（最後のステージ）
	BUTTON_NUM,		// ボタンがある画面の数
	INGAME,			// ゲーム中
	EXPLANATION		// ゲームの仕様等を開設する画面
};

enum FADE_STATE {	// フェードの状態を定義
	FADEOUT,	// フェードアウト
	FADEIN,		// フェードイン
	FADEWAIT,	// フェード待機
	NOTFADE,	// 画面切り替え
	NONE,	// 何もしない
};

struct ImageData {	// 画像データ構造体
	int image;	// 画像ハンドル
	int width;	// 画像の幅
	int height;	// 画像の高さ
};

// タイトルシーンの描画処理を行うクラス
class TitleScene {
public:
	/// <summary> タイトルのUIを描画 </summary>
	void Draw();
};

// ステージセレクトシーンの描画処理を行うクラス
class StageSelectScene {
public:
	/// <summary> ステージセレクトのUIを描画 </summary>
	void Draw();
};

// ポーズシーンの描画処理を行うクラス
class PauseScene {
public:
	/// <summary> ポーズのUIを描画 </summary>
	void Draw(Player& _player);
};

// インゲームシーンの描画処理を行うクラス
class InGameScene {
public:
	/// <summary> インゲームのUIを描画 </summary>
	void Draw(Player& _player);
};

// ゲームオーバーシーンの描画処理を行うクラス
class GameOverScene {
public:
	/// <summary> ゲームオーバーのUIを描画 </summary>
	void Draw();
};

// クリアシーンの描画処理を行うクラス
class ClearScene {
public:
	/// <summary> クリアのUIを描画 </summary>
	void Draw();
};

// ゲームの仕様等の説明の描画処理を行うクラス
class  ExceptionScene {
public:
	/// <summary> ゲームの仕様を描画 </summary>
	void Draw();
private:
	int currentPage;	// 表示しているページ
};


class UIManager {
public:
	/// <summary> コンストラクタ </summary>
	UIManager() :currentScreen(), nextScreen(), keyWASD(), keySpace(), keyEscape() {}

	/// <summary> コンストラクタではできない初期化処理を行うメソッド </summary>
	void			SetUp();

	/// <summary> 画面にあったUIを描画する </summary>
	/// <param name="player"> プレイヤーのインスタンス </param>
	void			DrawUI(Player& _player);

	void			DrawStartCountDown();

	/// <summary> ゲーム進捗率を描画する </summary>
	void			DrawProgressRateBar(const Player& player, float startPct, float endPct, float heightPct);

	/// <summary>  ジャンプボタンを押している時間をゲージで描画する </summary>
	void			DrawJumpPct(int _pressedJump);

	/// <summary> テキストを中央に描画するメソッド </summary>
	/// <param name="fontType"> 使用するフォントの配列の要素数 </param>
	void			DrawStringCenter(float left, float top, float right, float bottom, std::string text, int fontType);

	/// <summary> テキストを描画：RightをLeftの値より小さくしたらLeftの位置で描画する。大きい場合は指定の枠の左右中央に描画 </summary>
	void			DrawString(float leftPct, float rightPct, float heightPct, std::string text, int font);

	/// <summary> 画像を描画 </summary>
	void			DrawImage(float leftPct, float topPct, ImageData image);

	/// <summary> 角を丸くした長方形を描画 </summary>
	void			DrawRoundRect(float _topPct, float _bottomPct, float _leftPct, float _rightPct, float _radiusPct, int _color);

	/// <summary> 現在の画面が指定の画面と等しいかを返す </summary>
	bool			CheckScreen(SCREEN_TYPE screen)			{ return currentScreen == screen; }

	/// <summary> WASDの画像を返す </summary>
	ImageData		GetImageWASD()							{ return keyWASD; }
	/// <summary> Spaceの画像を返す </summary>
	ImageData		GetImageSpace()							{ return keySpace; }
	/// <summary> Escapeの画像を返す </summary>
	ImageData		GetImageEscape()						{ return keyEscape; }
	/// <summary> 現在の画面の状態を返す </summary>
	SCREEN_TYPE		GetCurrentScreen()						{ return currentScreen; }
	/// <summary> 次の画面の状態を返す </summary>
	SCREEN_TYPE		GetNextScreen()							{ return nextScreen; }
	/// <summary> 現在スタートカウントダウンを行っているか返す </summary>
	bool			GetIsStartCountDown()					{ return isStartCountDown; }

	/// <summary> 現在の画面情報を設定 </summary>
	void			SetCurrentScreen(SCREEN_TYPE current)	{ currentScreen = current; }
	/// <summary> 次の画面情報を設定 </summary>
	void			SetNextScreen(SCREEN_TYPE next)			{ nextScreen = next; }
	/// <summary> スタートカウントダウンを行うかの設定 </summary>
	void			SetIsStartCountDown(bool state)			{ isStartCountDown = state; }
private:
	SCREEN_TYPE				currentScreen;	// 現在の画面の状態
	SCREEN_TYPE				nextScreen;		// 次の画面の状態

	// 画像データ群
	ImageData				keyWASD;
	ImageData				keySpace;
	ImageData				keyEscape;

	// 描画するシーン群
	TitleScene				titleScene;
	StageSelectScene		stageSelectScene;
	PauseScene				pauseScene;
	InGameScene				inGameScene;
	GameOverScene			gameOverScene;
	ClearScene				clearScene;
	ExceptionScene			exceptionScene;

	int						startTime = 0;		// 待機を開始したタイミングを保持
	int						waitTime = 0;		// 何秒待機するかの値
	int						drawCount = 0;		// 描画する文字のカウント

	int						textFadeSpeed = 0;	// 文字のalpha値を変更するための変数
	bool					isFadeStart = true;	// 文字のフェードが始めか終わりかの判定
	bool					isStartCountDown = true;	// スタートカウントダウンの描画が終了しているか


	static constexpr int	START_WAITTIME[2] = { 1000,1000 };	// 待機時間
	const std::string		DRAW_TEXT[2] = {"READY..." ,"GO!!!"};	// 描画する文字
	static constexpr int	TEXT_FADE_SPEED[2][2] = { { 30,-5 }, { 30,-10 } };	// 文字をフェードさせるスピード
};

extern UIManager uiManager;


class FadeManager {
public:
	/// <summary> コンストラクタ </summary>
	FadeManager() :fadeState(FADEIN), isFading(true), alphaValue(255), fadeStartCount() {}

	/// <summary> 描画する画面を変更 </summary>
	void ChangeUIState(SCREEN_TYPE _screen, FADE_STATE _fade);

	/// <summary> フェード処理を管理 </summary>
	void DrawFadeController();

	/// <summary> フェード処理を行う </summary>
	void DrawFade(int _fadeSpeed);

	void DrawTextFade(std::string _text, int _font, int _value);

	/// <summary> 画面切り替えをする際に座標やデータを初期化 </summary>
	void ChangeScene();

	/// <summary> フェード中かを返す </summary>
	bool GetIsFading()	{ return isFading; }
	/// <summary> 現在のα値を返す </summary>
	int GetAlphaValue() { return alphaValue; }
private:
	FADE_STATE	fadeState;			// 現在のフェードの状態
	bool		isFading;			// フェード中か判定
	int			alphaValue;			// フェードのα値
	int			fadeStartCount;		// フェードの待機開始タイミングを保存
	
	static constexpr	int FADE_SPEED = 6;			// フェード速度
	static constexpr	int FADE_WAIT_TIME = 500;	// フェードの待機時間
};
extern FadeManager fadeManager;