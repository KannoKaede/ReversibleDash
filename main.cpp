#include "DxLib.h"
#include "Main.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	ScreenSwithing();
	while (ProcessMessage() == 0 && !isGameQuit)
	{
		ClearDrawScreen();
		//テスト用画面の状態切り替え処理
		if (CheckHitKey(KEY_INPUT_1))screenType = TITLE;
		if (CheckHitKey(KEY_INPUT_2))screenType = STAGESELECT;
		if (CheckHitKey(KEY_INPUT_3))screenType = INGAME;
		if (CheckHitKey(KEY_INPUT_4))screenType = PAUSE;
		if (CheckHitKey(KEY_INPUT_5))screenType = GAMEOVER;
		if (CheckHitKey(KEY_INPUT_6))screenType = STAGECLEAR;
		if (CheckHitKey(KEY_INPUT_7))isGameQuit = true;
		ScreenSwithing();
		ScreenFlip();
		clsDx();
	}

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}