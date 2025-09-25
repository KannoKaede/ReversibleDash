#pragma once
#include "UI.h"		// 画面の状態を取得用
#include <vector>
#include "main.h"	// 画面サイズ取得用
#ifndef Button_h
#define Button_h

class Button {
public:
	enum BUTTON_TYPE {
		GAMESTART,  // ゲーム開始
		OPENSTAGESELECT,    // ステージセレクトを開く
		GAMEQUIT,   // exe終了
		SELECTSTAGE1,   // ステージ選択
		SELECTSTAGE2,   // ステージ選択
		SELECTSTAGE3,   // ステージ選択
		SELECTSTAGE4,   // ステージ選択
		SELECTSTAGE5,   // ステージ選択
		SELECTSTAGE6,   // ステージ選択
		RESUME,	// ゲーム再開
		GAMEEXIT,	// インゲーム終了
		RETRY,	// リトライ
		NEXTSTAGE,	// 次のステージへ
		RETURNTITLE,	// タイトルへ戻る
	};

	/// <summary> ボタンの初期化コンストラクタ </summary>
	/// <param name="screen"> 所属する画面 </param>
	/// <param name="y"> ボタンが縦軸でどこにあるか </param>
	/// <param name="x"> 所属する横軸でどこにあるか </param>
	/// <param name="center"> ボタンの中心座標 </param>
	/// <param name="width"> ボタンの横幅 </param>
	/// <param name="height"> ボタンの縦幅 </param>
	/// <param name="button"> 押された際の処理 </param>
	/// <param name="text"> ボタンに表示する文字列 </param>
	/// <param name="font"> 使用するフォント </param>
	Button(SCREEN_TYPE screen, int y, int x, VECTOR center, int width, int height, BUTTON_TYPE button, std::string text, int font);

	/// <summary> ボタンの描画メソッド </summary>
	void Draw();

	/// <summary> ボタンの色の変更メソッド </summary>
	/// <param name="changeColor"> 変更する色 </param>
	void SetButtonColor(int changeColor);

	/// <summary> ボタンの描画座標を返すメソッド </summary>
	/// <param name="screenSize"> 画面のサイズ </param>
	/// <param name="pos"> ボタンの中心座標 </param>
	/// <param name="length"> ボタンの長さ </param>
	/// <returns> 描画座標 </returns>
	int GetDrawPos(int screenSize, float pos, int length);

	/// <summary> buttonTypeを返すメソッド </summary>
	/// <returns> buttonType </returns>
	BUTTON_TYPE GetButtonType();

	/// <summary> belongScreenを返すメソッド </summary>
	/// <returns> belongScreen </returns>
	SCREEN_TYPE GetBelongScreen();

	/// <summary> columNumを返すメソッド </summary>
	/// <returns> columNum </returns>
	int GetColumNum();

	/// <summary> rowNumを返すメソッド </summary>
	/// <returns> rowNum </returns>
	int GetRowNum();

private:
	BUTTON_TYPE buttonType;   // ボタンの種類
	SCREEN_TYPE belongScreen;   // どのスクリーンに配置してあるか
	int columnNum;   // 縦の何番目に属しているか
	int rowNum;   // 横の何番目に属しているか
	VECTOR centerPos;   // ボタンの中心座標
	int widthLength;    // ボタンの横幅
	int heightLength;   // ボタンの縦幅
	std::string drawText;   // ボタンに表示する文字列
	int fontType;   // 使用するフォント
	int buttonColor = 0;   // ボタンの色
};

/// <summary> どのボタンを選択しているかを返すメソッド </summary>
/// <returns> 選択中のボタンのインスタンス </returns>
Button* SelectGetButtonArray();
/// <summary> ボタンの移動処理を行うメソッド </summary>
void ButtonMovement();

/// <summary> ボタンの押下処理を行うメソッド </summary>
void ButtonPressed();

/// <summary> 数値を指定の範囲内に収めるメソッド：リファクタリング、ベースヘッダなどに移動する </summary>
/// <param name="num"> 収めたい数値 </param>
/// <param name="min"> 最小値 </param>
/// <param name="max"> 最大値 </param>
/// <returns> 指定の数字に収めた値 </returns>
float ClampNum(float num, float min, float max);

extern std::vector<Button*> buttonArray;    // ボタンの配列
extern VECTOR buttonMovePos;    // ボタンの移動座標
extern VECTOR buttonPos;    // ボタンの選択位置
const int BUTTON_NUM_X = 4; // 横のボタン数
const int BUTTON_NUM_Y = 4; // 縦のボタン数
const int BUTTON_NUM_SCREEN = 5;    // ボタンのある画面の種類数
extern int buttonMap[BUTTON_NUM_SCREEN][BUTTON_NUM_Y][BUTTON_NUM_X];    // ボタンの配置マップ
const int BUTTON_SELECT_COLOR = GetColor(0, 255, 128);  // 選択中のボタンの色
const int BUTTON_NORMAL_COLOR = GetColor(200, 200, 200);    // 非選択中のボタンの色
const int TEXT_COLOR = GetColor(0, 0, 0);   // 文字の色

#endif
