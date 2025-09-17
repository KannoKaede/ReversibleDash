#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"

SCREEN_TYPE currentScreenType;
SCREEN_TYPE nextScreenType;
bool isFading = true;
int alphaValue = 255;
int fadeStartCount;
FADE_STATE fadeState;
int buttonPosX = 0;
int buttonPosY = 0;
int buttonMap[SCREEN_BUTTON_NUM][BUTTON_NUM_Y][BUTTON_NUM_X] = {
	{	// TITLE
		{1,0,0,0},
		{1,0,0,0},
		{1,0,0,0},
		{0,0,0,0}
	},
	{	// STAGESELECT
		{1,1,1,0},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	},
	{	// PAUSE
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	},
	{	// GAMEOVER
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	},
	{	// STAGECLEAR
		{1,1,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	}
};
int font;
/// <summary> 画面の状態に対応したUIを表示するメソッド </summary>
void ScreenUISwithing()
{
	int  backScreen = GetColor(230, 230, 230);
	int brack = GetColor(0, 0, 0);
	int gray = GetColor(200, 200, 200);
	int green = GetColor(0, 255, 128);
	switch (currentScreenType)
	{
	case TITLE:
		DrawStringToHandle(screenWidth * 0.18, screenHeight * 0.14, "ReversibleDash", brack, font);
		DrawBox(screenWidth * 0.32, screenHeight * 0.4, screenWidth * 0.68, screenHeight * 0.53, buttonMap[TITLE][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(230, 230, "GAME START", brack, normalFontHandle);
		DrawBox(180, 290, 460, 350, buttonMap[TITLE][1][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(210, 310, "STAGE SELECT", brack, normalFontHandle);
		DrawBox(180, 370, 460, 430, buttonMap[TITLE][2][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(240, 390, "GAME QUIT", brack, normalFontHandle);
		DrawStringToHandle(500, 450, "Ver_0.0.00.00", brack, smallFontHandle);
		break;
	case STAGESELECT:
		DrawStringToHandle(30, 70, "ReversibleDash", brack, bigFontHandle);
		DrawBox(90, 190, 230, 260, buttonMap[STAGESELECT][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(130, 265, "STAGE1", brack, smallFontHandle);
		DrawBox(250, 190, 390, 260, buttonMap[STAGESELECT][0][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(290, 265, "STAGE2", brack, smallFontHandle);
		DrawBox(410, 190, 550, 260, buttonMap[STAGESELECT][0][2] == 2 ? green : gray, TRUE);
		DrawStringToHandle(450, 265, "STAGE3", brack, smallFontHandle);
		DrawBox(90, 330, 230, 400, buttonMap[STAGESELECT][1][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(130, 405, "STAGE4", brack, smallFontHandle);
		DrawBox(250, 330, 390, 400, buttonMap[STAGESELECT][1][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(290, 405, "STAGE5", brack, smallFontHandle);
		DrawBox(410, 330, 550, 400, buttonMap[STAGESELECT][1][2] == 2 ? green : gray, TRUE);
		DrawStringToHandle(450, 405, "STAGE6", brack, smallFontHandle);
		DrawBox(570, 350, 620, 400, buttonMap[STAGESELECT][1][3] == 2 ? green : gray, TRUE);
		DrawStringToHandle(574, 370, "BACK", brack, smallFontHandle);
		break;
	case PAUSE:
		DrawBox(130, 100, 510, 370, backScreen, TRUE);
		DrawStringToHandle(210, 150, "PAUSE", brack, bigFontHandle);
		DrawBox(170, 290, 300, 350, buttonMap[PAUSE][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(178, 310, "RESUME", brack, normalFontHandle);
		DrawBox(340, 290, 470, 350, buttonMap[PAUSE][0][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(358, 310, "TITLE", brack, normalFontHandle);
		break;
	case GAMEOVER:
		DrawBox(80, 70, 580, 400, backScreen, TRUE);
		DrawStringToHandle(150, 120, "GAMEOVER", brack, bigFontHandle);
		DrawBox(120, 320, 300, 370, buttonMap[GAMEOVER][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(165, 335, "RETRY", brack, normalFontHandle);
		DrawBox(340, 320, 520, 370, buttonMap[GAMEOVER][0][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(383, 335, "TITLE", brack, normalFontHandle);
		DrawStringToHandle(165, 210, "SCORE", brack, normalFontHandle);
		DrawFormatStringToHandle(155, 250, brack, normalFontHandle, "%06d", score);
		break;
	case STAGECLEAR:
		DrawBox(80, 70, 580, 400, backScreen, TRUE);
		DrawStringToHandle(110, 120, "STAGECLEAR", brack, bigFontHandle);
		DrawBox(120, 320, 300, 370, buttonMap[STAGECLEAR][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(118, 335, "NEXT STAGE", brack, normalFontHandle);
		DrawBox(340, 320, 520, 370, buttonMap[STAGECLEAR][0][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(383, 335, "TITLE", brack, normalFontHandle);
		DrawStringToHandle(165, 210, "SCORE", brack, normalFontHandle);
		DrawFormatStringToHandle(155, 250, brack, normalFontHandle, "%06d", score);
		DrawStringToHandle(345, 210, "HIGHSCORE", brack, normalFontHandle);
		DrawFormatStringToHandle(370, 250, brack, normalFontHandle, "%06d", highScore[stageNumber]);
		break;
	case INGAME:
		// インゲームのUIを用意したらここに配置
		DrawFormatStringToHandle(5, 465, brack, smallFontHandle, "SCORE:%06d", inGameVewScore);
		break;
	default:
		printfDx("ERROR: ScreenUISwithing%d\n", currentScreenType);
		break;
	}
}

/// <summary> フェード演出の制御を行うメソッド：フェード演出中はFlagを立てて他の処理を制御 </summary>
void ScreenFadeControl() {
	switch (fadeState)
	{
	case FADEOUT:		// 画面を暗転：処理開始時にフラグを立てる
		if (!isFading) {
			isFading = true;
		}
		if (alphaValue == 255) {
			fadeState = FADEWAIT;
		}
		ScreenFade(FADE_SPEED);
		break;
	case FADEIN:	// 画面を明転：処理終了時にフラグを折る
		if (alphaValue == 0) {
			isFading = false;
		}
		ScreenFade(-FADE_SPEED);
		break;
	case FADEWAIT:		// 指定時間待機：待機中にUIの切り替えを行う
		if (fadeStartCount == 0) {
			fadeStartCount = GetNowCount();
			currentScreenType = nextScreenType;	// 変数の中身を変えてUIを切り替え
		}
		ScreenFade(0);
		if ((fadeStartCount + FADE_WAIT_TIME) <= GetNowCount()) {
			fadeState = FADEIN;
			fadeStartCount = 0;

			// ボタンの選択位置をリセット
			buttonPosY = 0;
			buttonPosX = 0;
			// タイトルでステージナンバーをリセット
			if (currentScreenType == TITLE) {
				stageNumber = 0;
			}
		}
		break;
	}
}

/// <summary> フェード処理を行うメソッド </summary>
/// <param name="fadeSpeed">フェード速度</param>
void ScreenFade(int fadeSpeed)
{
	// SetDrawBlendMode設定し直すことでフェード画面のみの透明度を変更する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	alphaValue += fadeSpeed;
	if (alphaValue < 0) alphaValue = 0;
	if (alphaValue > 255) alphaValue = 255;
	DrawBox(0, 0, screenWidth, screenHeight, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int buttonMoveCount;	// ボタン移動の待機時間用カウンタ
/// <summary> ボタンの選択位置を変更するメソッド </summary>
void ButtonChanged() {
	int x = 0, y = 0;
	if (!isFading) {
		if (CheckHitKey(KEY_INPUT_UP))y = -1;
		if (CheckHitKey(KEY_INPUT_DOWN))y = 1;
		if (CheckHitKey(KEY_INPUT_LEFT))x = -1;
		if (CheckHitKey(KEY_INPUT_RIGHT))x = 1;
	}

	// ボタンの選択位置を変更：指定フレーム経つまで移動不可
	if (x != 0 || y != 0) {
		buttonMoveCount++;
		if (buttonMoveCount % WAIT_BUTTON_MOVE == 1) {
			buttonPosX += x;
			buttonPosY += y;
		}
	}
	else {
		buttonMoveCount = 0;
	}

	// 移動先にボタンが無かったら移動リセットする
	if (buttonMap[currentScreenType][buttonPosY][buttonPosX] == 0) {
		buttonPosX -= x;
		buttonPosY -= y;
	}

	// ボタンの状態を更新。最初にボタンをすべて非選択状態にしてから、選択中のボタンだけ選択状態にする
	for (int z = 0; z < SCREEN_BUTTON_NUM; z++) {
		for (int y = 0; y < BUTTON_NUM_Y; y++) {
			for (int x = 0; x < BUTTON_NUM_X; x++) {
				buttonMap[z][y][x] = buttonMap[z][y][x] == 0 ? 0 : 1;
			}
		}
		buttonMap[currentScreenType][buttonPosY][buttonPosX] = 2;
	}
}

int buttonClickCount;	// ボタン押下の待機時間用カウンタ
/// <summary> ボタンが押されたときの処理を行うメソッド </summary>
void CheckButtonPressed() {
	if (CheckHitKey(KEY_INPUT_SPACE) && currentScreenType != INGAME) {
		if (buttonMap[TITLE][0][0] == 2) {	// タイトル：ゲーム開始
			ButtonPressedProcessing(INGAME, true);
			stageNumber = 1;
		}
		if (buttonMap[TITLE][1][0] == 2) {	// タイトル：ステージセレクトに遷移
			ButtonPressedProcessing(STAGESELECT, false);
		}
		if (buttonMap[TITLE][2][0] == 2) {	// タイトル：ゲームを終了
			isGameQuit = true;
			return;
		}
		for (int y = 0; y < BUTTON_NUM_Y - 1; y++) {
			for (int x = 0; x < BUTTON_NUM_X - 1; x++) {
				if (buttonMap[STAGESELECT][y][x] == 2) {	// ステージセレクト：ステージ選択ボタン(これで変数用意すれば選んだステージを調べられるはず）
					ButtonPressedProcessing(INGAME, true);
					stageNumber = y * 3 + x + 1;
				}
			}
		}
		if (buttonMap[STAGESELECT][1][3] == 2) {	// ステージセレクトタイトルに戻る
			ButtonPressedProcessing(TITLE, false);
		}
		if (buttonMap[PAUSE][0][0] == 2) {	// ポーズ：ゲーム再開
			ButtonPressedProcessing(INGAME, false);
		}
		if (buttonMap[PAUSE][0][1] == 2) {	// ポーズ：タイトルに戻る
			ButtonPressedProcessing(TITLE, true);
		}
		if (buttonMap[GAMEOVER][0][0] == 2) {	// ゲームオーバー：ゲーム再開
			ButtonPressedProcessing(INGAME, true);
		}
		if (buttonMap[GAMEOVER][0][1] == 2) {	// ゲームオーバー：タイトルに戻る
			ButtonPressedProcessing(TITLE, true);
		}
		if (buttonMap[STAGECLEAR][0][0] == 2) {	// ステージクリア：ゲーム再開
			ButtonPressedProcessing(INGAME, true);
			stageNumber++;
		}
		if (buttonMap[STAGECLEAR][0][1] == 2) {	// ステージクリア：タイトルに戻る
			ButtonPressedProcessing(TITLE, true);
		}
	}
	else if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		if (currentScreenType == INGAME) {
			ButtonPressedProcessing(PAUSE, false);
		}
	}
	else {
		buttonClickCount = 0;
		return;

	}
}

/// <summary>
/// ボタンが押された際の共通処理
/// </summary>
/// <param name="nextScreen"> 次の画面</param>
/// <param name="buttonScreen"> ボタンを押した画面</param>
/// <param name="y"> ボタンの座標Y</param>
/// <param name="x"> ボタンの座標X</param>
/// <param name="isFade"> true = フェード処理を行う false = 即座に切り替える</param>
void ButtonPressedProcessing(SCREEN_TYPE nextScreen, bool isFade) {
	buttonClickCount++;
	if (buttonClickCount % 100 == 1) {
		nextScreenType = nextScreen;
		if (isFade) {
			fadeState = FADEOUT;
		}
		else {
			buttonPosY = 0;
			buttonPosX = 0;
			currentScreenType = nextScreen;
		}
	}
}
