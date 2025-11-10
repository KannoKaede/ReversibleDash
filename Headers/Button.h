#pragma once
#include "UI.h"		// 画面の状態を取得用
#include <vector>

constexpr int BUTTON_NUM_X = 6; // 横のボタン数
constexpr int BUTTON_NUM_Y = 5; // 縦のボタン数
constexpr int BUTTON_NUM_SCREEN = 5;    // ボタンのある画面の種類数
const VECTOR START_BUTTON_POS = VGet(1, 1, 0);	// 画面が変わるたびにボタンの位置を戻す座標

class Button {
public:
	enum BUTTON_TYPE {
		GAMESTART,  // ゲーム開始
		OPENSTAGESELECT,    // ステージセレクトを開く
		GAMEQUIT,   // exe終了
		SELECTSTAGE,	// ステージ選択
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
	Button(SCREEN_TYPE screen, int y, int x, VECTOR center, int width, int height, BUTTON_TYPE button, std::string text, int font, bool isCenterPos);

	/// <summary> ボタンの描画メソッド </summary>
	void Draw()const;

	// private変数を読み取り専用で返すメソッド群
	BUTTON_TYPE GetButtonType()const { return buttonType; };
	SCREEN_TYPE GetBelongScreen()const { return belongScreen; };
	int GetColumNum()const { return columnNum; };
	int GetRowNum()const { return rowNum; };

	// private変数に書き込みを行うメソッド群
	void SetDrawText(std::string text) { drawText = text; }
	void SetButtonColor(int changeColor) { buttonColor = changeColor; }
	void SetButtonType(BUTTON_TYPE type) { buttonType = type; }
	
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
	bool isCenter;	// テキストをボタン中央に描画するか
};

class ButtonManager {
public:
	ButtonManager() :buttonArray() {}

	int buttonMap[BUTTON_NUM_SCREEN][BUTTON_NUM_Y][BUTTON_NUM_X] = {
	{ {0,0,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,0,0,0,0,0} }, // TITLE
	{ {0,0,0,0,0,0}, {0,1,1,1,0,0}, {0,1,1,1,1,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // STAGESELECT
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // PAUSE
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // GAMEOVER
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }  // STAGECLEAR
	};    // ボタンの配置マップ

	/// <summary> どのボタンを選択しているかを返すメソッド </summary>
	/// <returns> 選択中のボタンのインスタンス </returns>
	Button* SelectGetButtonArray();

	/// <summary> ボタンの移動処理を行うメソッド </summary>
	void ButtonMovement();

	/// <summary> ボタンの押下処理を行うメソッド </summary>
	void ButtonPressed();

	void SetButtonArray(Button* button) { buttonArray.push_back(button); }
	void SetButtonMovePos(VECTOR pos) { buttonMovePos = pos; }
	void SetButtonPos(VECTOR pos) { buttonPos = pos; }
private:
	VECTOR buttonMovePos = START_BUTTON_POS;    // ボタンの移動座標
	VECTOR buttonPos = START_BUTTON_POS;    // ボタンの選択位置
	std::vector<Button*> buttonArray;    // ボタンの配列

};

extern ButtonManager buttonManager;
