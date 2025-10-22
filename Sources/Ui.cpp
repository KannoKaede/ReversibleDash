#include "DxLib.h"
#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "InGame.h"
#include "Button.h"
#include "Input.h"


SCREEN_TYPE currentScreenType;
SCREEN_TYPE nextScreenType;
bool isFading = true;
int alphaValue = 255;
int fadeStartCount;
FADE_STATE fadeState;

std::string previousText;
std::string drawText = "";
int keyRight, keyLeft, keyUp, keyDown, keyEscape, keySpace;

Button titleButton(TITLE, 1, 1, VGet(50, 47, 0), 18, 6, Button::GAMESTART, "GAME START", FONT_LARGE, true);
Button openStageSelectButton(TITLE, 2, 1, VGet(50, 67, 0), 18, 6, Button::OPENSTAGESELECT, "STAGE SELECT", FONT_LARGE, true);
Button quitButton(TITLE, 3, 1, VGet(50, 87, 0), 18, 6, Button::GAMEQUIT, "GAME QUIT", FONT_LARGE, true);
Button stageSelect1(STAGESELECT, 1, 1, VGet(28, 41, 0), 9, 9, Button::SELECTSTAGE1, "STAGE.1", FONT_MEDIUM, false);
Button stageSelect2(STAGESELECT, 1, 2, VGet(50, 41, 0), 9, 9, Button::SELECTSTAGE2, "STAGE.2", FONT_MEDIUM, false);
Button stageSelect3(STAGESELECT, 1, 3, VGet(72, 41, 0), 9, 9, Button::SELECTSTAGE3, "STAGE.3", FONT_MEDIUM, false);
Button stageSelect4(STAGESELECT, 2, 1, VGet(28, 74, 0), 9, 9, Button::SELECTSTAGE4, "STAGE.4", FONT_MEDIUM, false);
Button stageSelect5(STAGESELECT, 2, 2, VGet(50, 74, 0), 9, 9, Button::SELECTSTAGE5, "STAGE.5", FONT_MEDIUM, false);
Button stageSelect6(STAGESELECT, 2, 3, VGet(72, 74, 0), 9, 9, Button::SELECTSTAGE6, "STAGE.6", FONT_MEDIUM, false);
Button returnTitle(STAGESELECT, 2, 4, VGet(90, 80, 0), 5, 5, Button::RETURNTITLE, "BACK", FONT_MEDIUM, true);
Button resumeGame(PAUSE, 1, 1, VGet(37, 63, 0), 10, 5, Button::RESUME, "RESUME", FONT_LARGE, true);
Button pauseGameExit(PAUSE, 1, 2, VGet(63, 63, 0), 10, 5, Button::GAMEEXIT, "EXIT", FONT_LARGE, true);
Button retryGame(GAMEOVER, 1, 1, VGet(37, 70, 0), 10, 5, Button::RETRY, "RETRY", FONT_LARGE, true);
Button gameOverGameExit(GAMEOVER, 1, 2, VGet(63, 70, 0), 10, 5, Button::GAMEEXIT, "EXIT", FONT_LARGE, true);
Button nextGame(STAGECLEAR, 1, 1, VGet(37, 70, 0), 10, 5, Button::NEXTSTAGE, "NEXT", FONT_LARGE, true);
Button clearGameExit(STAGECLEAR, 1, 2, VGet(63, 70, 0), 10, 5, Button::GAMEEXIT, "EXIT", FONT_LARGE, true);

void UISetUp() {
	keyRight = LoadGraph("Resource/Images/RightKey.png");
	keyLeft = LoadGraph("Resource/Images/LeftKey.png");
	keyUp = LoadGraph("Resource/Images/UpKey.png");
	keyDown = LoadGraph("Resource/Images/DownKey.png");
	keyEscape = LoadGraph("Resource/Images/EscapeKey.png");
	keySpace = LoadGraph("Resource/Images/SpaceKey.png");
}

