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
Player player(VGet(0, 0, 0), VGet(0, -90 * DX_PI_F / 180, 0), FIRST_SPEED);
Camera camera(START_CAMERA_POS, START_CAMERA_LOOK);
Light light(START_LIGHT_POS);

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//ウィンドウモードに設定し画面の解像度に応じて画面サイズを変更
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	ChangeWindowMode(TRUE);
	SetGraphMode(screenWidth, screenHeight, 32);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	player.StartUp();
	camera.StartUp();
	light.StartUp();
	// フォントデータの作成
	fontSetting();
	SetBackgroundColor(255, 255, 255);	// 背景色を白に
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	while (ProcessMessage() == 0 && !isGameQuit)
	{
		ClearDrawScreen();
		DrawLine(0, 720, 2560, 720, GetColor(0, 0, 0));
		CheckAllKeyState();	// 全キーの状態をチェック
		ButtonMovement();	//  ボタンの移動
		ButtonPressed();	// ボタンが押されたときの処理

		switch (currentScreenType)
		{
		case TITLE:
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
				player.Move();
				player.ChangeSpeed();
				player.Jump();
				if (player.GetChangeSpeedCount() <= 4) {
					light.Move(player.GetSpeed());
					camera.Move(player.GetSpeed());
				}
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
			break;
		default:
			break;
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
