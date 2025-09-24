#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
#include "Player.h"

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
	Player  player(VGet(0, 0, 20), VGet(0, 80, 0), FIRST_SPEED);
	Camera camera(VGet(player.GetPosition().x + 60.0f, 70.0f, -100.0f), VGet(player.GetPosition().x + 60.0f, 70.0f, 0.0f));
	Light light(VGet(player.GetPosition().x + 60.0f, 70.0f, -100.0f));


	SetBackgroundColor(255, 255, 255);	// 背景色を白に
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	while (ProcessMessage() == 0 && !isGameQuit)
	{
		ClearDrawScreen();
		printfDx("%f\n%f\n%f", player.GetPosition().x, player.GetPosition().y, player.GetPosition().z);
		MV1SetPosition(player.modelHandle, player.GetPosition());
		DrawSphere3D(VGet(20.0f, 00.0f, 20.0f), 80.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
		SetCameraPositionAndTarget_UpVecY(camera.GetPosition(), camera.GetTarget());
		SetLightPosition(light.GetPosition());
		MV1DrawModel(player.modelHandle);
		printfDx("%d", stageNumber);
		switch (currentScreenType)
		{
		case TITLE:
			ButtonChanged();
			score = 0;	// 仮で置いている
			break;
		case STAGESELECT:
			ButtonChanged();
			break;
		case PAUSE:
			ButtonChanged();
			break;
		case GAMEOVER:
			ButtonChanged();
			break;
		case STAGECLEAR:
			ButtonChanged();
			HighScoreCheck();
			break;
		case INGAME:
			ButtonChanged();
			if (!isGameStop) {
				player.ChangeSpeed();
				if (CheckHitKey(KEY_INPUT_1)) { currentScreenType = GAMEOVER; }	// 仮で置いている
				printfDx("%f", goalPosition[stageNumber]);
				if (player.GetPosition().x > goalPosition[stageNumber] + 200) { currentScreenType = STAGECLEAR; buttonPosX = 0; buttonPosY = 0; }	// 画面端に行くとクリアにしている：マジックナンバーで適当にやってるので後で変更
				if (CheckHitKey(KEY_INPUT_SPACE)) { ScoreCalculation(); }	// 仮で置いている
				if (player.GetChangeSpeedCount() < 5) {
					camera.Move(player.GetPosition().x);
					light.Move(player.GetPosition().x);
				}
				player.Move();
				player.Jump();
			}
			else {
				if (!isFading) DrawStartCountDown();
			}
			break;
		default:
			break;
		}

		if (fadeState == FADEWAIT) {
			player.SetPosition(VGet(0, 0, 20));
			player.SetSpeed(FIRST_SPEED);
			player.SetChangeSpeedCount(1);
			camera.Move(player.GetPosition().x);
			light.Move(player.GetPosition().x);
		}

		CheckButtonPressed();  // ボタンが押されたときの処理
		ScreenUISwithing();	//	UIを描画
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
