#pragma once
#include "UI.h"		// 画面の状態を取得用
#include <vector>

/// <summary> ボタンの押下時の処理を設定 </summary>
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

/// <summary> ボタンの属している画面、ボタンマップの座標を格納する構造体 </summary>
struct ButtonLocation {
	SCREEN_TYPE		screen;		// 属している画面
	int				columnNum;	// ボタンマップの座標Y
	int				rowNum;		// ボタンマップの座標X
};

/// <summary> ボタンの中央座標と縦横の長さを格納する構造体 </summary>
struct ButtonArea {
	VECTOR2			position;	// ボタンの座標(%)
	float			width;		// ボタンの幅(%)
	float			height;		// ボタンの高さ(%)
};

class Button {
public:
	/// <summary> コンストラクタ：描画、識別に必要な情報を初期化する </summary>
	Button(ButtonLocation _location, ButtonArea _area, ButtonType _buttonType, std::string _drawText, int _fontType);

	/// <summary> ボタンの描画 </summary>
	void			Draw()const;


	/// <summary> ボタンの種類を返す </summary>
	ButtonType		GetButtonType()const { return buttonType; }
	/// <summary> 所属する画面を返す </summary>
	SCREEN_TYPE		GetScreen()const { return location.screen; }
	/// <summary> ボタン列番号を返す </summary>
	int				GetColumnNum()const { return location.columnNum; }
	/// <summary> ボタンの行番号を返す </summary>
	int				GetRowNum()const { return location.rowNum; }
	/// <summary> フォントの種類を返す </summary>
	int				GetFontType()const { return fontType; }


	/// <summary> 表示テキストを設定 </summary>
	void			SetDrawText(const std::string _drawText) { drawText = _drawText; }
	/// <summary> ボタンの色を設定 </summary>
	void			SetButtonColor(const int _buttonColor) { buttonColor = _buttonColor; }
private:
	ButtonLocation	location;		// 属する画面、ボタンマップの座標
	ButtonArea		area;			// 描画座標、幅高さ(%)
	ButtonType		buttonType;		// 押下時の処理設定
	std::string		drawText;		// 表示するテキスト
	int				fontType;		// 使用するフォントの種類
	int				buttonColor;	// ボタンの色
};

class ButtonManager {
public:
	/// <summary> コンストラクタ </summary>
	ButtonManager() : buttonMovePos(START_BUTTON_POS), buttonPos(START_BUTTON_POS), buttonArray() {}

	/// <summary> ボタンの移動処理を行う </summary>
	void			UpdateButtonSelection();

	/// <summary> ボタンの押下処理を行う </summary>
	void			ButtonPressed();

	/// <summary> 現在選択されているボタンを返す </summary>
	Button* GetSelectButton()const;

	/// <summary> 配列の末尾にボタンを登録 </summary>
	void			SetButtonArray(Button* _button) { buttonArray.push_back(_button); }
	/// <summary> ボタンの移動座標を設定 </summary>
	void			SetButtonMovePos(const VECTOR2 _buttonMovePos) { buttonMovePos = _buttonMovePos; }
	/// <summary> ボタンの座標を設定 </summary>
	void			SetButtonPos(const VECTOR2 _buttonPos) { buttonPos = _buttonPos; }


	static constexpr VECTOR2 START_BUTTON_POS = { 1, 1 };	// 画面表示時に最初に選択するボタンの座標
private:
	VECTOR2					buttonMovePos;	// ボタンの移動座標
	VECTOR2					buttonPos;		// ボタンの選択位置
	std::vector<Button*>	buttonArray;    // ボタンの配列

	static constexpr int	BUTTON_NUM_X = 6;					// ボタンマップXのサイズ
	static constexpr int	BUTTON_NUM_Y = 5;					// ボタンマップYのサイズ
	static constexpr int	BUTTON_NUM_SCREEN = 5;			// ボタンが存在する画面の数
	// ボタンのマップ情報：1 = ボタンがある　0 = ボタンが無い
	static constexpr int buttonMap[BUTTON_NUM_SCREEN][BUTTON_NUM_Y][BUTTON_NUM_X] = {
	{ // TITLE
		{0,0,0,0,0,0},
		{0,1,0,0,0,0},
		{0,1,0,0,0,0},
		{0,1,0,0,0,0},
		{0,0,0,0,0,0}
		},
	{ // STAGESELECT
		{0,0,0,0,0,0},
		{0,1,1,1,0,0},
		{0,1,1,1,1,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0}
	},
	{ // PAUSE
		{0,0,0,0,0,0},
		{0,1,1,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0}
	},
	{ // GAMEOVER
		{0,0,0,0,0,0},
		{0,1,1,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0}
	},
	{  // STAGECLEAR
		{0,0,0,0,0,0},
		{0,1,1,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0}
	}
	};
};

extern ButtonManager buttonManager;
