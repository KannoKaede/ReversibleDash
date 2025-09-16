#pragma once
// UIの制御に関する変数、関数をまとめたヘッダ

/*--------------------------------------------------------------------------------------------------------------------*/
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
__declspec(selectany) SCREEN_TYPE currentScreenType = TITLE;

/// <summary> 次の画面の状態 </summary>
__declspec(selectany) SCREEN_TYPE nextScreenType = TITLE;

/// <summary> 画面の状態に対応したUIを表示するメソッド </summary>
void ScreenUISwithing();

/*フェード処理関連--------------------------------------------------------------------------------------------------------------------*/

/// <summary> 現在フェード中か </summary>
__declspec(selectany) bool isFading = true;

/// <summary> フェード速度 </summary>
const int FADE_SPEED = 6;

/// <summary> 現在のフェードの状態：0=透明　255=黒 </summary>
__declspec(selectany) int alphaValue = 255;

/// <summary> フェードの待機開始タイミングを保存 </summary>
__declspec(selectany) int fadeStartCount = 0;

/// <summary> フェードの待機時間 </summary>
const int FADE_WAIT_TIME = 500;

/// <summary> フェードの状態を定義 </summary>
enum FADE_STATE {
	FADEOUT,
	FADEIN,
	FADEWAIT
};

/// <summary> 現在のフェードの状態 </summary>
__declspec(selectany) FADE_STATE fadeState = FADEOUT;

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
__declspec(selectany) int buttonMap[SCREEN_BUTTON_NUM][BUTTON_NUM_Y][BUTTON_NUM_X] = {
	{	// TITLE
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{0,0,0,0}
	},
	{	// STAGESELECT
		{1,1,1,0},
		{1,1,1,0},
		{1,1,1,1},
		{0,0,0,0}
	},
	{	// PAUSE
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	},
	{	// GAMEOVER
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	},
	{	// STAGECLEAR
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	}
};

/// <summary> 現在選択されているボタンの座標：横 </summary>
__declspec(selectany) int buttonPosX = 0;

/// <summary> 現在選択されているボタンの座標：縦 </summary>
__declspec(selectany) int buttonPosY = 0;

/// <summary> ボタンが移動してから次に移動できるまでの待機時間 </summary>
const int WAIT_BUTTON_MOVE = 20;

/// <summary> ボタンの選択位置を変更するメソッド </summary>
void ButtonChanged();

/// <summary> ボタンが押されたときの処理を行うメソッド </summary>
void OnClickSwitchUI();
