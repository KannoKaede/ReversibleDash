#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "Stage.h"
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
ImageData keyWASD;
ImageData keySpace;
ImageData keyEscape;


Button titleButton(TITLE, 1, 1, VGet(50, 47, 0), 18, 6, Button::GAMESTART, "GAME START", LARGE, true);
Button openStageSelectButton(TITLE, 2, 1, VGet(50, 67, 0), 18, 6, Button::OPENSTAGESELECT, "STAGE SELECT", LARGE, true);
Button quitButton(TITLE, 3, 1, VGet(50, 87, 0), 18, 6, Button::GAMEQUIT, "GAME QUIT", LARGE, true);
Button stageSelect1(STAGESELECT, 1, 1, VGet(28, 41, 0), 9, 9, Button::SELECTSTAGE1, "STAGE.1", MEDIUM, false);
Button stageSelect2(STAGESELECT, 1, 2, VGet(50, 41, 0), 9, 9, Button::SELECTSTAGE2, "STAGE.2", MEDIUM, false);
Button stageSelect3(STAGESELECT, 1, 3, VGet(72, 41, 0), 9, 9, Button::SELECTSTAGE3, "STAGE.3", MEDIUM, false);
Button stageSelect4(STAGESELECT, 2, 1, VGet(28, 74, 0), 9, 9, Button::SELECTSTAGE4, "STAGE.4", MEDIUM, false);
Button stageSelect5(STAGESELECT, 2, 2, VGet(50, 74, 0), 9, 9, Button::SELECTSTAGE5, "STAGE.5", MEDIUM, false);
Button stageSelect6(STAGESELECT, 2, 3, VGet(72, 74, 0), 9, 9, Button::SELECTSTAGE6, "STAGE.6", MEDIUM, false);
Button returnTitle(STAGESELECT, 2, 4, VGet(90, 80, 0), 5, 5, Button::RETURNTITLE, "BACK", MEDIUM, true);
Button resumeGame(PAUSE, 1, 1, VGet(37, 63, 0), 10, 5, Button::RESUME, "RESUME", LARGE, true);
Button pauseGameExit(PAUSE, 1, 2, VGet(63, 63, 0), 10, 5, Button::GAMEEXIT, "EXIT", LARGE, true);
Button retryGame(GAMEOVER, 1, 1, VGet(37, 70, 0), 10, 5, Button::RETRY, "RETRY", LARGE, true);
Button gameOverGameExit(GAMEOVER, 1, 2, VGet(63, 70, 0), 10, 5, Button::GAMEEXIT, "EXIT", LARGE, true);
Button nextGame(CLEAR, 1, 1, VGet(37, 70, 0), 10, 5, Button::NEXTSTAGE, "NEXT", LARGE, true);
Button clearGameExit(CLEAR, 1, 2, VGet(63, 70, 0), 10, 5, Button::GAMEEXIT, "EXIT", LARGE, true);

void UISetUp() {
	keyWASD = { LoadGraph("Resource/Images/WASD.png") };
	GetGraphSize(keyWASD.image, &keyWASD.width, &keyWASD.height);
	keyEscape = { LoadGraph("Resource/Images/EscapeKey.png") };
	GetGraphSize(keyEscape.image, &keyEscape.width, &keyEscape.height);
	keySpace = { LoadGraph("Resource/Images/SpaceKey.png") };
	GetGraphSize(keySpace.image, &keySpace.width, &keySpace.height);
}

