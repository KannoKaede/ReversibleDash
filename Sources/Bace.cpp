#include "Main.h"
#include "UI.h"

ScreenSize screen;	// 画面サイズ
FontData fontData[4];	// フォントデータとサイズ
bool isGameStop;		// ゲームの進行が止まっているか判定するフラグ
int stageNumber;		// 遊んでいるステージ番号

void SetScreenSize() {
	screen.width = GetSystemMetrics(SM_CXSCREEN);
	screen.height = GetSystemMetrics(SM_CYSCREEN);
	ChangeWindowMode(TRUE);
	SetGraphMode(screen.width, screen.height, 32);
}

float ClampNumF(float num, float min, float max) {
	if (num < min) return min;
	else if (num > max) return max;
	else return num;
}

int ClampNumI(int num, int min, int max) {
	if (num < min) return min;
	else if (num > max) return max;
	else return num;
}

float ScreenDrawPosF(int screenSize, float drawPosPercent) {
	return screenSize * drawPosPercent / 100;
}

int ScreenDrawPosI(int screenSize, float drawPosPercent) {
	return(int)(screenSize * drawPosPercent / 100);
}
int TextDrawCenterPosX(float left, float right, std::string text, int font) {
	return (int)(((right - left) - GetDrawFormatStringWidthToHandle(font, const_cast<char*>(text.c_str()))) / 2 + left);

}
int TextDrawCenterPosY(float top, float bottom, int fontSize, std::string text) {
	return (int)(((bottom - top) - fontSize) / 2 + top);
}

bool IsDrawInGame() {
	return currentScreenType == INGAME || currentScreenType == PAUSE || currentScreenType == GAMEOVER || currentScreenType == CLEAR;
}


float ChangeRadians(float num) {
	return num * DX_PI_F / 180;
}
