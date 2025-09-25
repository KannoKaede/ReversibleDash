#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
#include "Button.h"
#include "Player.h"
#include "Input.h"

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

	int ModelHandle = MV1LoadModel("Resource/F-14Test.mv1");
	SetCameraNearFar(0, 1000);
	SetUseLighting(TRUE);
	SetLightDirection(VGet(0, 0, 1));

	//ウィンドウモードに設定し画面の解像度に応じて画面サイズを変更
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	ChangeWindowMode(TRUE);
	SetGraphMode(screenWidth, screenHeight, 32);

	// フォントデータの作成
	fontSetting();
	SetBackgroundColor(255, 255, 255);	// 背景色を白に
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	while (ProcessMessage() == 0 && !isGameQuit)
	{
		CheckAllKeyState();	// 全キーの状態をチェック
		ClearDrawScreen();
		SetCameraPositionAndTarget_UpVecY(VGet(50, 0, 50), VGet(0, 0, 0));
		ButtonMovement();	//  ボタンの移動
		ButtonPressed();	// ボタンが押されたときの処理
		//DrawSphere3D(VGet(0, 0, 0), 80.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
		printfDx("%d\n", ModelHandle);
		VECTOR test = MV1GetPosition(ModelHandle);
		printfDx("%f\n%f\n%f", test.x, test.y, test.z);
		MV1SetPosition(ModelHandle, VGet(0, 0, 0));
		int i = MV1DrawModel(ModelHandle);
		printfDx("%d", i);
		switch (currentScreenType)
		{
		case TITLE:
			score = 0;	// 仮で置いている
			break;
		case STAGESELECT:
			break;
		case PAUSE:
			break;
		case GAMEOVER:
			break;
		case STAGECLEAR:
			HighScoreCheck();
			break;
		case INGAME:
			if (!isGameStop) {
				if (CheckHitKey(KEY_INPUT_1)) { currentScreenType = GAMEOVER; }	// 仮で置いている
				printfDx("%f", goalPosition[stageNumber]);
				if (CheckHitKey(KEY_INPUT_SPACE)) { ScoreCalculation(); }	// 仮で置いているr.Move();
			}
			else {
				if (!isFading) DrawStartCountDown();
			}
			break;
		default:
			break;
		}
		//CheckButtonPressed();  // ボタンが押されたときの処理
		ScreenUISwithing();	//	UIを描画
		ScreenFadeControl();	// フェード演出

		ScreenFlip();

		clsDx();	// デバッグ用文字を消す
		WaitTimer(16); // 約60FPS
	}
	MV1DeleteModel(ModelHandle);
	// フォントデータを削除
	DeleteFontToHandle(normalFontHandle);
	DeleteFontToHandle(bigFontHandle);
	DeleteFontToHandle(smallFontHandle);
	RemoveFontResourceExA("", FR_PRIVATE, NULL);

	DxLib_End();
	return 0;
}