/// <summary> 画面の状態に対応したUIを表示するメソッド </summary>
void DrawUI(Player player)
{
	// 取得したサイズをコンソールに出力する
	if (base.IsDrawInGame()) {
		DrawFormatStringToHandle(base.ScreenDrawPosI(base.GetScreen().width, 1), base.ScreenDrawPosI(base.GetScreen().height, 95), COLOR_BLACK, base.GetFontData(MEDIUM).handle, "SCORE:%06d", highScore[base.GetStageNumber()]);
		DrawFormatStringToHandle(base.ScreenDrawPosI(base.GetScreen().width, 1), base.ScreenDrawPosI(base.GetScreen().height, 1), COLOR_BLACK, base.GetFontData(MEDIUM).handle, "STAGE.%d", base.GetStageNumber());
		DrawProgressRateBar(player, 50, 97, 96.5f);
		if (currentScreenType == INGAME) {
			DrawImage(21, 95, keyEscape);
			DrawTextString(23.5f, 0, 95.8f, "Pause", base.GetFontData(SMALL).handle);
			DrawImage(32, 95, keySpace);
			DrawTextString(37.5, 0, 95.8f, "Jump", base.GetFontData(SMALL).handle);
			DrawStartCountDown();
		}
		if (currentScreenType == PAUSE) {
			DrawBox(base.ScreenDrawPosI(base.GetScreen().width, 25), base.ScreenDrawPosI(base.GetScreen().height, 25),
				base.ScreenDrawPosI(base.GetScreen().width, 75), base.ScreenDrawPosI(base.GetScreen().height, 75), COLOR_WHITEGRAY, TRUE);
			DrawTextString(0, 100, 32, "PAUSE", base.GetFontData(EXTRALARGE).handle);
			DrawImage(20, 95, keyWASD);
			DrawTextString(23.5f, 0, 95.8f, "Move", base.GetFontData(SMALL).handle);
			DrawImage(32, 95, keySpace);
			DrawTextString(37.5f, 0, 95.8f, "Select", base.GetFontData(SMALL).handle);
		}
		if (currentScreenType == GAMEOVER) {
			DrawBox(base.ScreenDrawPosI(base.GetScreen().width, 23), base.ScreenDrawPosI(base.GetScreen().height, 18),
				base.ScreenDrawPosI(base.GetScreen().width, 77), base.ScreenDrawPosI(base.GetScreen().height, 82), COLOR_WHITEGRAY, TRUE);
			DrawTextString(0, 100, 25, "GAMEOVER", base.GetFontData(EXTRALARGE).handle);
			DrawTextString(27, 47, 43, "SCORE", base.GetFontData(LARGE).handle);
			DrawTextInt(27, 47, 51, "000000", base.GetFontData(LARGE).handle, score);
			DrawImage(20, 95, keyWASD);
			DrawTextString(23.5f, 0, 95.8f, "Move", base.GetFontData(SMALL).handle);
			DrawImage(32, 95, keySpace);
			DrawTextString(37.5f, 0, 95.8f, "Select", base.GetFontData(SMALL).handle);
		}
		if (currentScreenType == CLEAR) {
			DrawBox(base.ScreenDrawPosI(base.GetScreen().width, 23), base.ScreenDrawPosI(base.GetScreen().height, 18),
				base.ScreenDrawPosI(base.GetScreen().width, 77), base.ScreenDrawPosI(base.GetScreen().height, 82), COLOR_WHITEGRAY, TRUE);
			DrawTextString(0, 100, 25, "STAGE CLEAR", base.GetFontData(EXTRALARGE).handle);
			DrawTextString(27, 47, 43, "SCORE", base.GetFontData(LARGE).handle);
			DrawTextInt(27, 47, 51, "000000", base.GetFontData(LARGE).handle, score);
			DrawTextString(53, 73, 43, "HIGHSCORE", base.GetFontData(LARGE).handle);
			DrawTextInt(53, 73, 51, "000000", base.GetFontData(LARGE).handle, highScore[base.GetStageNumber()]);
			DrawImage(20, 95, keyWASD);
			DrawTextString(23.5f, 0, 95.8f, "Move", base.GetFontData(SMALL).handle);
			DrawImage(32, 95, keySpace);
			DrawTextString(37.5f, 0, 95.8f, "Select", base.GetFontData(SMALL).handle);
		}
	}
	else {
		if (currentScreenType == TITLE) {
			DrawTextString(0, 100, 16, "ReversibleDash", base.GetFontData(EXTRALARGE).handle);
			DrawTextString(83, 0, 95, "Ver 0.7.00.00", base.GetFontData(MEDIUM).handle);
			DrawImage(20, 95, keyWASD);
			DrawTextString(23.5f, 0, 95.8f, "Move", base.GetFontData(SMALL).handle);
			DrawImage(32, 95, keySpace);
			DrawTextString(37.5f, 0, 95.8f, "Select", base.GetFontData(SMALL).handle);
		}
		if (currentScreenType == STAGESELECT) {
			DrawTextString(0, 100, 16, "STAGESELECT", base.GetFontData(EXTRALARGE).handle);
			DrawImage(20, 95, keyWASD);
			DrawTextString(23.5f, 0, 95.8f, "Move", base.GetFontData(SMALL).handle);
			DrawImage(32, 95, keySpace);
			DrawTextString(37.5f, 0, 95.8f, "Select", base.GetFontData(SMALL).handle);
		}
	}
}

