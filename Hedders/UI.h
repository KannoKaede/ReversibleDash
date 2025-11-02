#pragma once
#include <string>
#include "DxLib.h"
#include "Player.h"

constexpr int FADE_SPEED = 6;	// フェード速度
constexpr int FADE_WAIT_TIME = 500;	// フェードの待機時間
const std::string START_COUNTDOWN_1 = "READY...";	// スタートカウントダウンの文字の中身：最初
const std::string START_COUNTDOWN_2 = "GO!";	// スタートカウントダウンの文字の中身：最後

enum SCREEN_TYPE	// 画面の状態を定義
{
	TITLE,	// タイトル
	STAGESELECT,	// ステージセレクト
	PAUSE,	// ポーズ
	GAMEOVER,	// ゲームオーバー
	CLEAR,	// クリア
	INGAME	// ゲーム中
};
extern SCREEN_TYPE currentScreenType;	// 現在の画面の状態
extern SCREEN_TYPE nextScreenType;	// 次の画面の状態

/// <summary> UIの初期設定を行うメソッド </summary>
void UISetUp();

/// <summary> 画面の状態に対応したUIを毎フレーム表示するメソッド </summary>
/// <param name="player"> プレイヤーのインスタンス </param>
void DrawUI(Player player);

extern bool isFading;	// フェード中かどうか
extern int alphaValue;	// フェードのα値
extern int fadeStartCount;	// フェードの待機開始タイミングを保存

enum FADE_STATE {	// フェードの状態を定義
	FADEOUT,	// フェードアウト
	FADEIN,		// フェードイン
	SCREENSETUP,	// 画面切り替え
	FADEWAIT,	// フェード待機
	NONE	// 何もしない
};
extern FADE_STATE fadeState;	// 現在のフェードの状態

struct ImageData {	// 画像データ構造体
	int image;	// 画像ハンドル
	int width;	// 画像の幅
	int height;	// 画像の高さ
};
extern ImageData keyWASD;	//WASDキー画像データ
extern ImageData keySpace;	//スペースキー画像データ
extern ImageData keyEscape;	//エスケープキー画像データ

/// <summary> フェード演出の制御を行うメソッド </summary>
bool ScreenFadeControl();

/// <summary> フェード処理を行うメソッド </summary>
/// <param name="fadeSpeed"> フェード処理の速度 </param>
void ScreenFade(int fadeSpeed);

/// <summary> 都度リセットする必要があるものをリセットするメソッド </summary>
void SystemReset();

extern std::string previousText;	// 前回描画していた文字

extern std::string drawText;	// 描画する文字

/// <summary> スタートカウントダウンの描画を行うメソッド </summary>
void DrawStartCountDown();

/// <summary> ゲーム進捗率を描画するメソッド </summary>
/// <param name="player"> プレイヤーのインスタンス </param>
/// <param name="startPos"> バーの左端座標 </param>
/// <param name="endPos"> バーの右端座標 </param>
/// <param name="heightPos"> 描画するスクリーン座標Y（％） </param>
void DrawProgressRateBar(const Player& player, float startPos, float endPos, float heightPos);

/// <summary> テキストを中央に描画するメソッド </summary>
/// <param name="left"> 左端の座標 </param>
/// <param name="top"> 上端の座標 </param>
/// <param name="right"> 右端の座標 </param>
/// <param name="bottom"> 下端の座標 </param>
/// <param name="text"> 描画するテキスト </param>
/// <param name="fontType"> どのフォントを使用するか </param>
void DrawTextCenter(float left, float top, float right, float bottom, std::string text, int fontType);

/// <summary> テキストを描画するメソッド：rightをleftの値より小さくしたらleftの位置で描画する。大きい場合は指定の枠の左右中央に描画 </summary>
/// <param name="leftPct"> 左端の座標（％） </param>
/// <param name="rightPct"> 右端の座標（％） </param>
/// <param name="heightPct"> Y軸の描画座標（％） </param>
/// <param name="text"> 描画するテキスト </param>
/// <param name="font"> 使用するフォント </param>
void DrawTextString(float leftPct, float rightPct, float heightPct, std::string text, int font);

/// <summary> テキストを描画するメソッド：rightをleftの値より小さくしたらleftの位置で描画する。大きい場合は指定の枠の左右中央に描画 </summary>
/// <param name="leftPct"> 左端の座標（％） </param>
/// <param name="rightPct"> 右端の座標（％） </param>
/// <param name="heightPct"> Y軸の描画座標（％） </param>
/// <param name="text"> 描画するテキスト </param>
/// <param name="font"> 使用するフォント </param>
/// /// <param name="font"> 使用するフォント </param>
void DrawTextInt(float leftPct, float rightPct, float heightPct, std::string text, int font, int num);

/// <summary> 画像を描画するメソッド </summary>
/// <param name="leftPct"> 画像描画時の左上の座標X </param>
/// <param name="topPct"> 画像描画時の左上の座標Y </param>
/// <param name="image"> 画像のハンドル、幅高さが格納されている構造体 </param>
void DrawImage(float leftPct, float topPct, ImageData image);

/// <summary> 描画する座標を変更するメソッド </summary>
/// <param name="screen"> 次に表示するUI </param>
/// <param name="fade"> フェードの状態を設定 </param>
void ChangeUIState(SCREEN_TYPE screen,FADE_STATE fade);