/// <summary> 画面の状態に対応したUIを表示するメソッド </summary>
void DrawUI(Player player)
{
	switch (currentScreenType)
	{
	case TITLE:
		titleButton.Draw();
		openStageSelectButton.Draw();
		quitButton.Draw();
		DrawTextString(0, 100, 16, "ReversibleDash", fontData[FONT_EXTRALARGE].fontHandle);
		DrawTextString(83, 0, 95, "Ver 0.7.00.00", fontData[FONT_MEDIUM].fontHandle);
		DrawImage(19, 97, keyLeft, true);
		DrawImage(21, 97, keyRight, true);
		DrawImage(20, 95.1f, keyUp, true);
		DrawImage(20, 97, keyDown, true);
		DrawTextString(22.5f, 0, 95.8f, "ButtonMove", fontData[FONT_SMALL].fontHandle);
		DrawImage(37, 95, keySpace, false);
		DrawTextString(42.5f, 0, 95.8f, "ButtonSelect", fontData[FONT_SMALL].fontHandle);
		break;
	case STAGESELECT:
		stageSelect1.Draw();
		stageSelect2.Draw();
		stageSelect3.Draw();
		stageSelect4.Draw();
		stageSelect5.Draw();
		stageSelect6.Draw();
		returnTitle.Draw();
		DrawTextString(0, 100, 16, "STAGESELECT", fontData[FONT_EXTRALARGE].fontHandle);
		DrawImage(19, 97, keyLeft, true);
		DrawImage(21, 97, keyRight, true);
		DrawImage(20, 95.1f, keyUp, true);
		DrawImage(20, 97, keyDown, true);
		DrawTextString(22.5f, 0, 95.8f, "ButtonMove", fontData[FONT_SMALL].fontHandle);
		DrawImage(37, 95, keySpace, false);
		DrawTextString(42.5f, 0, 95.8f, "ButtonSelect", fontData[FONT_SMALL].fontHandle);
		break;
	case PAUSE:
	case GAMEOVER:
	case STAGECLEAR:
	case INGAME:
		// インゲームのUIを用意したらここに配置
		DrawBox(0, ScreenDrawPosI(screenHeight, 94.4f), screenWidth, screenHeight, GetColor(128, 128, 128), TRUE);	// テスト インゲームのUIボックスの大きさ
		DrawFormatStringToHandle(ScreenDrawPosI(screenWidth, 1), ScreenDrawPosI(screenHeight, 95), COLOR_BLACK, fontData[FONT_MEDIUM].fontHandle, "SCORE:%06d", inGameVewScore);
		DrawFormatStringToHandle(ScreenDrawPosI(screenWidth, 1), ScreenDrawPosI(screenHeight, 1), COLOR_BLACK, fontData[FONT_MEDIUM].fontHandle, "STAGE.%d", stageNumber);
		DrawProgressRateBar(player, 50, 97, 96.5f);
		if (currentScreenType == INGAME) {
			DrawImage(20, 95, keyEscape, false);
			DrawTextString(22.5f, 0, 95.8f, "Pause", fontData[FONT_SMALL].fontHandle);
			DrawImage(37, 95, keySpace, false);
			DrawTextString(42.5f, 0, 95.8f, "Jump", fontData[FONT_SMALL].fontHandle);
		}
		if (currentScreenType == PAUSE) {
			DrawBox(ScreenDrawPosI(screenWidth, 25), ScreenDrawPosI(screenHeight, 25), ScreenDrawPosI(screenWidth, 75), ScreenDrawPosI(screenHeight, 75), COLOR_WHITEGRAY, TRUE);
			resumeGame.Draw();
			pauseGameExit.Draw();
			DrawTextString(0, 100, 32, "PAUSE", fontData[FONT_EXTRALARGE].fontHandle);
			DrawImage(19, 97, keyLeft, true);
			DrawImage(21, 97, keyRight, true);
			DrawImage(20, 95.1f, keyUp, true);
			DrawImage(20, 97, keyDown, true);
			DrawTextString(22.5f, 0, 95.8f, "ButtonMove", fontData[FONT_SMALL].fontHandle);
			DrawImage(37, 95, keySpace, false);
			DrawTextString(42.5f, 0, 95.8f, "ButtonSelect", fontData[FONT_SMALL].fontHandle);
		}
		if (currentScreenType == GAMEOVER) {
			DrawBox(ScreenDrawPosI(screenWidth, 23), ScreenDrawPosI(screenHeight, 18), ScreenDrawPosI(screenWidth, 77), ScreenDrawPosI(screenHeight, 82), COLOR_WHITEGRAY, TRUE);
			gameOverGameExit.Draw();
			retryGame.Draw();
			DrawTextString(0, 100, 25, "GAMEOVER", fontData[FONT_EXTRALARGE].fontHandle);
			DrawTextString(27, 47, 43, "SCORE", fontData[FONT_LARGE].fontHandle);
			DrawTextInt(27, 47, 51, "000000", fontData[FONT_LARGE].fontHandle, score);
			DrawImage(19, 97, keyLeft, true);
			DrawImage(21, 97, keyRight, true);
			DrawImage(20, 95.1f, keyUp, true);
			DrawImage(20, 97, keyDown, true);
			DrawTextString(22.5f, 0, 95.8f, "ButtonMove", fontData[FONT_SMALL].fontHandle);
			DrawImage(37, 95, keySpace, false);
			DrawTextString(42.5f, 0, 95.8f, "ButtonSelect", fontData[FONT_SMALL].fontHandle);
		}
		if (currentScreenType == STAGECLEAR) {
			DrawBox(ScreenDrawPosI(screenWidth, 23), ScreenDrawPosI(screenHeight, 18), ScreenDrawPosI(screenWidth, 77), ScreenDrawPosI(screenHeight, 82), COLOR_WHITEGRAY, TRUE);
			nextGame.Draw();
			clearGameExit.Draw();
			DrawTextString(0, 100, 25, "STAGE CLEAR", fontData[FONT_EXTRALARGE].fontHandle);
			DrawTextString(27, 47, 43, "SCORE", fontData[FONT_LARGE].fontHandle);
			DrawTextInt(27, 47, 51, "000000", fontData[FONT_LARGE].fontHandle, score);
			DrawTextString(53, 73, 43, "HIGHSCORE", fontData[FONT_LARGE].fontHandle);
			DrawTextInt(53, 73, 51, "000000", fontData[FONT_LARGE].fontHandle, highScore[stageNumber]);
			DrawImage(19, 97, keyLeft, true);
			DrawImage(21, 97, keyRight, true);
			DrawImage(20, 95.1f, keyUp, true);
			DrawImage(20, 97, keyDown, true);
			DrawTextString(22.5f, 0, 95.8f, "ButtonMove", fontData[FONT_SMALL].fontHandle);
			DrawImage(37, 95, keySpace, false);
			DrawTextString(42.5f, 0, 95.8f, "ButtonSelect", fontData[FONT_SMALL].fontHandle);
		}
		break;
	default:
		printfDx("ERROR : 予期しない値です(currentScreenType)");
		break;
	}
}