void SystemReset() {
	buttonManager.buttonMovePos = START_BUTTON_POS;
	buttonManager.buttonPos = START_BUTTON_POS;
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
		if (fadeStartCount == 0) {
			base.Initialization();
			fadeStartCount = GetNowCount();
		}
		if ((fadeStartCount + FADE_WAIT_TIME) <= GetNowCount()) {
			SystemReset();
			fadeState = FADEIN;
			if (currentScreenType == TITLE)base.SetStageNumber(0);
		}
		ScreenFade(0);
		return true;
	case NONE:
		return false;
	default:
		return false;
	}
}

/// <summary> フェード処理を行うメソッド </summary>
/// <param name="fadeSpeed">フェード速度</param>
void ScreenFade(int fadeSpeed)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	alphaValue = base.ClampNumI(alphaValue += fadeSpeed, 0, 255);
	DrawBox(0, 0, base.GetScreen().width, base.GetScreen().height, COLOR_BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void TextFade(std::string text, int font) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	DrawTextString(0, 100, 45, drawText, base.GetFontData(EXTRALARGE).handle);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

int startTime;
int fadeSpeed = 5;
int waitTime = 420;
constexpr int WAITTIME_START = 420;
#define WAITTIME_DRAW 500
#define WAITTIME_CHANGE 700
#define TEXTFADEINSPEED 15
#define TEXTFADEOUTSPEED1 -10
#define TEXTFADEOUTSPEED2 -5
/// <summary> スタートカウントダウンの描画を行うメソッド </summary>
void DrawStartCountDown() {
	if (isFading||!base.GetIsGameStop()) return;
	if (previousText != drawText) {
		previousText = drawText;
		startTime = 0;
	}
	if (startTime == 0) {
		startTime = GetNowCount();
	}
	TextFade(drawText, base.GetFontData(EXTRALARGE).handle);
	if (startTime + waitTime > GetNowCount()) {
		return;
	}
	alphaValue = base.ClampNumI(alphaValue + fadeSpeed, 0, 255);
	if (alphaValue == 0) {
		fadeSpeed = TEXTFADEINSPEED;
		if (drawText != START_COUNTDOWN_2) {	// α値が0になったタイミングでテキストの状態を確認
			drawText = START_COUNTDOWN_2;
			waitTime = WAITTIME_CHANGE;
		}
		else {	// 最後のテキストだった場合スタートカウントダウンを終了する
			base.SetIsGameStop(false);
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
	float x = base.ClampNumF(player.GetPosition().x / stageManager.GetGoalPosition(base.GetStageNumber()), 0, 1);
	float w = (endPos - startPos) * x;
	DrawBox(base.ScreenDrawPosI(base.GetScreen().width, startPos), base.ScreenDrawPosI(base.GetScreen().height, heightPos - 1),
		base.ScreenDrawPosI(base.GetScreen().width, endPos), base.ScreenDrawPosI(base.GetScreen().height, heightPos + 1), GetColor(200, 200, 200), TRUE);
	DrawCircleAA(base.ScreenDrawPosF(base.GetScreen().width, startPos), base.ScreenDrawPosF(base.GetScreen().height, heightPos),
		base.ScreenDrawPosF(base.GetScreen().width, 1), 64, GetColor(0, 200, 0), TRUE);	// 開始地点
	DrawCircleAA(base.ScreenDrawPosF(base.GetScreen().width, endPos), base.ScreenDrawPosF(base.GetScreen().height, heightPos),
		base.ScreenDrawPosF(base.GetScreen().width, 1), 64, GetColor(200, 200, 200), TRUE);	// 終了地点
	DrawBox(base.ScreenDrawPosI(base.GetScreen().width, startPos), base.ScreenDrawPosI(base.GetScreen().height, heightPos - 1),
		base.ScreenDrawPosI(base.GetScreen().width, startPos + w), base.ScreenDrawPosI(base.GetScreen().height, heightPos + 1), GetColor(0, 200, 0), TRUE);
	DrawCircleAA(base.ScreenDrawPosF(base.GetScreen().width, startPos + w), base.ScreenDrawPosF(base.GetScreen().height, heightPos),
		base.ScreenDrawPosF(base.GetScreen().width, 1), 64, GetColor(0, 200, 0), TRUE);	// プレイヤー座標
}


void DrawTextCenter(float left, float top, float right, float bottom, std::string text, int fontType) {

	int drawPosX = base.TextDrawCenterPosX(left, right, text, base.GetFontData(fontType).handle);	// 左右中央を計算
	int drawPosY = base.TextDrawCenterPosY(top, bottom, base.GetFontData(fontType).size, text);	// 上下中央を計算
	DrawStringToHandle(drawPosX, drawPosY, const_cast<char*>(text.c_str()), COLOR_BLACK, base.GetFontData(fontType).handle);
}

void DrawTextString(float leftPct, float rightPct, float heightPct, std::string text, int font) {
	float drawLeftPos = base.ScreenDrawPosF(base.GetScreen().width, leftPct);
	float drawRightPos = base.ScreenDrawPosF(base.GetScreen().width, rightPct);
	int drawPosX = drawLeftPos > drawRightPos ? (int)drawLeftPos : base.TextDrawCenterPosX(drawLeftPos, drawRightPos, text, font);
	int drawPosY = base.ScreenDrawPosI(base.GetScreen().height, heightPct);
	DrawStringToHandle(drawPosX, drawPosY, const_cast<char*>(text.c_str()), COLOR_BLACK, font);
}

void DrawTextInt(float leftPct, float rightPct, float heightPct, std::string text, int font, int num) {
	float drawLeftPos = base.ScreenDrawPosF(base.GetScreen().width, leftPct);
	float drawRightPos = base.ScreenDrawPosF(base.GetScreen().width, rightPct);
	int drawPosX = drawLeftPos > drawRightPos ? (int)drawLeftPos : base.TextDrawCenterPosX(drawLeftPos, drawRightPos, text, font);
	int drawPosY = base.ScreenDrawPosI(base.GetScreen().height, heightPct);
	DrawFormatStringToHandle(drawPosX, drawPosY, COLOR_BLACK, font, "%06d", num);
}

void DrawImage(float leftPct, float topPct, ImageData image) {
	// 実装環境の画面サイズとプレイ時の画面サイズでどれくらい差があるのか
	float test = (float)base.GetScreen().width / 2560;
	// 左上頂点座標を計算
	int x1 = base.ScreenDrawPosI(base.GetScreen().width, leftPct);
	int y1 = base.ScreenDrawPosI(base.GetScreen().height, topPct);
	// 右下頂点座標を計算
	int x2 = x1 + (int)((float)image.width * test);
	int y2 = y1 + (int)((float)image.height * test);

	DrawExtendGraph(x1, y1, x2, y2, image.image, TRUE);
}

void ChangeUIState(SCREEN_TYPE screen, FADE_STATE fade) {
	nextScreenType = screen;
	fadeState = fade;
	base.SetIsGameStop(true);
}

