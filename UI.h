#pragma once
#include <string>
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

/// <summary> 画面の状態に対応したUIを毎フレーム表示するメソッド </summary>
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
	FADEWAIT,
	NONE
};

/// <summary> 現在のフェードの状態 </summary>
extern FADE_STATE fadeState;

/// <summary> フェード演出の制御を行うメソッド：フェード演出中はFlagを立てて他の処理を制御 </summary>
void ScreenFadeControl();

/// <summary> フェード処理を行うメソッド </summary>
/// <param name="fadeSpeed"> フェード処理の速度 </param>
void ScreenFade(int fadeSpeed);

/// <summary> 画面比率に合わせた計算 
/// <param name="x"> 100%で表した座標の比率 </param>
/// <returns> 画面解像度に応じた値</returns>
int DrawPositionX(int x);

/// <summary> 画面比率に合わせた計算 
/// <param name="x"> 100%で表した座標の比率 </param>
/// <returns> 画面解像度に応じた値</returns>
int DrawPositionY(int y);

/// <summary> ボタン用の図形を描画 </summary>
/// <param name="loopY">何回ループするかfor外側</param>
/// <param name="loopX">何回ループするかfor内側</param>
/// <param name="topLeft">描画する図形の左上の座標</param>
/// <param name="lengthX">図形の横幅</param>
/// <param name="lengthY">図形の縦幅</param>
/// <param name="plusX">二個目の図形の位置を横にずらす値</param>
/// <param name="plusY">二個目の図形の位置を縦にずらす値</param>
/// <param name="screen">画面の種類</param>
/// <param name="isSquare">四角形か三角形を描画するかのフラグ:true=四角形</param>
void SquareTest(int loopY, int loopX, VECTOR topLeft, int lengthX, int lengthY, int plusX, int plusY, SCREEN_TYPE screen, bool isSquare);

/// <summary> 指定の枠の中央に文字を描画する </summary>
/// <param name="drawText"> 描画する文字列 </param>
/// <param name="boxLeftPos"> 指定の枠の左座標 </param>
/// <param name="boxRightPos"> 指定の枠の右座標 </param>
/// <param name="drawPosY"> 描画する際の縦座標 </param>
/// <param name="font"> 使用するフォント </param>
/// <param name="isNum"> 数字を使用するか：true = 数字を使用 </param>
/// <param name="num"> 使用する数字 </param>
void StringTest(std::string drawText, int boxLeftPos, int boxRightPos, int drawPosY, int font, bool isNum, int num);

/*ボタン関連--------------------------------------------------------------------------------------------------------------------*/

/// <summary> 背景枠の色 </summary>
extern int  backScreen;

/// <summary> ボタン選択状態の色 </summary>
extern int gray;

/// <summary> ボタン非選択状態の色 </summary>
extern int green;

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
void ButtonPressedProcessing(SCREEN_TYPE nextScreen, bool isFade);

/*フォント関連--------------------------------------------------------------------------------------------------------------------*/

/// <summary> フォントの色 </summary>
extern int brack;

/// <summary> フォントサイズ大 </summary>
extern int bigFontHandle;

/// <summary> フォントサイズ中 </summary>
extern int normalFontHandle;

/// <summary> フォントサイズ小 </summary>
extern int smallFontHandle;
/// <summary> フォントのロードを行う関数 </summary>
void fontSetting();

/*常時描画しないUI関連--------------------------------------------------------------------------------------------------------------------*/

/// <summary> 描画文字が変更されたか確認する </summary>

extern std::string previousText;
/// <summary> 描画する文字 </summary>

extern std::string drawText;
/// <summary> スタートカウントダウンの文字の中身：最初 </summary>

const std::string START_COUNTDOWN_1 = "READY...";
/// <summary> スタートカウントダウンの文字の中身：最後 </summary>

const std::string START_COUNTDOWN_2 = "GO!";
/// <summary> スタートカウントダウンの描画を行うメソッド </summary>
void DrawStartCountDown();
#endif