#pragma once
#include "UI.h"		// 画面の状態を取得用
#include <vector>

const VECTOR START_BUTTON_POS = VGet(1, 1, 0);	// 画面が変わるたびにボタンの位置を戻す座標
constexpr int BUTTON_NUM_X = 6; // 横のボタン数
constexpr int BUTTON_NUM_Y = 5; // 縦のボタン数
constexpr int BUTTON_NUM_SCREEN = 5;    // ボタンのある画面の種類数

class Button {
public:
	enum BUTTON_TYPE {
		GAMESTART,  // ゲーム開始
		OPENSTAGESELECT,    // ステージセレクトを開く
		GAMEQUIT,   // exe終了
		SELECTSTAGE1, SELECTSTAGE2, SELECTSTAGE3, SELECTSTAGE4, SELECTSTAGE5, SELECTSTAGE6,	// ステージ選択
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

	/// <summary> ボタンの色の変更メソッド </summary>
	/// <param name="changeColor"> 変更する色 </param>
	void SetButtonColor(int changeColor);

	/// <summary> buttonTypeを返すメソッド </summary>
	/// <returns> buttonType </returns>
	BUTTON_TYPE GetButtonType()const;

	/// <summary> belongScreenを返すメソッド </summary>
	/// <returns> belongScreen </returns>
	SCREEN_TYPE GetBelongScreen()const;

	/// <summary> columnNumを返すメソッド </summary>
	/// <returns> columnNum </returns>
	int GetColumNum()const;

	/// <summary> rowNumを返すメソッド </summary>
	/// <returns> rowNum </returns>
	int GetRowNum()const;

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
	ButtonManager() :buttonArray({}), buttonMovePos(START_BUTTON_POS), buttonPos(START_BUTTON_POS) {}
	std::vector<Button*> buttonArray;    // ボタンの配列
	VECTOR buttonMovePos;    // ボタンの移動座標
	VECTOR buttonPos;    // ボタンの選択位置
	int buttonMap[BUTTON_NUM_SCREEN][BUTTON_NUM_Y][BUTTON_NUM_X];    // ボタンの配置マップ

	/// <summary> どのボタンを選択しているかを返すメソッド </summary>
	/// <returns> 選択中のボタンのインスタンス </returns>
	Button* SelectGetButtonArray();

	/// <summary> ボタンの移動処理を行うメソッド </summary>
	void ButtonMovement();

	/// <summary> ボタンの押下処理を行うメソッド </summary>
	void ButtonPressed();
};

extern ButtonManager buttonManager;
