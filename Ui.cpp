#include "DxLib.h"
#include "main.h"
#include "UI.h"

/// <summary> 画面の状態に対応したUIを表示するメソッド </summary>
void ScreenUISwithing()
{
	int  brack = GetColor(0, 0, 0);
	int gray = GetColor(200, 200, 200);
	int green = GetColor(0, 255, 128);
	switch (currentScreenType)
	{
	case TITLE:
		printfDx("TITLE\n");
		DrawBox(180, 210, 460, 270, buttonMap[TITLE][0][0] == 2 ? green : gray, TRUE);
		DrawBox(180, 290, 460, 350, buttonMap[TITLE][1][0] == 2 ? green : gray, TRUE);
		DrawBox(180, 370, 460, 430, buttonMap[TITLE][2][0] == 2 ? green : gray, TRUE);
		break;
	case STAGESELECT:
		printfDx("STAGESELECT\n");
		DrawBox(90, 150, 230, 220, buttonMap[STAGESELECT][0][0] == 2 ? green : gray, TRUE);
		DrawBox(250, 150, 390, 220, buttonMap[STAGESELECT][0][1] == 2 ? green : gray, TRUE);
		DrawBox(410, 150, 550, 220, buttonMap[STAGESELECT][0][2] == 2 ? green : gray, TRUE);
		DrawBox(90, 260, 230, 330, buttonMap[STAGESELECT][1][0] == 2 ? green : gray, TRUE);
		DrawBox(250, 260, 390, 330, buttonMap[STAGESELECT][1][1] == 2 ? green : gray, TRUE);
		DrawBox(410, 260, 550, 330, buttonMap[STAGESELECT][1][2] == 2 ? green : gray, TRUE);
		DrawBox(90, 370, 230, 440, buttonMap[STAGESELECT][2][0] == 2 ? green : gray, TRUE);
		DrawBox(250, 370, 390, 440, buttonMap[STAGESELECT][2][1] == 2 ? green : gray, TRUE);
		DrawBox(410, 370, 550, 440, buttonMap[STAGESELECT][2][2] == 2 ? green : gray, TRUE);
		DrawBox(570, 380, 620, 430, buttonMap[STAGESELECT][2][3] == 2 ? green : gray, TRUE);
		break;
	case PAUSE:
		printfDx("PAUSE\n");
		DrawBox(130, 100, 510, 370, brack, TRUE);
		DrawBox(170, 290, 300, 350, buttonMap[PAUSE][0][0] == 2 ? green : gray, TRUE);
		DrawBox(340, 290, 470, 350, buttonMap[PAUSE][0][1] == 2 ? green : gray, TRUE);
		break;
	case GAMEOVER:
		printfDx("GAMEOVER\n");
		DrawBox(80, 70, 580, 400, brack, TRUE);
		DrawBox(120, 320, 300, 370, buttonMap[GAMEOVER][0][0] == 2 ? green : gray, TRUE);
		DrawBox(340, 320, 520, 370, buttonMap[GAMEOVER][0][1] == 2 ? green : gray, TRUE);
		break;
	case STAGECLEAR:
		printfDx("STAGECLEAR\n");
		DrawBox(80, 70, 580, 400, brack, TRUE);
		DrawBox(120, 320, 300, 370, buttonMap[STAGECLEAR][0][0] == 2 ? green : gray, TRUE);
		DrawBox(340, 320, 520, 370, buttonMap[STAGECLEAR][0][1] == 2 ? green : gray, TRUE);
		break;
	case INGAME:
		printfDx("INGAME\n");
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
	DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int count;	// ボタン移動の待機時間用カウンタ
/// <summary> ボタンの選択位置を変更するメソッド </summary>
void ButtonChanged() {
	int x = 0, y = 0;
	if (CheckHitKey(KEY_INPUT_UP))y = -1;
	if (CheckHitKey(KEY_INPUT_DOWN))y = 1;
	if (CheckHitKey(KEY_INPUT_LEFT))x = -1;
	if (CheckHitKey(KEY_INPUT_RIGHT))x = 1;

	// ボタンの選択位置を変更：指定フレーム経つまで移動不可
	if (x != 0 || y != 0) {
		count++;
		if (count % WAIT_BUTTON_MOVE == 1) {
			buttonPosX += x;
			buttonPosY += y;
		}
	}
	else {
		count = 0;
	}

	// 移動先にボタンが無かったら移動リセットする
	if (buttonMap[currentScreenType][buttonPosY][buttonPosX] == 0) {
		buttonPosX -= x;
		buttonPosY -= y;
	}

	// ボタンの状態を更新最初にボタンをすべて非選択状態にしてから、選択中のボタンだけ選択状態にする
	for (int y = 0; y < BUTTON_NUM_Y; y++) {
		for (int x = 0; x < BUTTON_NUM_X; x++) {
			buttonMap[currentScreenType][y][x] = buttonMap[currentScreenType][y][x] == 0 ? 0 : 1;
		}
	}
	if (!isFading) {
		buttonMap[currentScreenType][buttonPosY][buttonPosX] = 2;
	}
}

/// <summary> ボタンが押されたときの処理を行うメソッド </summary>
void OnClickSwitchUI() {
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		if (buttonMap[TITLE][0][0] == 2) {	// タイトル：ゲーム開始
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			buttonMap[TITLE][0][0] = 1;
			stageNumber = 1;
		}
		if (buttonMap[TITLE][1][0] == 2) {	// タイトル：ステージセレクトに遷移
			nextScreenType = STAGESELECT;
			fadeState = FADEOUT;
			buttonMap[TITLE][1][0] == 1;
		}
		if (buttonMap[TITLE][2][0] == 2) {	// タイトル：ゲームを終了
			isGameQuit = true;
			return;
		}
		for (int y = 0; y < BUTTON_NUM_Y - 1; y++) {
			for (int x = 0; x < BUTTON_NUM_X - 1; x++) {
				if (buttonMap[STAGESELECT][y][x] == 2) {	// ステージセレクト：ステージ選択ボタン(これで変数用意すれば選んだステージを調べられるはず）
					nextScreenType = INGAME;
					fadeState = FADEOUT;
					stageNumber = y * 3 + x + 1;
				}
			}
		}
		if (buttonMap[STAGESELECT][2][3] == 2) {	// ステージセレクトタイトルに戻る
			nextScreenType = TITLE;
			fadeState = FADEOUT;
			buttonMap[STAGESELECT][2][3] = 1;
		}
		if (buttonMap[PAUSE][0][0] == 2) {	// ポーズ：ゲーム再開
			nextScreenType = INGAME;
			currentScreenType = nextScreenType;
			buttonMap[PAUSE][0][0] = 1;
		}
		if (buttonMap[PAUSE][0][1] == 2) {	// ポーズ：タイトルに戻る
			nextScreenType = TITLE;
			fadeState = FADEOUT;
			buttonMap[PAUSE][0][1] = 1;
		}
		if (buttonMap[GAMEOVER][0][0] == 2) {	// ゲームオーバー：ゲーム再開
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			buttonMap[GAMEOVER][0][0] = 1;
		}
		if (buttonMap[GAMEOVER][0][1] == 2) {	// ゲームオーバー：タイトルに戻る
			nextScreenType = TITLE;
			fadeState = FADEOUT;
			buttonMap[GAMEOVER][0][1] = 1;
		}
		if (buttonMap[STAGECLEAR][0][0] == 2) {	// ステージクリア：ゲーム再開
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			buttonMap[STAGECLEAR][0][0] = 1;
		}
		if (buttonMap[STAGECLEAR][0][1] == 2) {	// ステージクリア：タイトルに戻る
			nextScreenType = TITLE;
			fadeState = FADEOUT;
			buttonMap[STAGECLEAR][0][1] = 1;
		}
	}
	else if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		if (currentScreenType == INGAME) {
			nextScreenType = PAUSE;
			currentScreenType = nextScreenType;
		}
	}
	else {
		return;
	}
}
