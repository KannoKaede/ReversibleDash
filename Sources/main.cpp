#include "Audio.h"
#include "Button.h"
#include "CameraLight.h"
#include "Input.h"
#include "Main.h"
#include "Player.h"
#include "Score.h"
#include "Stage.h"
#include "UI.h"

Player player(START_PLAYER_POS, START_PLAYER_ROT, PLAYER_SCALE, FIRST_SPEED);
CameraLight cameraLight;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	base.SetScreenSize();	// 画面の解像度に応じて画面サイズを変更	: ここに置かないと画像が描画できなくなる
	if (DxLib_Init() == -1)return -1;	// DXライブラリ初期化処理
	base.SetUp();	// ゲームの初期設定を行う
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();	// 画面をクリア
		input.CheckAllKey();	// 全キーの状態をチェック
		if (base.IsDrawInGame()) {
			// カメラ、ライト、プレイヤーの描画
			player.Move();
			player.Jump();
			cameraLight.CameraMove(player);
			stageManager.Draw(player);
			scoreManager.AddViewScore();
			if (!base.GetIsGameStop() && stageManager.IsClear(player.GetPosition().x)) {
				scoreManager.CheckHighScore();
				fadeManager.ChangeUIState(base.GetStageNumber() == 6 ? GAMECLEAR : STAGECLEAR, NOTFADE);
				audioManager.PlaySE(audioManager.JINGLE_CLEAR);
			}
		}
		
		audioManager.PlayBGMControl();
		uiManager.DrawUI(player);	//	UIを描画
		if (uiManager.GetCurrentScreen()<SCREEN_TYPE::BUTTON_NUM) {
			buttonManager.UpdateButtonSelection();	//  ボタンの移動
			buttonManager.ButtonPressed();	// ボタンが押されたときの処理
		}
		else {
			
		}
		fadeManager.DrawFadeController();	// フェード処理：UIより後に処理を行わないとUIがフェードの前に出てきてしまう

		ScreenFlip();

		clsDx();	// デバッグ用文字を消す
		WaitTimer(16);
	}

	base.CleanUp();	// ゲーム終了処理
	DxLib_End();
	return 0;
}

void Base::SetUp() {
	SetBackgroundColor(160, 216, 239);	// 背景色を空色に設定
	SetMouseDispFlag(FALSE);	// マウスを非表示

	// Zバッファを有効にする、正確な奥行き関係に基づいた描画を行うために使用
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	

	// その他、初期設定を行うものをここでまとめて行う
	base.FontSetUp();
	uiManager.SetUp();
	audioManager.SetUp();
	stageManager.SetUp();
	player.SetUp();
	cameraLight.SetUp();
	scoreManager.LoadHighScore();
}

void Base::Initialization() {
	// 座標やスコア等をリセットする
	// 座標やスコア等をリセットする
	stageNumber = nextStageNumber;
	player.Initialization();
	cameraLight.Initialization();
	stageManager.Initialization();
	scoreManager.Initialization();
}

void Base::CleanUp() {
	scoreManager.SaveHighScore();
	// フォントデータを削除
	for (int i = 0; i < FONT_TYPE_NUM; i++) {
		DeleteFontToHandle(chihaya_FontData[i].handle);
	}
	RemoveFontResourceExA("", FR_PRIVATE, NULL);
}