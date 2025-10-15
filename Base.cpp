#include "Main.h"

float ClampNum(float num, float min, float max) {
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
	return (int)(((right - left) - GetDrawFormatStringWidthToHandle(font, const_cast<char*>(text.c_str()))) / 2 + left);	// ¶‰E’†‰›‚ğŒvZ

}
int TextDrawCenterPosY(float top, float bottom,int fontSize, std::string text, int font) {
	return (int)(((bottom - top) - fontSize) / 2 + top);	// ã‰º’†‰›‚ğŒvZ
}