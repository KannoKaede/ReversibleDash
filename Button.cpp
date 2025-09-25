#include "Button.h"
#include "Input.h"

std::vector<Button*> buttonArray;

Button::Button(SCREEN_TYPE screen, int y, int x, VECTOR center, int width, int height, BUTTON_TYPE button, std::string text, int font) {
	belongScreen = screen;
	columnNum = y;
	rowNum = x;
	centerPos = center;
	widthLength = width;
	heightLength = height;
	buttonType = button;
	drawText = text;
	fontType = font;
	buttonArray.push_back(this);
}

void Button::Draw() {
	DrawBox(GetDrawPos(screenWidth, centerPos.x, -widthLength),
		GetDrawPos(screenHeight, centerPos.y, heightLength),
		GetDrawPos(screenWidth, centerPos.x, widthLength),
		GetDrawPos(screenHeight, centerPos.y, -heightLength),
		buttonColor, TRUE);
}
void Button::SetButtonColor(int changeColor) {
	buttonColor = changeColor;
}

int Button::GetDrawPos(int screenSize, float pos, int length) {
	return screenSize * ((int)pos + length / 2) / 100;
}

Button::BUTTON_TYPE Button::GetButtonType() {
	return buttonType;
}

SCREEN_TYPE Button::GetBelongScreen() {
	return belongScreen;
}

int Button::GetColumNum() {
	return columnNum;
}

int Button::GetRowNum() {
	return rowNum;
}



VECTOR buttonMovePos;
VECTOR buttonPos;

int buttonMap[BUTTON_NUM_SCREEN][BUTTON_NUM_Y][BUTTON_NUM_X] = {
	{ {1,0,0,0}, {1,0,0,0}, {1,0,0,0}, {0,0,0,0} }, // TITLE
	{ {1,1,1,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} }, // STAGESELECT
	{ {1,1,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} }, // PAUSE
	{ {1,1,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} }, // GAMEOVER
	{ {1,1,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} }  // STAGECLEAR
};

void ButtonMovement() {
	if (CheckHitKeyDown(KEY_INPUT_UP)) buttonMovePos.y += -1;
	if (CheckHitKeyDown(KEY_INPUT_DOWN)) buttonMovePos.y += 1;
	if (CheckHitKeyDown(KEY_INPUT_LEFT)) buttonMovePos.x += -1;
	if (CheckHitKeyDown(KEY_INPUT_RIGHT)) buttonMovePos.x += 1;

	ClampNum(buttonMovePos.x, 0, BUTTON_NUM_X - 1);
	ClampNum(buttonMovePos.y, 0, BUTTON_NUM_Y - 1);

	if (buttonMap[currentScreenType][(int)buttonMovePos.y][(int)buttonMovePos.x] == 0) {
		buttonMovePos = buttonPos;
	}
	else {
		buttonPos = buttonMovePos;
	}

	for (int i = 0; i < buttonArray.size(); i++) {
		buttonArray[i]->SetButtonColor(BUTTON_NORMAL_COLOR);
	}

	Button* selected = SelectGetButtonArray();
	if (selected != nullptr) {
		selected->SetButtonColor(BUTTON_SELECT_COLOR);
	}
}

void ButtonPressed() {
	if (CheckHitKeyDown(KEY_INPUT_SPACE)) {
		Button* selected = SelectGetButtonArray();
		switch (selected->GetButtonType())
		{
		case Button::GAMESTART:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			stageNumber = 1;
			break;
		case Button::RESUME:
			nextScreenType = INGAME;
			fadeState = SCREENSETUP;
			break;
		case Button::RETRY:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			break;
		case Button::NEXTSTAGE:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			stageNumber++;
			break;
		case Button::OPENSTAGESELECT:
			nextScreenType = STAGESELECT;
			fadeState = SCREENSETUP;
			break;
		case Button::GAMEQUIT:
			isGameQuit = true;
			break;
		case Button::RETURNTITLE:
			nextScreenType = TITLE;
			fadeState = SCREENSETUP;
			break;
		case Button::SELECTSTAGE1:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			stageNumber = 1;
			break;
		case Button::SELECTSTAGE2:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			stageNumber = 2;
			break;
		case Button::SELECTSTAGE3:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			stageNumber = 3;
			break;
		case Button::SELECTSTAGE4:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			stageNumber = 4;
			break;
		case Button::SELECTSTAGE5:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			stageNumber = 5;
			break;
		case Button::SELECTSTAGE6:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			stageNumber = 6;
			break;
		case Button::GAMEEXIT:
			nextScreenType = TITLE;
			fadeState = FADEOUT;
			break;

		default:
			break;
		}
	}
}
//SELECTSTAGE,   // ステージ選択
//RESUME,	// ゲーム再開
//GAMEEXIT,	// インゲーム終了
//RETRY,	// リトライ
//NEXTSTAGE,	// 次のステージへ
//RETURNTITLE,	// タイトルへ戻る

Button* SelectGetButtonArray() {
	for (int i = 0; i < buttonArray.size(); i++) {
		if (buttonArray[i]->GetColumNum() == (int)buttonPos.y &&
			buttonArray[i]->GetRowNum() == (int)buttonPos.x &&
			buttonArray[i]->GetBelongScreen() == currentScreenType) {
			return buttonArray[i];
		}
	}
	return nullptr;
}

float ClampNum(float num, float min, float max) {
	if (num < min) return min;
	else if (num > max) return max;
	else return num;
}
