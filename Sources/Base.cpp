#include "Main.h"
#include "UI.h"
Base base;

void Base::SetScreenSize() {
	// モニターサイズを取得した後、そのサイズに合わせてウィンドウサイズを設定
	screen.width = GetSystemMetrics(SM_CXSCREEN);
	screen.height = GetSystemMetrics(SM_CYSCREEN);
	ChangeWindowMode(TRUE);
	SetGraphMode(screen.width, screen.height, 32);
}

float Base::ClampNumF(float num, float min, float max) {
	if (num < min) return min;
	else if (num > max) return max;
	else return num;
}

int Base::ClampNumI(int num, int min, int max) {
	if (num < min) return min;
	else if (num > max) return max;
	else return num;
}

float Base::ScreenDrawPosF(int screenSize, float drawPosPercent) {
	// 画面サイズに描画したい一の％をかけて100で割ることで描画座標を求める
	return screenSize * drawPosPercent / 100;
}

int Base::ScreenDrawPosI(int screenSize, float drawPosPercent) {
	// 画面サイズに描画したい一の％をかけて100で割ることで描画座標を求める
	return(int)(screenSize * drawPosPercent / 100);
}

int Base::TextDrawCenterPosX(float left, float right, std::string text, int font) {
	// 左右の差を求め、描画する文字列の幅を引いたものを2で割り余白を計算したのちに左端の座標を足すことで中央の座標を求める
	return (int)(((right - left) - GetDrawFormatStringWidthToHandle(font, const_cast<char*>(text.c_str()))) / 2 + left);
}

int Base::TextDrawCenterPosY(float top, float bottom, int fontSize, std::string text) {
	// 上下の差を求め、フォントサイズを引いたものを2で割り余白を計算したのちに上部の座標を足すことで中央の座標を求める
	return (int)(((bottom - top) - fontSize) / 2 + top);
}

bool Base::IsDrawInGame() {
	// ステージを裏で描画する画面を返す
	return currentScreenType == INGAME || currentScreenType == PAUSE || currentScreenType == GAMEOVER || currentScreenType == CLEAR;
}

constexpr float Base::ChangeRadians(float num) {
	// 度数法をラジアンに変換
	return num * DX_PI_F / 180;
}