void SystemReset() {
	buttonMovePos = STARTBUTTON_POS;
	buttonPos = STARTBUTTON_POS;
	currentScreenType = nextScreenType;
	if (fadeStartCount != 0)fadeStartCount = 0;
}
/// <summary> フェード演出の制御を行うメソッド：フェード演出中はFlagを立てて他の処理を制御 </summary>
bool ScreenFadeControl() {
	switch (fadeState)
	{
	case FADEOUT:		// 画面を暗転：処理開始時にフラグを立てる
		if (alphaValue == 255) fadeState = FADEWAIT;
		ScreenFade(FADE_SPEED);
		return true;
	case FADEIN:	// 画面を明転：処理終了時にフラグを折る
		if (alphaValue == 0) fadeState = NONE;
		ScreenFade(-FADE_SPEED);
		return true;
	case SCREENSETUP:	// 画面の切り替え：変数の中身を変えるだけ
		SystemReset();
		fadeState = NONE;
		return false;
	case FADEWAIT:		// 指定時間待機：待機中にUIの切り替えを行う
		if (fadeStartCount == 0) fadeStartCount = GetNowCount();
		if ((fadeStartCount + FADE_WAIT_TIME) <= GetNowCount()) {
			SystemReset();
			fadeState = FADEIN;
			if (currentScreenType == TITLE) stageNumber = 0;
		}
		ScreenFade(0);
		return true;
	case NONE:
		return false;
	default:
		printfDx("ERROR : 予期しない値です(fadeState)");
		return false;
	}
}

