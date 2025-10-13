#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
#include "Button.h"
#include "Input.h"

#define FONT_TYPE_1 1
#define FONT_TYPE_2 2
#define FONT_TYPE_3 3
// 全体的にリファクタリングする
SCREEN_TYPE currentScreenType;
SCREEN_TYPE nextScreenType;
bool isFading = true;
int alphaValue = 255;
int fadeStartCount;
FADE_STATE fadeState;
int buttonPosX = 0;
int buttonPosY = 0;
int backScreen = GetColor(230, 230, 230);
int gray = GetColor(200, 200, 200);
int green = GetColor(0, 255, 128);

int black = GetColor(0, 0, 0);
std::string previousText;
std::string drawText = START_COUNTDOWN_1;





/// <summary> ボタン用の図形を描画 </summary>
/// <param name="loopY">何回ループするかfor外側</param>
/// <param name="loopX">何回ループするかfor内側</param>
/// <param name="topLeft">描画する図形の左上の座標</param>
/// <param name="lengthX">図形の横幅</param>
/// <param name="lengthY">図形の縦幅</param>
/// <param name="plusX">二個目の図形の位置を横にずらす値</param>
/// <param name="plusY">二個目の図形の位置を縦にずらす値</param>
/// <param name="screen">画面の種類</param>
/// <param name="isSquare">四角形か三角形を描画するかのフラグ:true=四角形</param>
void SquareTest(int loopY, int loopX, VECTOR topLeft, int lengthX, int lengthY, int plusX, int plusY, SCREEN_TYPE screen, bool isSquare) {
	int posX = (int)topLeft.x;
	int posY = (int)topLeft.y - plusY;
	for (int y = 0; y < loopY; y++) {	// 描画する座標を変更しながら図形を描画(形が等しく位置も等間隔にしか置けない）
		posX = (int)topLeft.x;
		posY += plusY;
		for (int x = 0; x < loopX; x++) {
			if (isSquare) {
				DrawBox((int)ScreenDrawPos(screenWidth, posX), (int)ScreenDrawPos(screenHeight, posY), (int)ScreenDrawPos(screenWidth, posX + lengthX), (int)ScreenDrawPos(screenHeight, posY + lengthY), buttonMap[screen][y][x] == 2 ? green : gray, TRUE);
			}
			else {
				DrawTriangleAA(ScreenDrawPos(screenWidth, posX), ScreenDrawPos(screenHeight, posY), ScreenDrawPos(screenWidth, posX + lengthX), ScreenDrawPos(screenHeight, posY), ScreenDrawPos(screenWidth, posX + lengthX), ScreenDrawPos(screenHeight, posY + lengthY), buttonMap[screen][y][x] == 2 ? green : gray, TRUE);
			}
			posX += plusX;
		}
	}
}

/// <summary> 指定の枠の中央に文字を描画する </summary>
/// <param name="drawText"> 描画する文字列 </param>
/// <param name="boxLeftPos"> 指定の枠の左座標 </param>
/// <param name="boxRightPos"> 指定の枠の右座標 </param>
/// <param name="drawPosY"> 描画する際の縦座標 </param>
/// <param name="font"> 使用するフォント </param>
/// <param name="isNum"> 数字を使用するか：true = 数字を使用 </param>
/// <param name="num"> 使用する数字 </param>
void StringTest(std::string drawText, int boxLeftPos, int boxRightPos, int drawPosY, int font, bool isNum, int num) {
	// 指定の範囲から文字が中央に表示される座標を計算する
	int drawPosX = ((boxRightPos - boxLeftPos) - GetDrawFormatStringWidthToHandle(font, const_cast<char*>(drawText.c_str()))) / 2 + boxLeftPos;
	if (isNum) {
		DrawFormatStringToHandle(drawPosX, (int)ScreenDrawPos(screenHeight, drawPosY), black, font, "%06d", num);
	}
	else {
		DrawFormatStringToHandle(drawPosX, (int)ScreenDrawPos(screenHeight, drawPosY), black, font, "%s", const_cast<char*>(drawText.c_str()));
	}
}

