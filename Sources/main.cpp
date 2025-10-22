#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
#include "Button.h"
#include "Player.h"
#include "3dSetting.h"
#include "Input.h"

bool isGameQuit;		// exe終了フラグ
int screenWidth, screenHeight;	// 画面サイズ
FONT fontData[4];	// フォントデータとサイズ

Player player(VGet(0, 0, 0), VGet(0, -90 * DX_PI_F / 180, 0), FIRST_SPEED);
Camera camera(START_CAMERA_POS, START_CAMERA_LOOK);
Light light(START_LIGHT_POS);

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面の解像度に応じて画面サイズを変更
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	ChangeWindowMode(TRUE);
	SetGraphMode(screenWidth, screenHeight, 32);
	if (DxLib_Init() == -1) {	// エラー処理
		return -1;
	}
	// 初期設定
	UISetUp();
	GameSetUp();
	AudioSetUp();
	player.SetUp();
	camera.SetUp();
	light.SetUp();

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	while (ProcessMessage() == 0 && !isGameQuit)
	{
		ClearDrawScreen();
		CheckAllKeyState();	// 全キーの状態をチェック
		if (currentScreenType != INGAME) {
			ButtonMovement();	//  ボタンの移動
			ButtonPressed();	// ボタンが押されたときの処理
		}
		if (currentScreenType == STAGECLEAR) {
			HighScoreCheck();
		}
		if (currentScreenType == INGAME || currentScreenType == PAUSE || currentScreenType == GAMEOVER || currentScreenType == STAGECLEAR) {
			if (!isGameStop) {

				if (player.GetChangeSpeedCount() <= 4) {
					light.Move(player.GetSpeed());
					camera.Move(player.GetSpeed());
				}
				if (CheckHitKeyDown(KEY_INPUT_ESCAPE)) { nextScreenType = PAUSE; fadeState = SCREENSETUP; isGameStop = true; }
				if (CheckHitKey(KEY_INPUT_SPACE)) { ScoreCalculation(player.GetSpeed()); }	// 仮で置いているr.Move();
				InGameScoreView();
				if (player.GetPosition().x >= goalPosition[stageNumber] + CLEARCANGE_POS) {
					nextScreenType = STAGECLEAR;
					fadeState = SCREENSETUP;
					isGameStop = true;
				}
			}
			else {
				if (currentScreenType == INGAME && !isFading) DrawStartCountDown();
			}
			// カメラ、ライト、プレイヤーの描画
			player.Move();
			player.ChangeSpeed();
			player.Jump();
			SetCameraPositionAndTarget_UpVecY(camera.GetCameraPos(), camera.GetLookPos());
			SetLightPosition(light.GetLightPos());
			MV1SetPosition(player.GetModelHandle(), player.GetPosition());
			MV1DrawModel(player.GetModelHandle());
			DrawStage(stageNumber, player);
		}
		if (fadeState == FADEWAIT) {
			player.Initialization();
			camera.Initialization();
			light.Initialization();
			if (fadeState == FADEWAIT) {	//仮で置いておく
				score = 0;
				inGameVewScore = 0;
			}
		}
		if (!isFading) {
			if (currentScreenType == TITLE || currentScreenType == STAGESELECT)
				PlayBGM(bgm);
			if (currentScreenType == INGAME)
				PlayBGM(bgm1);
		}
		DrawUI(player);	//	UIを描画
		DrawGraph(-200, 100, keyDown, true);
		isFading = ScreenFadeControl();	// フェード演出

		ScreenFlip();

		clsDx();	// デバッグ用文字を消す
		WaitFrameRate();
	}
	// フォントデータを削除
	for (int i = 0; i < 4; i++) {
		DeleteFontToHandle(fontData[i].fontHandle);
	}
	RemoveFontResourceExA("", FR_PRIVATE, NULL);

	DxLib_End();
	return 0;
}

void GameSetUp() {
	// Zバッファを有効にする、正確な奥行き関係に基づいた描画を行うために使用
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetBackgroundColor(255, 255, 255);	// 背景色を白に。これは後で消す

	// フォントをロードして、サイズを設定
	AddFontResourceExA("Resource/Fonts/KaqookanV2.ttf", FR_PRIVATE, NULL);
	fontData[FONT_EXTRALARGE].fontSize = screenWidth / 18;
	fontData[FONT_LARGE].fontSize = screenWidth / 30;
	fontData[FONT_MEDIUM].fontSize = screenWidth / 60;
	fontData[FONT_SMALL].fontSize = screenWidth / 70;
	fontData[FONT_EXTRALARGE].fontHandle = CreateFontToHandle("N4カクーカンV2", fontData[FONT_EXTRALARGE].fontSize, 5, DX_FONTTYPE_ANTIALIASING);
	fontData[FONT_LARGE].fontHandle = CreateFontToHandle("N4カクーカンV2", fontData[FONT_LARGE].fontSize, 3, DX_FONTTYPE_ANTIALIASING);
	fontData[FONT_MEDIUM].fontHandle = CreateFontToHandle("N4カクーカンV2", fontData[FONT_MEDIUM].fontSize, 1, DX_FONTTYPE_ANTIALIASING);
	fontData[FONT_SMALL].fontHandle = CreateFontToHandle("N4カクーカンV2", fontData[FONT_SMALL].fontSize, 1, DX_FONTTYPE_ANTIALIASING);

	// NULLチェック
	if (fontData[FONT_EXTRALARGE].fontHandle == -1 || fontData[FONT_LARGE].fontHandle == -1 || fontData[FONT_MEDIUM].fontHandle == -1 || fontData[FONT_SMALL].fontHandle == -1) {
		printfDx("Error:NULL フォントの取得失敗\n");
	}
}