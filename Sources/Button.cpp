#include "Audio.h"
#include "Button.h"
#include "Input.h"
#include "Main.h"

ButtonManager buttonManager;

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
	buttonManager.SetButtonArray(this);
}

void Button::Draw()const {
	// ボタンの座標をスクリーン座標に変換
	int drawPosX = base.ScreenDrawPosI(base.GetScreen().width, centerPos.x);
	int drawPosY = base.ScreenDrawPosI(base.GetScreen().height, centerPos.y);
	// ボタンの幅と高さをスクリーン座標に変換する
	int width = base.ScreenDrawPosI(base.GetScreen().width, (float)widthLength);
	int height = base.ScreenDrawPosI(base.GetScreen().height, (float)heightLength);

	DrawBox((drawPosX - width), (drawPosY - height), (drawPosX + width), (drawPosY + height), buttonColor, TRUE);	// ボタン本体
	DrawBox(drawPosX, (drawPosY + (int)(height * 0.9f)), (drawPosX + width), (drawPosY + (int)(height * 1.35f)), buttonColor, TRUE);	// ボタン右下の長方形
	DrawTriangleAA((float)drawPosX, (float)drawPosY + ((float)height * 0.9f), (float)drawPosX, (float)drawPosY + ((float)height * 1.35f), (float)drawPosX - ((float)width * 0.2f), (float)drawPosY + ((float)height * 0.9f), buttonColor, TRUE);

	// テキストを中央に配置するか右下に配置するかで描画座標の計算を変える
	float  textBoxLeft = isCenter ? (float)(drawPosX - width) : (float)drawPosX;
	float textBoxTop = isCenter ? (float)(drawPosY - height) : (float)(drawPosY + height);
	float textBoxRight = (float)(drawPosX + width);
	float textBoxBottom = isCenter ? (float)(drawPosY + height) : (float)(drawPosY + height * 1.35f);

	// 上で計算した座標を使ってテキストを描画
	uiManager.DrawStringCenter(textBoxLeft, textBoxTop, textBoxRight, textBoxBottom, drawText, fontType);
}

void ButtonManager::ButtonMovement() {
	// 現在の画面に属しているボタンのみ描画する：色をすべて非選択状態に設定する
		for (auto* btn : buttonArray) {
			if (uiManager.CheckScreen(btn->GetBelongScreen())) {
				btn->Draw();
				btn->SetButtonColor(COLOR_LIGHTGRAY);
			}
		}
	// フェード中にボタンを移動できないようにする
	if (!fadeManager.GetIsFading()) {
		if (input.KeyDown(KEY_INPUT_UP) || input.KeyDown(KEY_INPUT_W)) buttonMovePos.y += -1;
		if (input.KeyDown(KEY_INPUT_DOWN) || input.KeyDown(KEY_INPUT_S)) buttonMovePos.y += 1;
		if (input.KeyDown(KEY_INPUT_LEFT) || input.KeyDown(KEY_INPUT_A)) buttonMovePos.x += -1;
		if (input.KeyDown(KEY_INPUT_RIGHT) || input.KeyDown(KEY_INPUT_D)) buttonMovePos.x += 1;
	}

	// ボタンの移動範囲を制限
	buttonMovePos.x = base.ClampNumF(buttonMovePos.x, 0, BUTTON_NUM_X - 1);
	buttonMovePos.y = base.ClampNumF(buttonMovePos.y, 0, BUTTON_NUM_Y - 1);

	// ボタンを押しているかのフラグを立てる：画面を変えた際にボタンのボタンの座標がずれてビープ音が鳴るのを防ぐ
	bool isMoveInput = input.KeyDown(KEY_INPUT_UP) || input.KeyDown(KEY_INPUT_DOWN) || input.KeyDown(KEY_INPUT_LEFT) || input.KeyDown(KEY_INPUT_RIGHT) || input.KeyDown(KEY_INPUT_W) || input.KeyDown(KEY_INPUT_S) || input.KeyDown(KEY_INPUT_A) || input.KeyDown(KEY_INPUT_D);
	if (buttonMap[uiManager.GetCurrentScreen()][(int)buttonMovePos.y][(int)buttonMovePos.x] == 0) {	// 移動先にボタンが無い場合はビープ音を鳴らして移動前の座標に戻す
		if (isMoveInput)audioManager.PlaySE(audioManager.BUTTON_BEEP);
		buttonMovePos = buttonPos;
	}
	else if (buttonPos.x != buttonMovePos.x || buttonPos.y != buttonMovePos.y) {	// 移動先にボタンがある、かつボタンの座標が変わっている場合は移動音を鳴らす
		audioManager.PlaySE(audioManager.BUTTON_MOVE);
	}
	buttonPos = buttonMovePos;	// ボタンの座標を更新

	// 選択されているボタンの色を最後に変更
	Button* selected = SelectGetButtonArray();
	if (selected != nullptr) {
		selected->SetButtonColor(COLOR_MINTGREEN);
	}
}

void ButtonManager::ButtonPressed() {
	if (fadeManager.GetIsFading()) return;
	if (input.KeyDown(KEY_INPUT_SPACE) || input.KeyDown(KEY_INPUT_RETURN)) {
		audioManager.PlaySE(audioManager.BUTTON_SELECT);	// 押されたら選択音を鳴らす
		Button* selected = SelectGetButtonArray();
		switch (selected->GetButtonType())	// ボタンごとに処理を分岐
		{
			// フェード処理を挟むかつインゲームに遷移するボタンをまとめた
		case Button::GAMESTART:
		case Button::RETRY:
		case Button::NEXTSTAGE:
		case Button::SELECTSTAGE:
			fadeManager.ChangeUIState(INGAME, fadeManager.FADEOUT);
			uiManager.SetIsStartCountDown(true);
			// ステージ1に移動
			if (selected->GetButtonType() == Button::GAMESTART)
				base.SetStageNumber(1);
			// 次のステージに移動
			if (selected->GetButtonType() == Button::NEXTSTAGE)
				base.SetStageNumber(base.GetStageNumber() + 1);
			// ボタンの座標を利用して指定のステージに移動
			if (selected->GetButtonType() == Button::SELECTSTAGE)
				base.SetStageNumber((selected->GetColumNum() - 1) * 3 + selected->GetRowNum());
			break;
		case Button::RESUME:
			fadeManager.ChangeUIState(INGAME, fadeManager.NOTFADE);
			uiManager.SetIsStartCountDown(true);
			break;
		case Button::OPENSTAGESELECT:
			fadeManager.ChangeUIState(STAGESELECT, fadeManager.NOTFADE);
			break;
		case Button::GAMEQUIT:
			DxLib_End();
			break;
		case Button::RETURNTITLE:
			fadeManager.ChangeUIState(TITLE, fadeManager.NOTFADE);
			break;
		case Button::GAMEEXIT:
			fadeManager.ChangeUIState(TITLE, fadeManager.FADEOUT);
			break;
		}
	}
}

Button* ButtonManager::SelectGetButtonArray() {
	for (auto* btn : buttonArray) {
		// 属している画面、ボタンの座標が一致するボタンを返す
		if (btn->GetColumNum() == (int)buttonPos.y && btn->GetRowNum() == (int)buttonPos.x && uiManager.CheckScreen(btn->GetBelongScreen()))
			return btn;
	}
	return nullptr;
}