Button titleButton(TITLE, 0, 0, VGet(50, 47, 0), 18, 6, Button::GAMESTART, "GAME START", FONT_TYPE_2);
Button openStageSelectButton(TITLE, 1, 0, VGet(50, 67, 0), 18, 6, Button::OPENSTAGESELECT, "STAGE SELECT", FONT_TYPE_2);
Button quitButton(TITLE, 2, 0, VGet(50, 87, 0), 18, 6, Button::GAMEQUIT, "GAME QUIT", FONT_TYPE_2);
Button stageSelect1(STAGESELECT, 0, 0, VGet(28, 41, 0), 9, 9, Button::SELECTSTAGE1, "STAGE.1", FONT_TYPE_3);
Button stageSelect2(STAGESELECT, 0, 1, VGet(50, 41, 0), 9, 9, Button::SELECTSTAGE2, "STAGE.2", FONT_TYPE_3);
Button stageSelect3(STAGESELECT, 0, 2, VGet(72, 41, 0), 9, 9, Button::SELECTSTAGE3, "STAGE.3", FONT_TYPE_3);
Button stageSelect4(STAGESELECT, 1, 0, VGet(28, 74, 0), 9, 9, Button::SELECTSTAGE4, "STAGE.4", FONT_TYPE_3);
Button stageSelect5(STAGESELECT, 1, 1, VGet(50, 74, 0), 9, 9, Button::SELECTSTAGE5, "STAGE.5", FONT_TYPE_3);
Button stageSelect6(STAGESELECT, 1, 2, VGet(72, 74, 0), 9, 9, Button::SELECTSTAGE6, "STAGE.6", FONT_TYPE_3);
Button returnTitle(STAGESELECT, 1, 3, VGet(88, 76, 0), 5, 5, Button::RETURNTITLE, "BACK", FONT_TYPE_3);
Button resumeGame(PAUSE, 0, 0, VGet(37, 63, 0), 10, 5, Button::RESUME, "RESUME", FONT_TYPE_2);
Button pauseGameExit(PAUSE, 0, 1, VGet(63, 63, 0), 10, 5, Button::GAMEEXIT, "EXIT", FONT_TYPE_2);
Button retryGame(GAMEOVER, 0, 0, VGet(37, 70, 0), 10, 5, Button::RETRY, "RETRY", FONT_TYPE_2);
Button gameOverGameExit(GAMEOVER, 0, 1, VGet(63, 70, 0), 10, 5, Button::GAMEEXIT, "EXIT", FONT_TYPE_2);
Button nextGame(STAGECLEAR, 0, 0, VGet(37, 70, 0), 10, 5, Button::NEXTSTAGE, "NEXT", FONT_TYPE_2);
Button clearGameExit(STAGECLEAR, 0, 1, VGet(63, 70, 0), 10, 5, Button::GAMEEXIT, "EXIT", FONT_TYPE_2);

