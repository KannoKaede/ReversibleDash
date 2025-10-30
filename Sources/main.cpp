#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
#include "Button.h"
#include "Player.h"
#include "3dSetting.h"
#include "Input.h"

SCREEN_SIZE screen;
FONT_DATA fontData[4];	// フォントデータとサイズ
bool isDrawInGame;

Player player(START_PLAYER_POS, START_PLAYER_ROT, START_PLAYER_SCALE, FIRST_SPEED);
Camera camera(START_CAMERA_POS, START_CAMERA_LOOK);
Light light(START_LIGHT_POS);

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面の解像度に応じて画面サイズを変更	: ここに置かないと画像が描画できなくなる
	screen.width = GetSystemMetrics(SM_CXSCREEN);
	screen.height = GetSystemMetrics(SM_CYSCREEN);
	ChangeWindowMode(TRUE);
	SetGraphMode(screen.width, screen.height, 32);
	if (DxLib_Init() == -1)return -1;
	// 初期設定
	GameSetUp();

	for (int i = 0; i < MV1GetMaterialNum(stageHandle); i++)
	{
		MV1SetMaterialDifColor(stageHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
		MV1SetMaterialAmbColor(stageHandle, i, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
		MV1SetMaterialSpcColor(stageHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
		MV1SetMaterialEmiColor(stageHandle, i, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
		MV1SetMaterialSpcPower(stageHandle, i, 3.0f);
	}
	for (int i = 0; i < MV1GetMaterialNum(player.GetModel()); i++)
	{
		MV1SetMaterialDifColor(player.GetModel(), i, GetColorF(0.3f, 0.3f, 0.3f, 1.0f));
		MV1SetMaterialAmbColor(player.GetModel(), i, GetColorF(1, 1, 1, 1));
		MV1SetMaterialSpcColor(player.GetModel(), i, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
		MV1SetMaterialEmiColor(player.GetModel(), i, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
		MV1SetMaterialSpcPower(player.GetModel(), i, 3.0f);
	}
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	while (ProcessMessage() == 0)
	{
		isDrawInGame = IsDrawInGame();
		ClearDrawScreen();
		CheckAllKeyState();	// 全キーの状態をチェック
		if (currentScreenType != INGAME) {
			ButtonMovement();	//  ボタンの移動
			ButtonPressed();	// ボタンが押されたときの処理
		}
		if (currentScreenType == CLEAR) {
			HighScoreCheck();
		}
		if (isDrawInGame) {
			// カメラ、ライト、プレイヤーの描画
			player.Move();
			player.ChangeSpeed();
			player.Jump();
			SetCameraPositionAndTarget_UpVecY(camera.GetCameraPos(), camera.GetLookPos());
			SetLightPosition(light.GetLightPos());
			DrawStage(player);
			if (!isGameStop) {

				if (player.GetChangeSpeedCount() <= 4) {
					light.Move(player.GetSpeed());
					camera.Move(player.GetSpeed());
				}
				if (CheckHitKeyDown(KEY_INPUT_ESCAPE)) { nextScreenType = PAUSE; fadeState = SCREENSETUP; isGameStop = true; }
				if (CheckHitKey(KEY_INPUT_SPACE)) { ScoreCalculation(player.GetSpeed()); }	// 仮で置いているr.Move();
				InGameScoreView();
				if (player.GetPosition().x >= goalPosition[stageNumber] + CLEARCANGE_POS) {
					nextScreenType = CLEAR;
					fadeState = SCREENSETUP;
					isGameStop = true;
				}
			}
			else {
				if (currentScreenType == INGAME && !isFading) DrawStartCountDown();
			}
		}
		if (fadeState == FADEWAIT) {
			player.Initialization();
			camera.Initialization();
			light.Initialization();
			StageInitialization();
			if (fadeState == FADEWAIT) {	//仮で置いておく
				score = 0;
				vewScore = 0;
			}
		}
		if (!isFading) {
			if (currentScreenType == TITLE || currentScreenType == STAGESELECT)
				PlayBGM(bgm);
			if (currentScreenType == INGAME)
				PlayBGM(bgm1);
		}
		DrawUI(player);	//	UIを描画
		isFading = ScreenFadeControl();	// フェード演出

		ScreenFlip();

		clsDx();	// デバッグ用文字を消す
		WaitTimer(16);
	}

	SaveHighScore();
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
	SetBackgroundColor(160, 216, 239);	// 背景色を白に。これは後で消す

	// フォントをロードして、サイズを設定
	AddFontResourceExA("Resource/Fonts/KaqookanV2.ttf", FR_PRIVATE, NULL);
	fontData[EXTRALARGE].fontSize = screen.width / 18;
	fontData[LARGE].fontSize = screen.width / 30;
	fontData[MEDIUM].fontSize = screen.width / 60;
	fontData[SMALL].fontSize = screen.width / 70;
	fontData[EXTRALARGE].fontHandle = CreateFontToHandle("N4カクーカンV2", fontData[EXTRALARGE].fontSize, 5, DX_FONTTYPE_ANTIALIASING);
	fontData[LARGE].fontHandle = CreateFontToHandle("N4カクーカンV2", fontData[LARGE].fontSize, 3, DX_FONTTYPE_ANTIALIASING);
	fontData[MEDIUM].fontHandle = CreateFontToHandle("N4カクーカンV2", fontData[MEDIUM].fontSize, 1, DX_FONTTYPE_ANTIALIASING);
	fontData[SMALL].fontHandle = CreateFontToHandle("N4カクーカンV2", fontData[SMALL].fontSize, 1, DX_FONTTYPE_ANTIALIASING);

	UISetUp();
	AudioSetUp();
	StageSetUp();
	player.SetUp();
	camera.SetUp();
	light.SetUp();
	LoadHighScore();
}