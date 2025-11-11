#pragma once
#include "UI.h"		// 画面の状態を取得用
#include <vector>

// ボタンの処理を分ける
enum class ButtonType {
	Start,  // ゲーム開始
	StageSelect,    // ステージセレクトを開く
	Quit,   // exe終了
	PickStage,	// ステージ選択
	Resume,	// ゲーム再開
	Exit,	// インゲーム終了
	Retry,	// リトライ
	Next,	// 次のステージへ
	ReturnTitle,	// タイトルへ戻る
};

// ボタンの属している画面、ボタンマップの座標を格納する構造体
struct ButtonLocation {
	SCREEN_TYPE screen;
	int columnNum;
	int rowNum;
};

// ボタンの中央座標と縦横の長さを格納する構造体 
struct ButtonArea {
	VECTOR2 position;
	float width;
	float height;
};

constexpr int BUTTON_NUM_X = 6; // 横のボタン数
constexpr int BUTTON_NUM_Y = 5; // 縦のボタン数
constexpr int BUTTON_NUM_SCREEN = 5;    // ボタンのある画面の種類数
const VECTOR START_BUTTON_POS = VGet(1, 1, 0);	// 画面が変わるたびにボタンの位置を戻す座標

class Button {
public:
	Button(ButtonLocation _location, ButtonArea _area, ButtonType _buttonType, std::string _drawText, int _fontType);
	/// <summary> ボタンの描画メソッド </summary>
	void Draw()const;

	// private変数を読み取り専用で返すメソッド群
	ButtonType GetButtonType()const { return buttonType; };
	SCREEN_TYPE GetBelongScreen()const { return location.screen; };
	int GetColumNum()const { return location.columnNum; };
	int GetRowNum()const { return location.rowNum; };
	int GetFont()const { return fontType; }

	// private変数に書き込みを行うメソッド群
	void SetDrawText(std::string text) { drawText = text; }
	void SetButtonColor(int changeColor) { buttonColor = changeColor; }
	void SetButtonType(ButtonType type) { buttonType = type; }
	void SetFont(int handle) { fontType = handle; }

private:
	ButtonLocation location;
	ButtonArea area;

	ButtonType buttonType;   // ボタンの種類
	std::string drawText;   // ボタンに表示する文字列
	int fontType;   // 使用するフォント
	int buttonColor = 0;   // ボタンの色
};

class ButtonManager {
public:
	ButtonManager() :buttonArray() {}
	
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

	int buttonMap[BUTTON_NUM_SCREEN][BUTTON_NUM_Y][BUTTON_NUM_X] = {
	{ {0,0,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,0,0,0,0,0} }, // TITLE
	{ {0,0,0,0,0,0}, {0,1,1,1,0,0}, {0,1,1,1,1,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // STAGESELECT
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // PAUSE
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // GAMEOVER
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }  // STAGECLEAR
	};    // ボタンの配置マップ
private:
	VECTOR buttonMovePos = START_BUTTON_POS;    // ボタンの移動座標
	VECTOR buttonPos = START_BUTTON_POS;    // ボタンの選択位置
	std::vector<Button*> buttonArray;    // ボタンの配列

};

extern ButtonManager buttonManager;
