#include "Audio.h"
#include "Button.h"
#include "CameraLight.h"
#include "Input.h"
#include "Main.h"
#include "Player.h"
#include "Score.h"
#include "Stage.h"
#include "UI.h"

Player player(START_PLAYER_POS, START_PLAYER_ROT, START_PLAYER_SCALE, FIRST_SPEED);
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
				fadeManager.ChangeUIState(CLEAR, fadeManager.NOTFADE);
			}
		}

		if (!fadeManager.GetIsFading()) {
			if (uiManager.IsEqualCurrenScreen(TITLE) || uiManager.IsEqualCurrenScreen(STAGESELECT))
				audioManager.PlayBGM(audioManager.OUTGAME_BGM);
			if (uiManager.IsEqualCurrenScreen(INGAME))
				audioManager.PlayBGM(audioManager.INGAME_BGM);
			if (input.KeyDown(KEY_INPUT_ESCAPE))  fadeManager.ChangeUIState(PAUSE, fadeManager.NOTFADE);
		}

		uiManager.DrawUI(player);	//	UIを描画
		if (!uiManager.IsEqualCurrenScreen(INGAME)) {
			buttonManager.ButtonMovement();	//  ボタンの移動
			buttonManager.ButtonPressed();	// ボタンが押されたときの処理
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

	// フォントサイズを設定した後、フォントをロードする
	AddFontResourceExA("Resource/Fonts/KaqookanV2.ttf", FR_PRIVATE, NULL);
	fontData[EXTRALARGE].size = screen.width / 18;
	fontData[LARGE].size = screen.width / 30;
	fontData[MEDIUM].size = screen.width / 60;
	fontData[SMALL].size = screen.width / 70;
	fontData[EXTRALARGE].handle = CreateFontToHandle("N4カクーカンV2", fontData[EXTRALARGE].size, 5, DX_FONTTYPE_ANTIALIASING);
	fontData[LARGE].handle = CreateFontToHandle("N4カクーカンV2", fontData[LARGE].size, 3, DX_FONTTYPE_ANTIALIASING);
	fontData[MEDIUM].handle = CreateFontToHandle("N4カクーカンV2", fontData[MEDIUM].size, 1, DX_FONTTYPE_ANTIALIASING);
	fontData[SMALL].handle = CreateFontToHandle("N4カクーカンV2", fontData[SMALL].size, 1, DX_FONTTYPE_ANTIALIASING);

	// その他、初期設定を行うものをここでまとめて行う
	uiManager.SetUp();
	audioManager.SetUp();
	stageManager.SetUp();
	player.SetUp();
	cameraLight.SetUp();
	scoreManager.LoadHighScore();

	// モデルの光の当たり方を設定：DXライブラリの初期設定のままだと暗すぎるので明るくする
	for (int i = 0; i < MV1GetMaterialNum(stageManager.GetCityHandle()); i++)	// ステージのモデル
	{
		MV1SetMaterialDifColor(stageManager.GetCityHandle(), i, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
		MV1SetMaterialAmbColor(stageManager.GetCityHandle(), i, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
		MV1SetMaterialSpcColor(stageManager.GetCityHandle(), i, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
		MV1SetMaterialEmiColor(stageManager.GetCityHandle(), i, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
		MV1SetMaterialSpcPower(stageManager.GetCityHandle(), i, 3.0f);
	}
	for (int i = 0; i < MV1GetMaterialNum(player.GetModel()); i++)	// プレイヤーのモデル
	{
		MV1SetMaterialDifColor(player.GetModel(), i, GetColorF(0.3f, 0.3f, 0.3f, 1.0f));
		MV1SetMaterialAmbColor(player.GetModel(), i, GetColorF(1, 1, 1, 1));
		MV1SetMaterialSpcColor(player.GetModel(), i, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
		MV1SetMaterialEmiColor(player.GetModel(), i, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
		MV1SetMaterialSpcPower(player.GetModel(), i, 3.0f);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < MV1GetMaterialNum(stageManager.GetCarHandle(i)); j++) {
			MV1SetMaterialDifColor(stageManager.GetCarHandle(i), j, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
			MV1SetMaterialAmbColor(stageManager.GetCarHandle(i), j, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
			MV1SetMaterialSpcColor(stageManager.GetCarHandle(i), j, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
			MV1SetMaterialEmiColor(stageManager.GetCarHandle(i), j, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
			MV1SetMaterialSpcPower(stageManager.GetCarHandle(i), j, 3.0f);
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < MV1GetMaterialNum(stageManager.GetCloudHandle(i)); j++) {
			MV1SetMaterialDifColor(stageManager.GetCloudHandle(i), j, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
			MV1SetMaterialAmbColor(stageManager.GetCloudHandle(i), j, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
			MV1SetMaterialSpcColor(stageManager.GetCloudHandle(i), j, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
			MV1SetMaterialEmiColor(stageManager.GetCloudHandle(i), j, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
			MV1SetMaterialSpcPower(stageManager.GetCloudHandle(i), j, 3.0f);
		}
	}
}

void Base::Initialization() {
	// 座標やスコア等をリセットする
	player.Initialization();
	cameraLight.Initialization();
	stageManager.Initialization();
	scoreManager.SetScore(0);
	scoreManager.SetViewScore(0);
}

void Base::CleanUp() {
	scoreManager.SaveHighScore();
	// フォントデータを削除
	for (int i = 0; i < FONT_TYPE_NUM; i++) {
		DeleteFontToHandle(fontData[i].handle);
	}
	RemoveFontResourceExA("", FR_PRIVATE, NULL);
}