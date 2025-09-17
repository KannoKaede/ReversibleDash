#pragma once
// UIの制御に関する変数、関数をまとめたヘッダ

#ifndef INCLUDED_UI_h
#define INCLUDED_UI_h
/*UI描画関連--------------------------------------------------------------------------------------------------------------------*/

/// <summary> 画面の種類を定義する </summary>
enum SCREEN_TYPE
{
	TITLE,
	STAGESELECT,
	PAUSE,
	GAMEOVER,
	STAGECLEAR,
	SCREEN_BUTTON_NUM, // ボタンがある画面の数
	INGAME
};

/// <summary> 現在の画面の状態 </summary>
extern SCREEN_TYPE currentScreenType;

/// <summary> 次の画面の状態 </summary>
extern SCREEN_TYPE nextScreenType;

/// <summary> 画面の状態に対応したUIを表示するメソッド </summary>
void ScreenUISwithing();

/*フェード処理関連--------------------------------------------------------------------------------------------------------------------*/

/// <summary> 現在フェード中か </summary>
extern bool isFading;

/// <summary> フェード速度 </summary>
const int FADE_SPEED = 6;

/// <summary> 現在のフェードの状態：0=透明　255=黒 </summary>
extern int alphaValue;

/// <summary> フェードの待機開始タイミングを保存 </summary>
extern int fadeStartCount;

/// <summary> フェードの待機時間 </summary>
const int FADE_WAIT_TIME = 500;

/// <summary> フェードの状態を定義 </summary>
enum FADE_STATE {
	FADEOUT,
	FADEIN,
	FADEWAIT
};

/// <summary> 現在のフェードの状態 </summary>
extern FADE_STATE fadeState;

/// <summary> フェード演出の制御を行うメソッド：フェード演出中はFlagを立てて他の処理を制御 </summary>
void ScreenFadeControl();

/// <summary> フェード処理を行うメソッド </summary>
/// <param name="fadeSpeed"> フェード処理の速度 </param>
void ScreenFade(int fadeSpeed);

/*ボタン関連--------------------------------------------------------------------------------------------------------------------*/

/// <summary> ボタンマップの最大数：横 </summary>
const int BUTTON_NUM_X = 4;

/// <summary> ボタンを配置するマップの最大数：縦 </summary>
const int BUTTON_NUM_Y = 4;

/// <summary> ボタンが配置されているマップ：0 = ボタンなし・1 = ボタンあり・2 = ボタン選択中 </summary>
extern int buttonMap[SCREEN_BUTTON_NUM][BUTTON_NUM_Y][BUTTON_NUM_X];

/// <summary> 現在選択されているボタンの座標：横 </summary>
extern int buttonPosX;

/// <summary> 現在選択されているボタンの座標：縦 </summary>
extern int buttonPosY;

/// <summary> ボタンが移動してから次に移動できるまでの待機時間 </summary>
const int WAIT_BUTTON_MOVE = 20;

/// <summary> ボタンの選択位置を変更するメソッド </summary>
void ButtonChanged();

/// <summary> ボタンが押されたときの処理を行うメソッド </summary>
void CheckButtonPressed();

/// <summary>
/// ボタンが押された際の共通処理
/// </summary>
/// <param name="nextScreen"> 次の画面</param>
/// <param name="buttonScreen"> ボタンを押した画面</param>
/// <param name="y"> ボタンの座標Y</param>
/// <param name="x"> ボタンの座標X</param>
/// <param name="isFade"> true = フェード処理を行う false = 即座に切り替える</param>
void ButtonPressedProcessing(SCREEN_TYPE nextScreen, SCREEN_TYPE buttonScreen, int y, int x, bool isFade);

/*フォント関連--------------------------------------------------------------------------------------------------------------------*/

extern int bigFontHandle;

extern int normalFontHandle;

extern int smallFontHandle;
#endif