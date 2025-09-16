#include "DxLib.h"
#include "Main.h"
#include "UI.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetBackgroundColor(255, 255, 255);	// 背景色を白に
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	ScreenUISwithing();	// UIを描画
	int a = LoadGraph("Resource/仮ボタン.png");
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


		if (currentScreenType != INGAME) {	// ボタン操作
			ButtonChanged();
		}
		printfDx("選択されているボタン：[%d][%d][%d]\n", currentScreenType, buttonPosY, buttonPosX);
		printfDx("ステージ番号；%d\n", stageNumber);
		OnClickSwitchUI();  // ボタンが押されたときの処理
		ScreenUISwithing();	//	UIを描画
		ScreenFadeControl();	// フェード演出
		ScreenFlip();
		clsDx();	// printfDx用画面クリア
		WaitTimer(16); // 約60FPS
	}

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}