#include "Button.h"

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

void Button::Draw()const {
	ScreenSize screen = GameBase::Instance().GetScreenSize();
	// ボタンの座標をスクリーン座標に変換
	int drawPosX = ScreenDrawPosI(screen.width, centerPos.x);
	int drawPosY = ScreenDrawPosI(screen.height, centerPos.y);
	// ボタンの幅と高さをスクリーン座標に変換する
	int width = ScreenDrawPosI(screen.width, (float)widthLength);
	int height = ScreenDrawPosI(screen.height, (float)heightLength);

	DrawBox((drawPosX - width), (drawPosY - height), (drawPosX + width), (drawPosY + height), buttonColor, TRUE);	// ボタン本体
	DrawBox(drawPosX, (drawPosY + (int)(height * 0.9f)), (drawPosX + width), (drawPosY + (int)(height * 1.35f)), buttonColor, TRUE);	// ボタン右下の長方形
	DrawTriangleAA((float)drawPosX, (float)drawPosY + ((float)height * 0.9f), (float)drawPosX, (float)drawPosY + ((float)height * 1.35f), (float)drawPosX - ((float)width * 0.2f), (float)drawPosY + ((float)height * 0.9f), buttonColor, TRUE);

	// テキストを中央に配置するか右下に配置するかで描画座標の計算を変える
	float  textBoxLeft = isCenter ? (float)(drawPosX - width) : (float)drawPosX;
	float textBoxTop = isCenter ? (float)(drawPosY - height) : (float)(drawPosY + height);
	float textBoxRight = (float)(drawPosX + width);
	float textBoxBottom = isCenter ? (float)(drawPosY + height) : (float)(drawPosY + height * 1.35f);

	// 上で計算した座標を使ってテキストを描画
	DrawTextCenter(textBoxLeft, textBoxTop, textBoxRight, textBoxBottom, drawText, fontType);
}
void Button::SetButtonColor(int changeColor) {
	buttonColor = changeColor;
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



VECTOR buttonMovePos = START_BUTTON_POS;
VECTOR buttonPos = START_BUTTON_POS;

int buttonMap[BUTTON_NUM_SCREEN][BUTTON_NUM_Y][BUTTON_NUM_X] = {
	{ {0,0,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,1,0,0,0,0}, {0,0,0,0,0,0} }, // TITLE
	{ {0,0,0,0,0,0}, {0,1,1,1,0,0}, {0,1,1,1,1,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // STAGESELECT
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // PAUSE
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }, // GAMEOVER
	{ {0,0,0,0,0,0}, {0,1,1,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0}, {0,0,0,0,0,0} }  // STAGECLEAR
};

void ButtonMovement() {
	// 現在の画面に属しているボタンのみ描画する：色をすべて非選択状態に設定する
	for (auto* btn : buttonArray) {
		if (btn->GetBelongScreen() == currentScreenType) {
			btn->Draw();
			btn->SetButtonColor(COLOR_LIGHTGRAY);
		}
	}
	// フェード中にボタンを移動できないようにする
	if (!isFading) {
		if (CheckHitKeyDown(KEY_INPUT_UP) || CheckHitKeyDown(KEY_INPUT_W)) buttonMovePos.y += -1;
		if (CheckHitKeyDown(KEY_INPUT_DOWN) || CheckHitKeyDown(KEY_INPUT_S)) buttonMovePos.y += 1;
		if (CheckHitKeyDown(KEY_INPUT_LEFT) || CheckHitKeyDown(KEY_INPUT_A)) buttonMovePos.x += -1;
		if (CheckHitKeyDown(KEY_INPUT_RIGHT) || CheckHitKeyDown(KEY_INPUT_D)) buttonMovePos.x += 1;
	}

	// ボタンの移動範囲を制限
	buttonMovePos.x = ClampNumF(buttonMovePos.x, 0, BUTTON_NUM_X - 1);
	buttonMovePos.y = ClampNumF(buttonMovePos.y, 0, BUTTON_NUM_Y - 1);

	// ボタンを押しているかのフラグを立てる：画面を変えた際にボタンのボタンの座標がずれてビープ音が鳴るのを防ぐ
	bool isMoveInput = CheckHitKeyDown(KEY_INPUT_UP) || CheckHitKeyDown(KEY_INPUT_DOWN) || CheckHitKeyDown(KEY_INPUT_LEFT) || CheckHitKeyDown(KEY_INPUT_RIGHT) || CheckHitKeyDown(KEY_INPUT_W) || CheckHitKeyDown(KEY_INPUT_S) || CheckHitKeyDown(KEY_INPUT_A) || CheckHitKeyDown(KEY_INPUT_D);
	if (buttonMap[currentScreenType][(int)buttonMovePos.y][(int)buttonMovePos.x] == 0) {	// 移動先にボタンが無い場合はビープ音を鳴らして移動前の座標に戻す
		if (isMoveInput)PlaySE(se[BUTTON_BEEP]);
		buttonMovePos = buttonPos;
	}
	else if (buttonPos.x != buttonMovePos.x || buttonPos.y != buttonMovePos.y) {	// 移動先にボタンがある、かつボタンの座標が変わっている場合は移動音を鳴らす
		PlaySE(se[BUTTON_MOVE]);
	}
	buttonPos = buttonMovePos;	// ボタンの座標を更新

	// 選択されているボタンの色を最後に変更
	Button* selected = SelectGetButtonArray();
	if (selected != nullptr) {
		selected->SetButtonColor(COLOR_MINTGREEN);
	}
}

void ButtonPressed() {
	if (isFading) return;
	if (CheckHitKeyDown(KEY_INPUT_SPACE) || CheckHitKeyDown(KEY_INPUT_RETURN)) {
		PlaySE(se[BUTTON_SELECT]);	// 押されたら選択音を鳴らす
		Button* selected = SelectGetButtonArray();
		switch (selected->GetButtonType())	// ボタンごとに処理を分岐
		{
		case Button::GAMESTART:
			ChangeUIState(INGAME, FADEOUT);
			GameBase::Instance().SetStageNumber(1);
			drawText = START_COUNTDOWN_1;
			break;
		case Button::RESUME:
			ChangeUIState(INGAME, SCREENSETUP);
			drawText = START_COUNTDOWN_1;
			break;
		case Button::RETRY:
			ChangeUIState(INGAME, FADEOUT);
			drawText = START_COUNTDOWN_1;
			break;
		case Button::NEXTSTAGE:
			GameBase::Instance().SetStageNumber(GameBase::Instance().GetStageNumber()+1);
			ChangeUIState(INGAME, FADEOUT);
			drawText = START_COUNTDOWN_1;
			break;
		case Button::OPENSTAGESELECT:
			ChangeUIState(STAGESELECT, SCREENSETUP);
			break;
		case Button::GAMEQUIT:
			DxLib_End();
			break;
		case Button::RETURNTITLE:
			ChangeUIState(TITLE, SCREENSETUP);
			break;
		case Button::SELECTSTAGE1:
			ChangeUIState(INGAME, FADEOUT);
			drawText = START_COUNTDOWN_1;
			GameBase::Instance().SetStageNumber(1);
			break;
		case Button::SELECTSTAGE2:
			ChangeUIState(INGAME, FADEOUT);
			drawText = START_COUNTDOWN_1;
			GameBase::Instance().SetStageNumber(2);
			break;
		case Button::SELECTSTAGE3:
			ChangeUIState(INGAME, FADEOUT);
			drawText = START_COUNTDOWN_1;
			GameBase::Instance().SetStageNumber(3);
			break;
		case Button::SELECTSTAGE4:
			ChangeUIState(INGAME, FADEOUT);
			drawText = START_COUNTDOWN_1;
			GameBase::Instance().SetStageNumber(4);
			break;
		case Button::SELECTSTAGE5:
			ChangeUIState(INGAME, FADEOUT);
			drawText = START_COUNTDOWN_1;
			GameBase::Instance().SetStageNumber(5);
			break;
		case Button::SELECTSTAGE6:
			ChangeUIState(INGAME, FADEOUT);
			drawText = START_COUNTDOWN_1;
			GameBase::Instance().SetStageNumber(6);
			break;
		case Button::GAMEEXIT:
			ChangeUIState(TITLE, FADEOUT);
			break;
		}
	}
}

Button* SelectGetButtonArray() {
	for (auto* btn : buttonArray) {
		// 属している画面、ボタンの座標が一致するボタンを返す
		if (btn->GetColumNum() == (int)buttonPos.y && btn->GetRowNum() == (int)buttonPos.x && btn->GetBelongScreen() == currentScreenType)
			return btn;
	}
	return nullptr;
}

