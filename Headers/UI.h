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
	FADE_NONE,	// 何もしない
};

enum ROUNDRECT_ANGLE {	// 角の丸い長方形の中で角が丸くない部分を定義
	ANGLE_NONE,
	LEFTTOP,
	LEFTBOTTOM,
	RIGHTTOP,
	RIGHTBOTTOM,
	LEFTRIGHTTOP,
	RIGHTTOP_LEFTRIGHTBOTTOM,
	LEFTTOP_LEFTRIGHTBOTTOM,
	ANGLE_ALL
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
class  ExplanationScene {
public:
	/// <summary> ゲームの仕様を描画 </summary>
	void Draw();
	
	/// <summary> 表示するページを設定 </summary>
	void SetCurrentPage(int _currentPage) { currentPage = _currentPage; }
private:
	int currentPage;	// 表示しているページ
};


class UIManager {
public:
	/// <summary> コンストラクタ </summary>
	UIManager() :currentScreen(), nextScreen(), keyWASD(), keySpace(), keyEscape(), explanations{}, carWindow(),titleCarWindow() {}

	/// <summary> コンストラクタではできない初期化処理を行うメソッド </summary>
	void			SetUp();

	/// <summary> 画面にあったUIを描画する </summary>
	void			DrawUI(Player& _player);

	/// <summary> ゲーム開始のカウントダウンを描画する </summary>
	void			DrawStartCountDown();

	/// <summary> ゲーム進捗率を描画する </summary>
	void			DrawProgressRateBar(const Player& player, float startPct, float endPct, float heightPct);

	/// <summary>  ジャンプボタンを押している時間をゲージで描画する </summary>
	void			DrawJumpPct(int _pressedJump, float _jumpHeightPct, bool _isFall);

	/// <summary> テキストを中央に描画するメソッド </summary>
	/// <param name="fontType"> 使用するフォントの配列の要素数 </param>
	void			DrawStringCenter(float left, float top, float right, float bottom, std::string text, int fontType);

	/// <summary> テキストを描画：RightをLeftの値より小さくしたらLeftの位置で描画する。大きい場合は指定の枠の左右中央に描画 </summary>
	void			DrawString(float _leftPct, float _rightPct, float _heightPct, std::string _text, int _font, int _color);

	/// <summary> 画像を描画 </summary>
	void			DrawImage(float leftPct, float topPct, ImageData image);

	/// <summary> 角を丸くした長方形を描画 </summary>
	/// <param name="_angle"> 角を丸くしない箇所を指定 </param>
	void			DrawRoundRect(float _topPct, float _bottomPct, float _leftPct, float _rightPct, float _radiusPct, int _color, ROUNDRECT_ANGLE _angle);

	/// <summary> 現在の画面が指定の画面と等しいかを返す </summary>
	bool			CheckScreen(SCREEN_TYPE screen)			{ return currentScreen == screen; }

	/// <summary> WASDの画像を返す </summary>
	ImageData		GetImageWASD()const						{ return keyWASD; }
	/// <summary> Spaceの画像を返す </summary>
	ImageData		GetImageSpace()const					{ return keySpace; }
	/// <summary> Escapeの画像を返す </summary>
	ImageData		GetImageEscape()const					{ return keyEscape; }
	/// <summary> 説明に使用する画像を返す </summary>
	ImageData		GetExplanations(int number)				{ return explanations[number]; }
	/// <summary> 車の窓の画像を返す </summary>
	ImageData		GetCarWindow()const						{ return carWindow; }
	/// <summary> タイトル背景画像を返す </summary>
	ImageData		GetTitleCarWindow()const				{ return titleCarWindow; }
	/// <summary> 空の画像を返す </summary>
	ImageData		GetSkyImage()const						{ return skyImage; }
	/// <summary> 現在の画面の状態を返す </summary>
	SCREEN_TYPE		GetCurrentScreen()const					{ return currentScreen; }
	/// <summary> 次の画面の状態を返す </summary>
	SCREEN_TYPE		GetNextScreen()const					{ return nextScreen; }
	/// <summary> 現在スタートカウントダウンを行っているか返す </summary>
	bool			GetIsStartCountDown()const				{ return isStartCountDown; }

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
	ImageData				explanations[8];
	ImageData				carWindow;
	ImageData				titleCarWindow;
	ImageData				skyImage;
	ImageData				runImage[2];
	ImageData				jumpImage[2];

	// 描画するシーン群
	TitleScene				titleScene;
	StageSelectScene		stageSelectScene;
	PauseScene				pauseScene;
	InGameScene				inGameScene;
	GameOverScene			gameOverScene;
	ClearScene				clearScene;
	ExplanationScene		explanationScene;

	int						startTime = 0;		// 待機を開始したタイミングを保持
	int						drawCount = 0;		// 描画する文字のカウント
	bool					isFadeOut = true;	// 文字のフェードが始めか終わりかの判定
	bool					isStartCountDown = true;	// スタートカウントダウンの描画が終了しているか


	static constexpr int	WAITTIME[2] = { 1000,200 };	// 待機時間
	const std::string		DRAW_TEXT[2] = {"READY..." ,"GO!!!"};	// 描画する文字
	static constexpr int	TEXT_FADE_SPEED[2] = { 30,-5 };	// 文字をフェードさせるスピード
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

	/// <summary> テキストのフェード処理を行う </summary>
	void DrawTextFade(std::string _text, int _fontType, int _value);

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