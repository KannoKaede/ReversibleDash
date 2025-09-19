#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"

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
int bigFontHandle;
int normalFontHandle;
int smallFontHandle;
std::string previousText;
std::string drawText = START_COUNTDOWN_1;

void fontSetting() {
	AddFontResourceExA("KaqookanV2.ttf", FR_PRIVATE, NULL);
	bigFontHandle = CreateFontToHandle("N4カクーカンV2", screenWidth / 18, 5, DX_FONTTYPE_ANTIALIASING);
	normalFontHandle = CreateFontToHandle("N4カクーカンV2", screenWidth / 30, 3, DX_FONTTYPE_ANTIALIASING);
	smallFontHandle = CreateFontToHandle("N4カクーカンV2", screenWidth / 60, 1, DX_FONTTYPE_ANTIALIASING);
}



int brack = GetColor(0, 0, 0);
/// <summary> 画面の状態に対応したUIを表示するメソッド </summary>
void ScreenUISwithing()
{
	int  backScreen = GetColor(230, 230, 230);
	int gray = GetColor(200, 200, 200);
	int green = GetColor(0, 255, 128);
	switch (currentScreenType)
	{
	case TITLE:
		DrawStringToHandle(screenWidth * 0.18, screenHeight * 0.16, "ReversibleDash", brack, bigFontHandle);
		DrawBox(screenWidth * 0.32, screenHeight * 0.4, screenWidth * 0.68, screenHeight * 0.53, buttonMap[TITLE][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.36, screenHeight * 0.435, "GAME START", brack, normalFontHandle);
		DrawBox(screenWidth * 0.32, screenHeight * 0.6, screenWidth * 0.68, screenHeight * 0.73, buttonMap[TITLE][1][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.33, screenHeight * 0.635, "STAGE SELECT", brack, normalFontHandle);
		DrawBox(screenWidth * 0.32, screenHeight * 0.8, screenWidth * 0.68, screenHeight * 0.93, buttonMap[TITLE][2][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.38, screenHeight * 0.835, "GAME QUIT", brack, normalFontHandle);
		DrawStringToHandle(screenWidth * 0.8, screenHeight * 0.95, "Ver_0.0.00.00", brack, smallFontHandle);

		break;
	case STAGESELECT:
		DrawStringToHandle(screenWidth * 0.24, screenHeight * 0.16, "STAGESELECT", brack, bigFontHandle);
		DrawBox(screenWidth * 0.19, screenHeight * 0.32, screenWidth * 0.37, screenHeight * 0.5, buttonMap[STAGESELECT][0][0] == 2 ? green : gray, TRUE);
		DrawBox(screenWidth * 0.28, screenHeight * 0.5, screenWidth * 0.37, screenHeight * 0.535, buttonMap[STAGESELECT][0][0] == 2 ? green : gray, TRUE);
		DrawTriangleAA(screenWidth * 0.28, screenHeight * 0.49, screenWidth * 0.28, screenHeight * 0.535, screenWidth * 0.26, screenHeight * 0.49, buttonMap[STAGESELECT][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.28, screenHeight * 0.5, "STAGE1", brack, smallFontHandle);
		DrawBox(screenWidth * 0.41, screenHeight * 0.32, screenWidth * 0.59, screenHeight * 0.5, buttonMap[STAGESELECT][0][1] == 2 ? green : gray, TRUE);
		DrawBox(screenWidth * 0.5, screenHeight * 0.5, screenWidth * 0.59, screenHeight * 0.535, buttonMap[STAGESELECT][0][1] == 2 ? green : gray, TRUE);
		DrawTriangleAA(screenWidth * 0.5, screenHeight * 0.49, screenWidth * 0.5, screenHeight * 0.535, screenWidth * 0.48, screenHeight * 0.49, buttonMap[STAGESELECT][0][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.5, screenHeight * 0.5, "STAGE2", brack, smallFontHandle);
		DrawBox(screenWidth * 0.63, screenHeight * 0.32, screenWidth * 0.81, screenHeight * 0.5, buttonMap[STAGESELECT][0][2] == 2 ? green : gray, TRUE);
		DrawBox(screenWidth * 0.72, screenHeight * 0.5, screenWidth * 0.81, screenHeight * 0.535, buttonMap[STAGESELECT][0][2] == 2 ? green : gray, TRUE);
		DrawTriangleAA(screenWidth * 0.72, screenHeight * 0.49, screenWidth * 0.72, screenHeight * 0.535, screenWidth * 0.7, screenHeight * 0.49, buttonMap[STAGESELECT][0][2] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.72, screenHeight * 0.5, "STAGE3", brack, smallFontHandle);
		DrawBox(screenWidth * 0.19, screenHeight * 0.65, screenWidth * 0.37, screenHeight * 0.83, buttonMap[STAGESELECT][1][0] == 2 ? green : gray, TRUE);
		DrawBox(screenWidth * 0.28, screenHeight * 0.83, screenWidth * 0.37, screenHeight * 0.865, buttonMap[STAGESELECT][1][0] == 2 ? green : gray, TRUE);
		DrawTriangleAA(screenWidth * 0.28, screenHeight * 0.82, screenWidth * 0.28, screenHeight * 0.865, screenWidth * 0.26, screenHeight * 0.82, buttonMap[STAGESELECT][1][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.28, screenHeight * 0.83, "STAGE4", brack, smallFontHandle);
		DrawBox(screenWidth * 0.41, screenHeight * 0.65, screenWidth * 0.59, screenHeight * 0.83, buttonMap[STAGESELECT][1][1] == 2 ? green : gray, TRUE);
		DrawBox(screenWidth * 0.5, screenHeight * 0.83, screenWidth * 0.59, screenHeight * 0.865, buttonMap[STAGESELECT][1][1] == 2 ? green : gray, TRUE);
		DrawTriangleAA(screenWidth * 0.5, screenHeight * 0.82, screenWidth * 0.5, screenHeight * 0.865, screenWidth * 0.48, screenHeight * 0.82, buttonMap[STAGESELECT][1][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.5, screenHeight * 0.83, "STAGE5", brack, smallFontHandle);
		DrawBox(screenWidth * 0.63, screenHeight * 0.65, screenWidth * 0.81, screenHeight * 0.83, buttonMap[STAGESELECT][1][2] == 2 ? green : gray, TRUE);
		DrawBox(screenWidth * 0.72, screenHeight * 0.83, screenWidth * 0.81, screenHeight * 0.865, buttonMap[STAGESELECT][1][2] == 2 ? green : gray, TRUE);
		DrawTriangleAA(screenWidth * 0.72, screenHeight * 0.82, screenWidth * 0.72, screenHeight * 0.865, screenWidth * 0.7, screenHeight * 0.82, buttonMap[STAGESELECT][1][2] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.72, screenHeight * 0.83, "STAGE6", brack, smallFontHandle);
		DrawBox(screenWidth * 0.84, screenHeight * 0.75, screenWidth * 0.93, screenHeight * 0.83, buttonMap[STAGESELECT][1][3] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.857, screenHeight * 0.775, "BACK", brack, smallFontHandle);
		break;
	case PAUSE:
		DrawBox(screenWidth * 0.25, screenHeight * 0.25, screenWidth * 0.75, screenHeight * 0.75, backScreen, TRUE);
		DrawStringToHandle(screenWidth * 0.37, screenHeight * 0.32, "PAUSE", brack, bigFontHandle);
		DrawBox(screenWidth * 0.275, screenHeight * 0.58, screenWidth * 0.475, screenHeight * 0.68, buttonMap[PAUSE][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.287, screenHeight * 0.6, "RESUME", brack, normalFontHandle);
		DrawBox(screenWidth * 0.525, screenHeight * 0.58, screenWidth * 0.725, screenHeight * 0.68, buttonMap[PAUSE][0][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.555, screenHeight * 0.6, "TITLE", brack, normalFontHandle);
		break;
	case GAMEOVER:
		DrawBox(screenWidth * 0.23, screenHeight * 0.18, screenWidth * 0.77, screenHeight * 0.82, backScreen, TRUE);
		DrawStringToHandle(screenWidth * 0.3, screenHeight * 0.25, "GAMEOVER", brack, bigFontHandle);
		DrawStringToHandle(screenWidth * 0.305, screenHeight * 0.43, "SCORE", brack, normalFontHandle);
		DrawFormatStringToHandle(screenWidth * 0.29, screenHeight * 0.515, brack, normalFontHandle, "%06d", score);
		DrawBox(screenWidth * 0.275, screenHeight * 0.65, screenWidth * 0.475, screenHeight * 0.74, buttonMap[GAMEOVER][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.302, screenHeight * 0.665, "RETRY", brack, normalFontHandle);
		DrawBox(screenWidth * 0.525, screenHeight * 0.65, screenWidth * 0.725, screenHeight * 0.74, buttonMap[GAMEOVER][0][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.555, screenHeight * 0.665, "TITLE", brack, normalFontHandle);
		break;
	case STAGECLEAR:
		DrawBox(screenWidth * 0.23, screenHeight * 0.18, screenWidth * 0.77, screenHeight * 0.82, backScreen, TRUE);
		DrawStringToHandle(screenWidth * 0.25, screenHeight * 0.25, "STAGECLEAR", brack, bigFontHandle);
		DrawStringToHandle(screenWidth * 0.305, screenHeight * 0.43, "SCORE", brack, normalFontHandle);
		DrawFormatStringToHandle(screenWidth * 0.29, screenHeight * 0.515, brack, normalFontHandle, "%06d", score);
		DrawStringToHandle(screenWidth * 0.5, screenHeight * 0.43, "HIGHSCORE", brack, normalFontHandle);
		DrawFormatStringToHandle(screenWidth * 0.54, screenHeight * 0.515, brack, normalFontHandle, "%06d", highScore[stageNumber]);
		DrawBox(screenWidth * 0.275, screenHeight * 0.65, screenWidth * 0.475, screenHeight * 0.74, buttonMap[STAGECLEAR][0][0] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.32, screenHeight * 0.665, "NEXT", brack, normalFontHandle);
		DrawBox(screenWidth * 0.525, screenHeight * 0.65, screenWidth * 0.725, screenHeight * 0.74, buttonMap[STAGECLEAR][0][1] == 2 ? green : gray, TRUE);
		DrawStringToHandle(screenWidth * 0.555, screenHeight * 0.665, "TITLE", brack, normalFontHandle);
		break;
	case INGAME:
		// インゲームのUIを用意したらここに配置
		DrawFormatStringToHandle(screenWidth * 0.01, screenHeight * 0.95, brack, smallFontHandle, "SCORE:%06d", inGameVewScore);
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
			fadeState = NONE;
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
	default:
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
		if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))y = -1;
		if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))y = 1;
		if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))x = -1;
		if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))x = 1;
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
	if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN)) {
		if (buttonMap[TITLE][0][0] == 2) {	// タイトル：ゲーム開始
			ButtonPressedProcessing(INGAME, true);
			stageNumber = 1;
			isGameStop = true;
			isStartCountDown = true;
			drawText = START_COUNTDOWN_1;
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
					isGameStop = true;
					isStartCountDown = true;
					drawText = START_COUNTDOWN_1;
				}
			}
		}
		if (buttonMap[STAGESELECT][1][3] == 2) {	// ステージセレクトタイトルに戻る
			ButtonPressedProcessing(TITLE, false);
		}
		if (buttonMap[PAUSE][0][0] == 2) {	// ポーズ：ゲーム再開
			ButtonPressedProcessing(INGAME, false);
			isStartCountDown = true;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
		}
		if (buttonMap[PAUSE][0][1] == 2) {	// ポーズ：タイトルに戻る
			ButtonPressedProcessing(TITLE, true);
		}
		if (buttonMap[GAMEOVER][0][0] == 2) {	// ゲームオーバー：ゲーム再開
			ButtonPressedProcessing(INGAME, true);
			isStartCountDown = true;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
		}
		if (buttonMap[GAMEOVER][0][1] == 2) {	// ゲームオーバー：タイトルに戻る
			ButtonPressedProcessing(TITLE, true);
		}
		if (buttonMap[STAGECLEAR][0][0] == 2) {	// ステージクリア：ゲーム再開
			ButtonPressedProcessing(INGAME, true);
			stageNumber++;
			isGameStop = true;
			isStartCountDown = true;
			drawText = START_COUNTDOWN_1;
		}
		if (buttonMap[STAGECLEAR][0][1] == 2) {	// ステージクリア：タイトルに戻る
			ButtonPressedProcessing(TITLE, true);
		}
	}
	else if (CheckHitKey(KEY_INPUT_ESCAPE) && !isStartCountDown) {
		if (currentScreenType == INGAME) {
			ButtonPressedProcessing(PAUSE, false);
			isGameStop = true;
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

int count;
int fadeSpeed = 3;
void DrawStartCountDown() {
	if (previousText != drawText) {
		previousText = drawText;
		count = 0;
	}
	if (++count <= 40) {
		return;
	}
	alphaValue += fadeSpeed;
	if (alphaValue <= 0) {
		alphaValue = 0;
		fadeSpeed = FADE_SPEED;
		if (drawText != START_COUNTDOWN_2) {
			drawText = START_COUNTDOWN_2;
		}
		else {
			isStartCountDown = false;
			isGameStop = false;
		}
	}
	if (alphaValue >= 255) {
		alphaValue = 255;
		WaitTimer(300);
		fadeSpeed = drawText == START_COUNTDOWN_2 ? -FADE_SPEED * 2.5 : -FADE_SPEED / 1.5;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	DrawStringToHandle(screenWidth * 0.24, screenHeight * 0.16, const_cast<char*>(drawText.c_str()), brack, bigFontHandle);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}