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
	// 画面サイズに描画したい一の％をかけて100で割ることで描画座標を求める
	return screenSize * drawPosPercent / 100;
}

int ScreenDrawPosI(int screenSize, float drawPosPercent) {
	// 画面サイズに描画したい一の％をかけて100で割ることで描画座標を求める
	return(int)(screenSize * drawPosPercent / 100);
}

int TextDrawCenterPosX(float left, float right, std::string text, int font) {
	// 左右の差を求め、描画する文字列の幅を引いたものを2で割り余白を計算したのちに左端の座標を足すことで中央の座標を求める
	return (int)(((right - left) - GetDrawFormatStringWidthToHandle(font, const_cast<char*>(text.c_str()))) / 2 + left);
}

int TextDrawCenterPosY(float top, float bottom, int fontSize, std::string text) {
	// 上下の差を求め、フォントサイズを引いたものを2で割り余白を計算したのちに上部の座標を足すことで中央の座標を求める
	return (int)(((bottom - top) - fontSize) / 2 + top);
}

bool IsDrawInGame() {
	// ステージを裏で描画する画面を返す
	return currentScreenType == INGAME || currentScreenType == PAUSE || currentScreenType == GAMEOVER || currentScreenType == CLEAR;
}


float ChangeRadians(float num) {
	// 度数法をラジアンに変換
	return num * DX_PI_F / 180;
}