/// <summary> フェード処理を行うメソッド </summary>
/// <param name="fadeSpeed">フェード速度</param>
void ScreenFade(int fadeSpeed)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	alphaValue = ClampNum(alphaValue += fadeSpeed, 0, 255);
	DrawBox(0, 0, screenWidth, screenHeight, COLOR_BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void TextFade(std::string text, int font) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	DrawTextString(0, 100, 45, drawText, fontData[FONT_EXTRALARGE].fontHandle);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int startTime;
int fadeSpeed = 5;
int waitTime = 420;
#define WAITTIME_START 420
#define WAITTIME_DRAW 500
#define WAITTIME_CHANGE 700
#define TEXTFADEINSPEED 15
#define TEXTFADEOUTSPEED1 -10
#define TEXTFADEOUTSPEED2 -5
/// <summary> スタートカウントダウンの描画を行うメソッド </summary>
void DrawStartCountDown() {

	if (previousText != drawText) {
		previousText = drawText;
		startTime = 0;
	}
	if (startTime == 0) {
		startTime = GetNowCount();
	}
	TextFade(drawText, fontData[FONT_EXTRALARGE].fontHandle);
	if (startTime + waitTime > GetNowCount()) {
		return;
	}
	alphaValue = ClampNum(alphaValue + fadeSpeed, 0, 255);
	if (alphaValue == 0) {
		fadeSpeed = TEXTFADEINSPEED;
		if (drawText != START_COUNTDOWN_2) {	// α値が0になったタイミングでテキストの状態を確認
			drawText = START_COUNTDOWN_2;
			waitTime = WAITTIME_CHANGE;
		}
		else {	// 最後のテキストだった場合スタートカウントダウンを終了する
			isGameStop = false;
			waitTime = WAITTIME_START;
		}
	}
	if (alphaValue == 255) {	// 文字がくっきり見えるようになったら一定時間待機した後フェードアウト速度を描画している文字に応じて変更
		startTime = 0;
		waitTime = WAITTIME_DRAW;
		if (drawText == START_COUNTDOWN_1) {
			fadeSpeed = TEXTFADEOUTSPEED1;
		}
		else {
			fadeSpeed = TEXTFADEOUTSPEED2;
		}
	}
}
void DrawProgressRateBar(const Player& player, float startPos, float endPos, float heightPos) {
	float x = ClampNum(player.GetPosition().x / goalPosition[stageNumber], 0, 1);
	float w = (endPos - startPos) * x;
	DrawBox(ScreenDrawPosI(screenWidth, startPos), ScreenDrawPosI(screenHeight, heightPos - 1), ScreenDrawPosI(screenWidth, endPos), ScreenDrawPosI(screenHeight, heightPos + 1), GetColor(200, 200, 200), TRUE);
	DrawCircleAA(ScreenDrawPosF(screenWidth, startPos), ScreenDrawPosF(screenHeight, heightPos), ScreenDrawPosF(screenWidth, 1), 64, GetColor(0, 200, 0), TRUE);	// 開始地点
	DrawCircleAA(ScreenDrawPosF(screenWidth, endPos), ScreenDrawPosF(screenHeight, heightPos), ScreenDrawPosF(screenWidth, 1), 64, GetColor(200, 200, 200), TRUE);	// 終了地点
	DrawBox(ScreenDrawPosI(screenWidth, startPos), ScreenDrawPosI(screenHeight, heightPos - 1), ScreenDrawPosI(screenWidth, startPos + w), ScreenDrawPosI(screenHeight, heightPos + 1), GetColor(0, 200, 0), TRUE);
	DrawCircleAA(ScreenDrawPosF(screenWidth, startPos + w), ScreenDrawPosF(screenHeight, heightPos), ScreenDrawPosF(screenWidth, 1), 64, GetColor(0, 200, 0), TRUE);	// プレイヤー座標
}


void DrawTextCenter(float left, float top, float right, float bottom, std::string text, int fontType) {
	int font = fontData[fontType].fontHandle;;
	int	fontSize = fontData[fontType].fontSize;;

	int drawPosX = TextDrawCenterPosX(left, right, text, font);	// 左右中央を計算
	int drawPosY = TextDrawCenterPosY(top, bottom, fontSize, text, font);	// 上下中央を計算
	DrawStringToHandle(drawPosX, drawPosY, const_cast<char*>(text.c_str()), COLOR_BLACK, font);
}

void DrawTextString(float leftPct, float rightPct, float heightPct, std::string text, int font) {
	float drawLeftPos = ScreenDrawPosF(screenWidth, leftPct);
	float drawRightPos = ScreenDrawPosF(screenWidth, rightPct);
	int drawPosX = drawLeftPos > drawRightPos ? (int)drawLeftPos : TextDrawCenterPosX(drawLeftPos, drawRightPos, text, font);
	int drawPosY = ScreenDrawPosI(screenHeight, heightPct);
	DrawStringToHandle(drawPosX, drawPosY, const_cast<char*>(text.c_str()), COLOR_BLACK, font);
}

void DrawTextInt(float leftPct, float rightPct, float heightPct, std::string text, int font, int num) {
	float drawLeftPos = ScreenDrawPosF(screenWidth, leftPct);
	float drawRightPos = ScreenDrawPosF(screenWidth, rightPct);
	int drawPosX = drawLeftPos > drawRightPos ? (int)drawLeftPos : TextDrawCenterPosX(drawLeftPos, drawRightPos, text, font);
	int drawPosY = ScreenDrawPosI(screenHeight, heightPct);
	DrawFormatStringToHandle(drawPosX, drawPosY, COLOR_BLACK, font, "%06d", num);
}

void DrawImage(float leftPct, float topPct, int image, bool isHalf) {
	int x = ScreenDrawPosI(screenWidth, leftPct);
	int y = ScreenDrawPosI(screenHeight, topPct);
	if (isHalf) {
		int lenth = isHalf ? KEYIMAGE_LENGTH / 2 : KEYIMAGE_LENGTH;
		DrawExtendGraph(x, y, x + lenth, y + lenth, image, TRUE);
	}
	else {
		DrawGraph(x, y, image, TRUE);
	}
}