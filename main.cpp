#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
#include "Button.h"
#include "Player.h"
#include "3dSetting.h"
#include "Input.h"
// メインの制御を文（特にwhile内）をリファクタリングする
bool isGameQuit;
int screenWidth;
int screenHeight;
int bigFontHandle;
int normalFontHandle;
int smallFontHandle;
Player player(VGet(0, 0, 0), VGet(0, -90 * DX_PI_F / 180, 0), FIRST_SPEED);
Camera camera(START_CAMERA_POS, START_CAMERA_LOOK);
Light light(START_LIGHT_POS);

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1) {	// エラー処理
		return -1;
	}
	// 初期設定
	GameSetUp();
	player.SetUp();
	camera.SetUp();
	light.SetUp();

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	while (ProcessMessage() == 0 && !isGameQuit)
	{
		ClearDrawScreen();
		CheckAllKeyState();	// 全キーの状態をチェック
		ButtonMovement();	//  ボタンの移動
		ButtonPressed();	// ボタンが押されたときの処理

		if (currentScreenType == STAGECLEAR) {
			HighScoreCheck();
		}
		if (currentScreenType == INGAME) {
			if (!isGameStop) {
				player.Move();
				player.ChangeSpeed();
				player.Jump();
				if (player.GetChangeSpeedCount() <= 4) {
					light.Move(player.GetSpeed());
					camera.Move(player.GetSpeed());
				}
				if (CheckHitKeyDown(KEY_INPUT_ESCAPE)) { nextScreenType = PAUSE; fadeState = SCREENSETUP; }
				if (CheckHitKey(KEY_INPUT_SPACE)) { ScoreCalculation(); }	// 仮で置いているr.Move();
				InGameScoreView();
				if (player.GetPosition().x >= goalPosition[stageNumber] + 1000) {	// マジックナンバーにするのはやめる（リファクタリング）
					nextScreenType = STAGECLEAR;
					fadeState = SCREENSETUP;
				}
			}
			else {
				if (!isFading) DrawStartCountDown();
			}
			// カメラ、ライト、プレイヤーの描画
			SetCameraPositionAndTarget_UpVecY(camera.GetCameraPos(), camera.GetLookPos());
			SetLightPosition(light.GetLightPos());
			MV1SetPosition(player.GetModelHandle(), player.GetPosition());
			MV1DrawModel(player.GetModelHandle());
			DrawStage(stageNumber, player);
			DrawProgressRateBar(player, 20, 80, 50);
		}
		if (fadeState == FADEWAIT || fadeState == SCREENSETUP) {
			player.Initialization();
			camera.Initialization();
			light.Initialization();
			if (fadeState == FADEWAIT) {	//仮で置いておく
				score = 0;
				inGameVewScore = 0;
			}
		}
		/*DrawUI();
		DrawModal()*/
		ScreenUISwitching();	//	UIを描画
		ScreenFadeControl();	// フェード演出

		ScreenFlip();

		clsDx();	// デバッグ用文字を消す
		WaitTimer(16); // 約60FPS
	}
	// フォントデータを削除
	DeleteFontToHandle(normalFontHandle);
	DeleteFontToHandle(bigFontHandle);
	DeleteFontToHandle(smallFontHandle);
	RemoveFontResourceExA("", FR_PRIVATE, NULL);

	DxLib_End();
	return 0;
}

void GameSetUp() {
	// 画面の解像度に応じて画面サイズを変更
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	ChangeWindowMode(TRUE);
	SetGraphMode(screenWidth, screenHeight, 32);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);


	SetBackgroundColor(255, 255, 255);	// 背景色を白に

	// フォントのをロードして、サイズ等を設定
	AddFontResourceExA("Resource/KaqookanV2.ttf", FR_PRIVATE, NULL);
	bigFontHandle = CreateFontToHandle("N4カクーカンV2", screenWidth / 18, 5, DX_FONTTYPE_ANTIALIASING);
	normalFontHandle = CreateFontToHandle("N4カクーカンV2", screenWidth / 30, 3, DX_FONTTYPE_ANTIALIASING);
	smallFontHandle = CreateFontToHandle("N4カクーカンV2", screenWidth / 60, 1, DX_FONTTYPE_ANTIALIASING);

	// NULLチェック
	if (screenWidth == 0 || screenHeight == 0) {
		printfDx("Error:NULL 画面サイズの取得失敗\n");
	}
	if (bigFontHandle == -1 || normalFontHandle == -1 || smallFontHandle == -1) {
		printfDx("Error:NULL フォントの取得失敗\n");
	}
}