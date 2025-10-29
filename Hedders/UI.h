#pragma once
#include <string>
#include "DxLib.h"
#include "Player.h"

const int COLOR_WHITEGRAY = GetColor(230, 230, 230);
const int COLOR_GRAY = GetColor(200, 200, 200);
const int COLOR_GREEN = GetColor(0, 255, 128);
const int COLOR_BLACK = GetColor(0, 0, 0);

constexpr int FADE_SPEED = 6;	// フェード速度
constexpr int FADE_WAIT_TIME = 500;	// フェードの待機時間

const std::string START_COUNTDOWN_1 = "READY...";	// スタートカウントダウンの文字の中身：最初
const std::string START_COUNTDOWN_2 = "GO!";	// スタートカウントダウンの文字の中身：最後

#define KEYIMAGE_LENGTH 54

void UISetUp();
/// <summary> 画面の種類を定義する </summary>
enum SCREEN_TYPE
{
	TITLE,
	STAGESELECT,
	PAUSE,
	GAMEOVER,
	CLEAR,
	INGAME
};

/// <summary> 現在の画面の状態 </summary>
extern SCREEN_TYPE currentScreenType;

/// <summary> 次の画面の状態 </summary>
extern SCREEN_TYPE nextScreenType;

/// <summary> 画面の状態に対応したUIを毎フレーム表示するメソッド </summary>
void DrawUI(Player player);

/*フェード処理関連--------------------------------------------------------------------------------------------------------------------*/

/// <summary> 現在フェード中か </summary>
extern bool isFading;

/// <summary> 現在のフェードの状態：0=透明　255=黒 </summary>
extern int alphaValue;

/// <summary> フェードの待機開始タイミングを保存 </summary>
extern int fadeStartCount;

/// <summary> フェードの状態を定義 </summary>
enum FADE_STATE {
	FADEOUT,
	FADEIN,
	SCREENSETUP,
	FADEWAIT,
	NONE
};

struct ImageData {
	int image;
	int width;
	int height;
};
extern ImageData keyWASD;
extern ImageData keySpace;
extern ImageData keyEscape;

/// <summary> 現在のフェードの状態 </summary>
extern FADE_STATE fadeState;

/// <summary> フェード演出の制御を行うメソッド：フェード演出中はFlagを立てて他の処理を制御 </summary>
bool ScreenFadeControl();

/// <summary> フェード処理を行うメソッド </summary>
/// <param name="fadeSpeed"> フェード処理の速度 </param>
void ScreenFade(int fadeSpeed);

/// <summary> 都度リセットする必要があるものをリセットするメソッド </summary>
void SystemReset();


/*常時描画しないUI関連--------------------------------------------------------------------------------------------------------------------*/

/// <summary> 描画文字が変更されたか確認する </summary>
extern std::string previousText;

/// <summary> 描画する文字 </summary>
extern std::string drawText;

/// <summary> スタートカウントダウンの描画を行うメソッド </summary>
void DrawStartCountDown();


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

void DrawImage(float leftPct, float topPct, ImageData image);
