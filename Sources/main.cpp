#include "3dSetting.h"
#include "Audio.h"
#include "Button.h"
#include "Input.h"
#include "Main.h"
#include "Player.h"
#include "Score.h"
#include "Stage.h"
#include "UI.h"

Player player(START_PLAYER_POS, START_PLAYER_ROT, START_PLAYER_SCALE, FIRST_SPEED);
Camera camera;
Light light;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	base.SetScreenSize();	// 画面の解像度に応じて画面サイズを変更	: ここに置かないと画像が描画できなくなる
	if (DxLib_Init() == -1)return -1;	// DXライブラリ初期化処理
	base.SetUp();	// ゲームの初期設定を行う
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();	// 画面をクリア
		CheckAllKeyState();	// 全キーの状態をチェック
		if (base.IsDrawInGame()) {
			// カメラ、ライト、プレイヤーの描画
			player.Move();
			player.Jump();
			camera.Move(player);
			stageManager.Draw(player);
			InGameScoreView();
			if (!base.isGameStop && stageManager.IsClear(player.GetPosition().x)) {
				HighScoreCheck();
				ChangeUIState(CLEAR, SCREENSETUP);
			}
		}

		if (!isFading) {
			if (currentScreenType == TITLE || currentScreenType == STAGESELECT)
				PlayBGM(bgm[TITLE_BGM]);
			if (currentScreenType == INGAME)
				PlayBGM(bgm[INGAME_BGM]);
			if (CheckHitKeyDown(KEY_INPUT_ESCAPE))  ChangeUIState(PAUSE, SCREENSETUP);
		}

		DrawUI(player);	//	UIを描画
		if (currentScreenType != INGAME) {
			buttonManager.ButtonMovement();	//  ボタンの移動
			buttonManager.ButtonPressed();	// ボタンが押されたときの処理
		}
		isFading = ScreenFadeControl();	// フェード処理：UIより後に処理を行わないとUIがフェードの前に出てきてしまう

		ScreenFlip();

		clsDx();	// デバッグ用文字を消す
		WaitTimer(16);
	}

	base.CleanUp();	// ゲーム終了処理
	DxLib_End();
	return 0;
}

void Base::SetUp() {
	SetBackgroundColor(160, 216, 239);	// 背景色を空色に設定：リファクタリング→スカイボックスに変更するかも
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
	UISetUp();
	AudioSetUp();
	stageManager.SetUp();
	player.SetUp();
	camera.SetUp();
	light.SetUp();
	LoadHighScore();

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
}

void Base::Initialization() {
	// 座標やスコア等をリセットする
	player.Initialization();
	camera.Initialization();
	stageManager.Initialization();
	score = 0;
	vewScore = 0;
}

void Base::CleanUp() {
	SaveHighScore();
	// フォントデータを削除
	for (int i = 0; i < FONT_TYPE_NUM; i++) {
		DeleteFontToHandle(fontData[i].handle);
	}
	RemoveFontResourceExA("", FR_PRIVATE, NULL);
}