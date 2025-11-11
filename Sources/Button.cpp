#include "Audio.h"
#include "Button.h"
#include "Input.h"
#include "Main.h"

ButtonManager buttonManager;

Button::Button(ButtonLocation _location, ButtonArea _area, ButtonType _buttonType, std::string _drawText, int _fontType) {
	location = _location;
	area = _area;
	buttonType = _buttonType;
	drawText = _drawText;
	fontType = _fontType;
	buttonManager.SetButtonArray(this);
}

void Button::Draw()const {
	// ボタンの上下左右の座標を計算
	int boxRight = base.ScreenDrawPosI(base.GetScreen().width, (area.position.x + area.width));
	int boxLeft = base.ScreenDrawPosI(base.GetScreen().width, (area.position.x - area.width));
	int  boxTop = base.ScreenDrawPosI(base.GetScreen().height, (area.position.y + area.height));
	int  boxBottom = base.ScreenDrawPosI(base.GetScreen().height, (area.position.y - area.height));

	DrawBox(boxLeft, boxTop, boxRight, boxBottom, buttonColor, TRUE);	// ボタン：長方形を描画

	// 上で計算した座標を使用してテキストを中央に描画
	uiManager.DrawStringCenter((float)boxLeft, (float)boxTop, (float)boxRight, (float)boxBottom, drawText, fontType);
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
		case ButtonType::Start:
		case ButtonType::Retry:
		case ButtonType::Next:
		case ButtonType::PickStage:
			fadeManager.ChangeUIState(INGAME, fadeManager.FADEOUT);
			uiManager.SetIsStartCountDown(true);
			// ステージ1に移動
			if (selected->GetButtonType() == ButtonType::Start)
				base.SetStageNumber(1);
			// 次のステージに移動
			if (selected->GetButtonType() == ButtonType::Next)
				base.SetStageNumber(base.GetStageNumber() + 1);
			// ボタンの座標を利用して指定のステージに移動
			if (selected->GetButtonType() == ButtonType::PickStage)
				base.SetStageNumber((selected->GetColumNum() - 1) * 3 + selected->GetRowNum());
			break;
		case ButtonType::Resume:
			fadeManager.ChangeUIState(INGAME, fadeManager.NOTFADE);
			uiManager.SetIsStartCountDown(true);
			break;
		case ButtonType::StageSelect:
			fadeManager.ChangeUIState(SCREEN_TYPE::STAGESELECT, fadeManager.NOTFADE);
			break;
		case ButtonType::Quit:
			DxLib_End();
			break;
		case ButtonType::ReturnTitle:
			fadeManager.ChangeUIState(TITLE, fadeManager.NOTFADE);
			break;
		case ButtonType::Exit:
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

