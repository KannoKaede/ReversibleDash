#include "Button.h"
#include "InGame.h"


std::vector<Button*> buttonArray;

Button::Button(SCREEN_TYPE screen, int y, int x, VECTOR center, int width, int height, BUTTON_TYPE button, std::string text, int font, bool isCenterPos) {
	belongScreen = screen;
	columnNum = y;
	rowNum = x;
	centerPos = center;
	widthLength = width;
	heightLength = height;
	buttonType = button;
	drawText = text;
	fontType = font;
	isCenter = isCenterPos;
	buttonArray.push_back(this);
}

void Button::Draw() {
	DrawBox(ScreenDrawPosI(screenWidth, centerPos.x - widthLength), ScreenDrawPosI(screenHeight, centerPos.y - heightLength),
		ScreenDrawPosI(screenWidth, centerPos.x + widthLength), ScreenDrawPosI(screenHeight, centerPos.y + heightLength), buttonColor, TRUE);
	DrawBox(ScreenDrawPosI(screenWidth, centerPos.x), ScreenDrawPosI(screenHeight, centerPos.y + heightLength*0.9f),
		ScreenDrawPosI(screenWidth, centerPos.x+ widthLength), ScreenDrawPosI(screenHeight, centerPos.y+heightLength*1.35f), buttonColor, TRUE);
	DrawTriangleAA(ScreenDrawPosF(screenWidth, centerPos.x), ScreenDrawPosF(screenHeight, centerPos.y + heightLength * 0.9f), 
			ScreenDrawPosF(screenWidth, centerPos.x), ScreenDrawPosF(screenHeight, centerPos.y + heightLength * 1.35f), 
			ScreenDrawPosF(screenWidth, centerPos.x-widthLength*0.2f), ScreenDrawPosF(screenHeight, centerPos.y + heightLength * 0.9f), buttonColor, TRUE);
	isCenter ?
		DrawTextCenter(ScreenDrawPosF(screenWidth, centerPos.x - widthLength), ScreenDrawPosF(screenHeight, centerPos.y - heightLength),
			ScreenDrawPosF(screenWidth, centerPos.x + widthLength), ScreenDrawPosF(screenHeight, centerPos.y + heightLength), drawText, fontType) :
		DrawTextCenter(ScreenDrawPosF(screenWidth, centerPos.x), ScreenDrawPosF(screenHeight, centerPos.y + heightLength),
			ScreenDrawPosF(screenWidth, centerPos.x + widthLength), ScreenDrawPosF(screenHeight, centerPos.y + heightLength * 1.35f), drawText, fontType);
}
void Button::SetButtonColor(int changeColor) {
	buttonColor = changeColor;
}

int Button::GetDrawPos(int screenSize, float pos, int length)const {
	return screenSize * ((int)pos + length) / 100;
}

Button::BUTTON_TYPE Button::GetButtonType()const {
	return buttonType;
}

SCREEN_TYPE Button::GetBelongScreen()const {
	return belongScreen;
}

int Button::GetColumNum() const {
	return columnNum;
}

int Button::GetRowNum() const {
	return rowNum;
}



VECTOR buttonMovePos= STARTBUTTON_POS;
VECTOR buttonPos= STARTBUTTON_POS;

int buttonMap[BUTTON_NUM_SCREEN][BUTTON_NUM_Y][BUTTON_NUM_X] = {
	{ {0,0,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,0,0,0,0,0} }, // TITLE
	{ {0,0,0,0,0,0}, {0,1,1,1,0,0}, {0,1,1,1,1,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // STAGESELECT
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // PAUSE
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // GAMEOVER
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }  // STAGECLEAR
};

void ButtonMovement() {
	if (CheckHitKeyDown(KEY_INPUT_UP)) buttonMovePos.y += -1;
	if (CheckHitKeyDown(KEY_INPUT_DOWN)) buttonMovePos.y += 1;
	if (CheckHitKeyDown(KEY_INPUT_LEFT)) buttonMovePos.x += -1;
	if (CheckHitKeyDown(KEY_INPUT_RIGHT)) buttonMovePos.x += 1;

	buttonMovePos.x = ClampNum(buttonMovePos.x, 0, BUTTON_NUM_X - 1);
	buttonMovePos.y = ClampNum(buttonMovePos.y, 0, BUTTON_NUM_Y - 1);

	if (buttonMap[currentScreenType][(int)buttonMovePos.y][(int)buttonMovePos.x] == 0) {
		PlaySE(buttonBeepSE);
		buttonMovePos = buttonPos;
	}
		if (buttonPos.x != buttonMovePos.x|| buttonPos.y != buttonMovePos.y) {
			PlaySE(buttonMoveSE);
		}
		buttonPos = buttonMovePos;

	for (int i = 0; i < buttonArray.size(); i++) {
		buttonArray[i]->SetButtonColor(BUTTON_NORMAL_COLOR);
	}

	Button* selected = SelectGetButtonArray();
	if (selected != nullptr) {
		selected->SetButtonColor(BUTTON_SELECT_COLOR);
	}
}

void ButtonPressed() {
	if (currentScreenType == INGAME) {
		buttonMovePos = VGet(0, 0, 0);
		buttonPos = VGet(0, 0, 0);
		return;
	}
	if (CheckHitKeyDown(KEY_INPUT_SPACE) && !isFading) {
		PlaySE(buttonSelectSE);
		Button* selected = SelectGetButtonArray();
		switch (selected->GetButtonType())	// ボタンごとに処理を分岐：リファクタリングまとめられるところはまとめる
		{
		case Button::GAMESTART:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			stageNumber = 1;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
			break;
		case Button::RESUME:
			nextScreenType = INGAME;
			fadeState = SCREENSETUP;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
			break;
		case Button::RETRY:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
			break;
		case Button::NEXTSTAGE:
			stageNumber++;
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
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
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
			stageNumber = 1;
			break;
		case Button::SELECTSTAGE2:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
			stageNumber = 2;
			break;
		case Button::SELECTSTAGE3:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
			stageNumber = 3;
			break;
		case Button::SELECTSTAGE4:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
			stageNumber = 4;
			break;
		case Button::SELECTSTAGE5:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
			stageNumber = 5;
			break;
		case Button::SELECTSTAGE6:
			nextScreenType = INGAME;
			fadeState = FADEOUT;
			isGameStop = true;
			drawText = START_COUNTDOWN_1;
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

