#include "Main.h"
#include "UI.h"
#include <random>
Base base;

void Base::SetScreenSize() {
	// モニターサイズを取得した後、そのサイズに合わせてウィンドウサイズを設定
	screen.width = GetSystemMetrics(SM_CXSCREEN);
	screen.height = GetSystemMetrics(SM_CYSCREEN);
	ChangeWindowMode(TRUE);
	SetGraphMode(screen.width, screen.height, 32);
}
void Base::FontSetUp() {
	// フォントサイズを設定した後、フォントをロードする
	AddFontResourceExA("Resource/Fonts/ちはやチョーク.ttf", FR_PRIVATE, NULL);
	fontData[EXTRALARGE].size = screen.width / 12;
	fontData[LARGE].size = screen.width / 25;
	fontData[MEDIUM].size = screen.width / 50;
	fontData[SMALL].size = screen.width / 60;
	fontData[EXTRALARGE].handle = CreateFontToHandle("ちはやチョーク", fontData[EXTRALARGE].size, 5, DX_FONTTYPE_ANTIALIASING);
	fontData[LARGE].handle = CreateFontToHandle("ちはやチョーク", fontData[LARGE].size, 3, DX_FONTTYPE_ANTIALIASING);
	fontData[MEDIUM].handle = CreateFontToHandle("ちはやチョーク", fontData[MEDIUM].size, 1, DX_FONTTYPE_ANTIALIASING);
	fontData[SMALL].handle = CreateFontToHandle("ちはやチョーク", fontData[SMALL].size, 1, DX_FONTTYPE_ANTIALIASING);
}

float Base::ClampNumF(float _num, float _min, float _max)const {
	if (_num < _min) return _min;
	else if (_num > _max) return _max;
	else return _num;
}

int Base::ClampNumI(int _num, int _min, int _max)const {
	if (_num < _min) return _min;
	else if (_num > _max) return _max;
	else return _num;
}

float Base::ScreenDrawPosF(int _screenSize, float _drawPosPct) {
	// 画面サイズに描画したい位置の％をかけて100で割ることで描画座標を求める
	return _screenSize * _drawPosPct / 100;
}

int Base::ScreenDrawPosI(int _screenSize, float _drawPosPercent) {
	// 画面サイズに描画したい位置の％をかけて100で割ることで描画座標を求める
	return(int)(_screenSize * _drawPosPercent / 100);
}

int Base::TextDrawCenterPosX(float _left, float _right, const std::string& _text, int _font) {
	// 左右の差を求め、描画する文字列の幅を引いたものを2で割り余白を計算したのちに左端の座標を足すことで中央の座標を求める
	return (int)(((_right - _left) - GetDrawFormatStringWidthToHandle(_font, const_cast<char*>(_text.c_str()))) / 2 + _left);
}

int Base::TextDrawCenterPosY(float _top, float _bottom, int _fontSize, const std::string& _text) {
	// 上下の差を求め、フォントサイズを引いたものを2で割り余白を計算したのちに上部の座標を足すことで中央の座標を求める
	return (int)(((_bottom - _top) - _fontSize) / 2 + _top);
}

bool Base::IsDrawInGame() {
	// ステージを裏で描画する画面を返す
	return uiManager.CheckScreen(INGAME) || uiManager.CheckScreen(PAUSE) || uiManager.CheckScreen(GAMEOVER) || uiManager.CheckScreen(STAGECLEAR) || uiManager.CheckScreen(GAMECLEAR);
}

int Base::Random(int _min, int _max) {
	static std::mt19937 rng(std::random_device{}());  // 乱数の種を初期化
	std::uniform_int_distribution<int> dist(_min, _max);	// 指定の値の乱数を作成
	return dist(rng);
}