/// <summary> 画面の状態に対応したUIを表示するメソッド </summary>
void ScreenUISwitching()
{
	switch (currentScreenType)
	{
	case TITLE:

		titleButton.Draw();
		openStageSelectButton.Draw();
		quitButton.Draw();
		StringTest("ReversibleDash", 0, screenWidth, 16, bigFontHandle, false, 0);
		DrawStringToHandle((int)ScreenDrawPos(screenWidth, 80), (int)ScreenDrawPos(screenWidth, 95), "Ver_0.0.00.00", black, smallFontHandle);
		break;
	case STAGESELECT:
		stageSelect1.Draw();
		stageSelect2.Draw();
		stageSelect3.Draw();
		stageSelect4.Draw();
		stageSelect5.Draw();
		stageSelect6.Draw();
		returnTitle.Draw();
		SquareTest(2, 3, VGet(28, 50, 0), 9, 3, 22, 33, STAGESELECT, true);
		SquareTest(2, 3, VGet(26, 49, 0), 2, 4, 22, 33, STAGESELECT, false);
		StringTest("STAGESELECT", 0, screenWidth, 16, bigFontHandle, false, 0);
		// この座標の位置に実際のテキストを置きたい
		//StringTest("STAGE1", (int)ScreenDrawPos(screenWidth, 28), (int)ScreenDrawPos(screenWidth, 37), 50, smallFontHandle, false, 0);
		//StringTest("STAGE2", (int)ScreenDrawPos(screenWidth, 50), (int)ScreenDrawPos(screenWidth, 59), 50, smallFontHandle, false, 0);
		//StringTest("STAGE3", (int)ScreenDrawPos(screenWidth, 72), (int)ScreenDrawPos(screenWidth, 81), 50, smallFontHandle, false, 0);
		//StringTest("STAGE4", (int)ScreenDrawPos(screenWidth, 28), (int)ScreenDrawPos(screenWidth, 37), 83, smallFontHandle, false, 0);
		//StringTest("STAGE5", (int)ScreenDrawPos(screenWidth, 50), (int)ScreenDrawPos(screenWidth, 59), 83, smallFontHandle, false, 0);
		//StringTest("STAGE6", (int)ScreenDrawPos(screenWidth, 72), (int)ScreenDrawPos(screenWidth, 81), 83, smallFontHandle, false, 0);
		break;
	case PAUSE:
	case GAMEOVER:
	case STAGECLEAR:
	case INGAME:
		// インゲームのUIを用意したらここに配置
		DrawFormatStringToHandle((int)ScreenDrawPos(screenWidth, 1), (int)ScreenDrawPos(screenHeight, 95), black, smallFontHandle, "SCORE:%06d", inGameVewScore);
		if (currentScreenType == PAUSE) {
			DrawBox((int)ScreenDrawPos(screenWidth, 25), (int)ScreenDrawPos(screenHeight, 25), (int)ScreenDrawPos(screenWidth, 75), (int)ScreenDrawPos(screenHeight, 75), backScreen, TRUE);
			resumeGame.Draw();
			pauseGameExit.Draw();
			StringTest("PAUSE", 0, screenWidth, 32, bigFontHandle, false, 0);
		}
		if (currentScreenType == GAMEOVER) {
			DrawBox((int)ScreenDrawPos(screenWidth, 23), (int)ScreenDrawPos(screenHeight, 18), (int)ScreenDrawPos(screenWidth, 77), (int)ScreenDrawPos(screenHeight, 82), backScreen, TRUE);
			gameOverGameExit.Draw();
			retryGame.Draw();
			StringTest("GAMEOVER", 0, screenWidth, 25, bigFontHandle, false, 0);
			StringTest("SCORE", (int)ScreenDrawPos(screenWidth, 27), (int)ScreenDrawPos(screenWidth, 47), 43, normalFontHandle, false, 0);
			StringTest("000000", (int)ScreenDrawPos(screenWidth, 27), (int)ScreenDrawPos(screenWidth, 47), 51, normalFontHandle, true, score);
		}
		if(currentScreenType == STAGECLEAR){
			DrawBox((int)ScreenDrawPos(screenWidth, 23), (int)ScreenDrawPos(screenHeight, 18), (int)ScreenDrawPos(screenWidth, 77), (int)ScreenDrawPos(screenHeight, 82), backScreen, TRUE);
			nextGame.Draw();
			clearGameExit.Draw();
			StringTest("STAGE CLEAR", 0, screenWidth, 25, bigFontHandle, false, 0);
			StringTest("SCORE", (int)ScreenDrawPos(screenWidth, 27), (int)ScreenDrawPos(screenWidth, 47), 43, normalFontHandle, false, 0);
			StringTest("000000", (int)ScreenDrawPos(screenWidth, 27), (int)ScreenDrawPos(screenWidth, 47), 51, normalFontHandle, true, score);
			StringTest("HIGHSCORE", (int)ScreenDrawPos(screenWidth, 53), (int)ScreenDrawPos(screenWidth, 73), 43, normalFontHandle, false, 0);
			StringTest("000000", (int)ScreenDrawPos(screenWidth, 53), (int)ScreenDrawPos(screenWidth, 73), 51, normalFontHandle, true, highScore[stageNumber]);
		}
		break;
	default:
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
	case SCREENSETUP:	// 画面の切り替え：変数の中身を変えるだけ
		buttonMovePos = VGet(0, 0, 0);
		buttonPos = VGet(0, 0, 0);
		currentScreenType = nextScreenType;
		fadeState = NONE;
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
			buttonMovePos = VGet(0, 0, 0);
			buttonPos = VGet(0, 0, 0);
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
	DrawBox(0, 0, screenWidth, screenHeight, black, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int count;
int fadeSpeed = 3;
/// <summary> スタートカウントダウンの描画を行うメソッド </summary>
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
		if (drawText != START_COUNTDOWN_2) {	// α値が0になったタイミングでテキストの状態を確認
			drawText = START_COUNTDOWN_2;
		}
		else {	// 最後のテキストだった場合スタートカウントダウンを終了する
			isGameStop = false;
		}
	}
	if (alphaValue >= 255) {	// 文字がくっきり見えるようになったら一定時間待機した後フェードアウト速度を描画している文字に応じて変更
		alphaValue = 255;
		WaitTimer(300);
		fadeSpeed = drawText == START_COUNTDOWN_2 ? -FADE_SPEED * 2.5 : -FADE_SPEED / 1.5;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	StringTest(const_cast<char*>(drawText.c_str()), 0, screenWidth, 45, bigFontHandle, false, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void DrawProgressRateBar(const Player& player, float startPos, float endPos, float heightPos) {	// 画面の下をUI表示ゾーンにするためリファクタリングする(動きもかくかくなので何とかする
	float x =ClampNum(player.GetPosition().x / goalPosition[stageNumber], 0, 1);
	float w = (endPos - startPos) * x;
	DrawBox((int)ScreenDrawPos(screenWidth, startPos), (int)ScreenDrawPos(screenHeight, heightPos - 1), (int)ScreenDrawPos(screenWidth, endPos), (int)ScreenDrawPos(screenHeight, heightPos + 1), GetColor(200, 200, 200), TRUE);
	DrawCircleAA(ScreenDrawPos(screenWidth, startPos), ScreenDrawPos(screenHeight, heightPos), ScreenDrawPos(screenWidth, 1), 64, GetColor(0, 200, 0), TRUE);	// 開始地点
	DrawCircleAA(ScreenDrawPos(screenWidth, endPos), ScreenDrawPos(screenHeight, heightPos), ScreenDrawPos(screenWidth, 1), 64, GetColor(200, 200, 200), TRUE);	// 終了地点
	DrawBox(ScreenDrawPos(screenWidth, startPos), ScreenDrawPos(screenHeight, heightPos - 1), ScreenDrawPos(screenWidth, startPos+ w), ScreenDrawPos(screenHeight, heightPos + 1), GetColor(0, 200, 0), TRUE);
	DrawCircleAA(ScreenDrawPos(screenWidth, startPos + w), ScreenDrawPos(screenHeight, heightPos), ScreenDrawPos(screenWidth, 1), 64, GetColor(0, 200, 0), TRUE);	// プレイヤー座標
}


void DrawTextCenter(float left, float top, float right, float bottom, std::string text, int fontType) {
	int font = {}, fontSize = {};
	switch (fontType)	// フォントなどの値を変える　リファクタリングしてくれ
	{
	case 1:
		font = bigFontHandle;
		fontSize = bigFontSize;
		break;
	case 2:
		font = normalFontHandle;
		fontSize = normalFontSize;
		break;
	case 3:
		font = smallFontHandle;
		fontSize = smallFontSize;
		break;
	}
	float drawPosX = ((right - left) - GetDrawFormatStringWidthToHandle(font, const_cast<char*>(text.c_str()))) / 2 + left;	// 左右中央を計算
	float drawPosY = (((bottom - top) - fontSize )/ 2 + top);	// 上下中央を計算
	DrawStringToHandle(drawPosX, drawPosY, const_cast<char*>(text.c_str()), black, font);
}