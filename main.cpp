#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"

bool isGameQuit;
int stageNumber;
int screenWidth;
int screenHeight;
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//ウィンドウモードに設定し画面の解像度に応じて画面サイズを変更
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	ChangeWindowMode(TRUE);
	SetGraphMode(screenWidth, screenHeight, 32);
	// フォントデータの作成
	fontSetting();

	SetBackgroundColor(255, 255, 255);	// 背景色を白に
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	ScreenUISwithing();	// UIを描画
	while (ProcessMessage() == 0 && !isGameQuit)
	{
		ClearDrawScreen();
		//テスト用画面の状態切り替え処理
		if (CheckHitKey(KEY_INPUT_1) && currentScreenType == INGAME) {
			currentScreenType = GAMEOVER;
		}
		if (CheckHitKey(KEY_INPUT_2) && currentScreenType == INGAME) {
			currentScreenType = STAGECLEAR;
		}
		if (currentScreenType == INGAME && !isFading && isStartCountDown) {
			DrawStartCountDown();
		}


			if (currentScreenType != INGAME) {	// ボタンの選択切り替え
				ButtonChanged();
			}

		// デバッグ用 -------------------------------------------------------------------------------
		ScoreCalculation();
		printfDx("画面サイズ：%d:%d\n", screenWidth, screenHeight);
		printfDx("選択されているボタン：[%d][%d][%d]\n", currentScreenType, buttonPosY, buttonPosX);
		printfDx("ステージ番号：%d\n", stageNumber);
		if (currentScreenType == TITLE)
			score = 0;
		// ------------------------------------------------------------------------------------------
		CheckButtonPressed();  // ボタンが押されたときの処理
		if (currentScreenType == STAGECLEAR) {
			HighScoreCheck();
		}
		ScreenUISwithing();	//	UIを描画
		ScreenFadeControl();	// フェード演出
		ScreenFlip();

		clsDx();	// デバッグ用文字を消す
		if (screenWidth != GetSystemMetrics(SM_CXSCREEN) || screenHeight != GetSystemMetrics(SM_CYSCREEN)) {
			SetGraphMode(screenWidth, screenHeight, 32);
			screenWidth = GetSystemMetrics(SM_CXSCREEN);
			screenHeight = GetSystemMetrics(SM_CYSCREEN);
			bigFontHandle = CreateFontToHandle("N4カクーカンV2", screenWidth / 18, 5, DX_FONTTYPE_ANTIALIASING);
			normalFontHandle = CreateFontToHandle("N4カクーカンV2", screenWidth / 30, 3, DX_FONTTYPE_ANTIALIASING);
			smallFontHandle = CreateFontToHandle("N4カクーカンV2", screenWidth / 60, 1, DX_FONTTYPE_ANTIALIASING);
		}
		WaitTimer(16); // 約60FPS
	}
	// フォントデータを削除
	DeleteFontToHandle(normalFontHandle);
	DeleteFontToHandle(bigFontHandle);
	DeleteFontToHandle(smallFontHandle);
	RemoveFontResourceExA("", FR_PRIVATE, NULL);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}