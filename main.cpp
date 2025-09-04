#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetMouseDispFlag(TRUE);
	LoadGraphScreen(220, 250, "Resource/仮ボタン.png", TRUE);
	DrawString(220, 250, "Hello C World!", GetColor(255, 255, 255));
	LoadGraphScreen(220, 320, "Resource/仮ボタン.png", TRUE);
	LoadGraphScreen(220, 390, "Resource/仮ボタン.png", TRUE);

	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}