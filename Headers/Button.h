#pragma once
#include "UI.h"		// 画面の状態を取得用
#include <vector>

// ボタンの処理を分ける
enum class ButtonType {
	Start,			// ゲーム開始
	StageSelect,	// ステージセレクトを開く
	Quit,			// exe終了
	PickStage,		// ステージ選択
	Resume,			// ゲーム再開
	Exit,			// インゲーム終了
	Retry,			// リトライ
	Next,			// 次のステージへ
	ReturnTitle,	// タイトルへ戻る
};

// ボタンの属している画面、ボタンマップの座標を格納する構造体
struct ButtonLocation {
	SCREEN_TYPE screen;	// 属している画面
	int columnNum;		// ボタンマップの座標Y
	int rowNum;			// ボタンマップの座標X
};

// ボタンの中央座標と縦横の長さを格納する構造体 
struct ButtonArea {
	VECTOR2 position;	// ボタンの座標(%)
	float width;		// ボタンの幅(%)
	float height;		// ボタンの高さ(%)
};

class Button {
public:
	/// <summary> コンストラクタ </summary>
	/// <param name="_location"> ボタンが属している画面、ボタンマップの座標 </param>
	/// <param name="_area"> ボタンの中心座標(%)、ボタンの幅高さ(%) </param>
	/// <param name="_buttonType"> ボタン押下時の処理を選択 </param>
	/// <param name="_drawText"> ボタン中央に表示するテキスト </param>
	/// <param name="_fontType"> 使用するフォントの種類 </param>
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
	ButtonLocation location;	// 属する画面、ボタンマップの座標
	ButtonArea area;			// 描画座標、幅高さ(%)
	ButtonType buttonType;		// 押下時の処理設定
	std::string drawText;		// 表示するテキスト
	int fontType;				// 使用するフォントの種類
	int buttonColor = 0;		// ボタンの色
};


constexpr int BUTTON_NUM_X = 6;					// ボタンマップXのサイズ
constexpr int BUTTON_NUM_Y = 5;					// ボタンマップYのサイズ
constexpr int BUTTON_NUM_SCREEN = 5;			// ボタンが存在する画面の数
constexpr VECTOR2 START_BUTTON_POS = { 1, 1 };	// 画面表示時に最初に選択するボタンの座標

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
	void SetButtonMovePos(VECTOR2 pos) { buttonMovePos = pos; }
	void SetButtonPos(VECTOR2 pos) { buttonPos = pos; }

	int buttonMap[BUTTON_NUM_SCREEN][BUTTON_NUM_Y][BUTTON_NUM_X] = {
	{ {0,0,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,0,0,0,0,0} }, // TITLE
	{ {0,0,0,0,0,0}, {0,1,1,1,0,0}, {0,1,1,1,1,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // STAGESELECT
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // PAUSE
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // GAMEOVER
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }  // STAGECLEAR
	};    // ボタンの配置マップ
private:
	VECTOR2 buttonMovePos = START_BUTTON_POS;    // ボタンの移動座標
	VECTOR2 buttonPos = START_BUTTON_POS;    // ボタンの選択位置
	std::vector<Button*> buttonArray;    // ボタンの配列

};

extern ButtonManager buttonManager;
