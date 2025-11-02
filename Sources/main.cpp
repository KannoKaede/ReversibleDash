#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
#include "Button.h"
#include "Player.h"
#include "3dSetting.h"
#include "Input.h"

Player player(START_PLAYER_POS, START_PLAYER_ROT, START_PLAYER_SCALE, FIRST_SPEED);
Camera camera(START_CAMERA_POS, START_CAMERA_LOOK);
Light light(START_LIGHT_POS);
Stage stage;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	SetScreenSize();	// 画面の解像度に応じて画面サイズを変更	: ここに置かないと画像が描画できなくなる
	if (DxLib_Init() == -1)return -1;	// DXライブラリ初期化処理
	GameSetUp();	// ゲームの初期設定を行う
	SetDrawScreen(DX_SCREEN_BACK);	// 描画先を裏画面に指定
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();	// 画面をクリア
		CheckAllKeyState();	// 全キーの状態をチェック
		if (IsDrawInGame()) {
			// カメラ、ライト、プレイヤーの描画
			player.Move();
			player.Jump();
			camera.Move(player);
			stage.Draw(player);
			InGameScoreView();
			if (!isGameStop && stage.IsGoal(player.GetPosition().x)) {
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
			ButtonMovement();	//  ボタンの移動
			ButtonPressed();	// ボタンが押されたときの処理
		}
		isFading = ScreenFadeControl();	// フェード処理：UIより後に処理を行わないとUIがフェードの前に出てきてしまう

		ScreenFlip();

		clsDx();	// デバッグ用文字を消す
		WaitTimer(16);
	}

	GameCleanUp();	// ゲーム終了処理
	DxLib_End();
	return 0;
}

void GameSetUp() {
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
	stage.SetUp();
	player.SetUp();
	camera.SetUp();
	light.SetUp();
	LoadHighScore();

	// モデルの光の当たり方を設定：DXライブラリの初期設定のままだと暗すぎるので明るくする
	for (int i = 0; i < MV1GetMaterialNum(stage.GetBackStageHandle()); i++)	// ステージのモデル
	{
		MV1SetMaterialDifColor(stage.GetBackStageHandle(), i, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
		MV1SetMaterialAmbColor(stage.GetBackStageHandle(), i, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
		MV1SetMaterialSpcColor(stage.GetBackStageHandle(), i, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
		MV1SetMaterialEmiColor(stage.GetBackStageHandle(), i, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
		MV1SetMaterialSpcPower(stage.GetBackStageHandle(), i, 3.0f);
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

void GameInitialization() {
	// 座標やスコア等をリセットする
	player.Initialization();
	camera.Initialization();
	stage.Initialization();
	score = 0;
	vewScore = 0;
}

void GameCleanUp() {
	SaveHighScore();
	// フォントデータを削除
	for (int i = 0; i < FONT_TYPE_NUM; i++) {
		DeleteFontToHandle(fontData[i].handle);
	}
	RemoveFontResourceExA("", FR_PRIVATE, NULL);
}