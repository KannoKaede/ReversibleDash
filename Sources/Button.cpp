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
	// ボタンの左右上下の%で表す座標を求める
	float leftPct = area.position.x - area.width;
	float topPct = area.position.y - area.height;
	float rightPct = area.position.x + area.width;
	float bottomPct = area.position.y + area.height;
	// ボタン背景枠を描画
	uiManager.DrawRoundRect(leftPct, topPct, rightPct, bottomPct, area.height * 0.5f, buttonColor,ANGLE_NONE);

	// ボタンの左右上下の座標を計算する
	float boxLeft = base.ScreenDrawPosF(base.GetScreen().width, leftPct);
	float boxTop = base.ScreenDrawPosF(base.GetScreen().height, topPct);
	float boxRight = base.ScreenDrawPosF(base.GetScreen().width, rightPct);
	float  boxBottom = base.ScreenDrawPosF(base.GetScreen().height, bottomPct);

	uiManager.DrawStringCenter(boxLeft, boxTop, boxRight, boxBottom, drawText, fontType);
}

void ButtonManager::UpdateButtonSelection() {
	// 現在の画面に属しているボタンを探す
	for (auto* btn : buttonArray) {
		// 属しているボタンのみを描画する
		if (uiManager.CheckScreen(btn->GetScreen())) {
			btn->Draw();
			btn->SetButtonColor(COLOR_LIGHTGRAY);	// 1度色を非選択状態の色に変更
		}
	}

	// フェード中はボタンを移動させない
	if (!fadeManager.GetIsFading()) {
		// ボタン座標移動処理
		if (input.KeyDown(KEY_INPUT_UP) || input.KeyDown(KEY_INPUT_W)) buttonMovePos.y += -1;
		if (input.KeyDown(KEY_INPUT_DOWN) || input.KeyDown(KEY_INPUT_S)) buttonMovePos.y += 1;
		if (input.KeyDown(KEY_INPUT_LEFT) || input.KeyDown(KEY_INPUT_A)) buttonMovePos.x += -1;
		if (input.KeyDown(KEY_INPUT_RIGHT) || input.KeyDown(KEY_INPUT_D)) buttonMovePos.x += 1;
	}

	// ボタンの移動範囲を制限
	buttonMovePos.x = base.ClampNumF(buttonMovePos.x, 0, BUTTON_NUM_X - 1);
	buttonMovePos.y = base.ClampNumF(buttonMovePos.y, 0, BUTTON_NUM_Y - 1);

	// 移動先にボタンが存在しない(0)の場合は移動前の座標に戻した後、ビープ音を再生
	if (buttonMap[uiManager.GetCurrentScreen()][(int)buttonMovePos.y][(int)buttonMovePos.x] == 0) {
		buttonMovePos = buttonPos;
		audioManager.PlaySE(audioManager.BUTTON_BEEP);
	}
	// 移動先にボタンが存在し、ボタン座標を動かしていた場合ボタン移動音を再生
	else if (buttonPos.x != buttonMovePos.x || buttonPos.y != buttonMovePos.y) {
		audioManager.PlaySE(audioManager.BUTTON_MOVE);
	}

	buttonPos = buttonMovePos;	// ボタンの座標を更新

	// 選択されているボタンの色を最後に変更する
	GetSelectButton()->SetButtonColor(COLOR_ORANGE);
}

void ButtonManager::ButtonPressed() {
	if (fadeManager.GetIsFading()) return;

	if (input.KeyDown(KEY_INPUT_SPACE) || input.KeyDown(KEY_INPUT_RETURN)) {
		audioManager.PlaySE(audioManager.BUTTON_SELECT);	// ボタン選択音を再生
		Button* selected = GetSelectButton();
		switch (selected->GetButtonType())	// ボタンごとに処理を分岐
		{
			// フェード処理を挟み、インゲームに遷移するボタン群
		case ButtonType::Start:
		case ButtonType::Retry:
		case ButtonType::Next:
		case ButtonType::PickStage:
			fadeManager.ChangeUIState(INGAME, FADEOUT);
			uiManager.SetIsStartCountDown(true);
			// ステージ1に移動
			if (selected->GetButtonType() == ButtonType::Start)
				base.nextStageNumber = 1;
			// 次のステージに移動
			if (selected->GetButtonType() == ButtonType::Next)
				base.nextStageNumber = base.GetStageNumber() + 1;
			// ボタンの座標を利用して指定のステージに移動
			if (selected->GetButtonType() == ButtonType::PickStage)
				base.nextStageNumber = (selected->GetColumnNum() - 1) * 3 + selected->GetRowNum();
			break;
		case ButtonType::Resume:	// ポーズ・ゲーム再開ボタン
			fadeManager.ChangeUIState(INGAME, NOTFADE);
			uiManager.SetIsStartCountDown(true);
			break;
		case ButtonType::StageSelect:	// ステージセレクト画面に移動するボタン
			fadeManager.ChangeUIState(SCREEN_TYPE::STAGESELECT, NOTFADE);
			break;
		case ButtonType::Quit:	// exeを落とすボタン
			DxLib_End();
			break;
		case ButtonType::ReturnTitle:	// ステージセレクトからタイトルに戻るボタン
			fadeManager.ChangeUIState(TITLE, NOTFADE);
			break;
		case ButtonType::Exit:	// ゲームからタイトルに戻るボタン
			fadeManager.ChangeUIState(TITLE, FADEOUT);
			break;
		}
	}
}

Button* ButtonManager::GetSelectButton()const {
	for (auto* btn : buttonArray) {
		// 属している画面、ボタンの座標が一致するボタンを返す
		if (btn->GetColumnNum() == (int)buttonPos.y && btn->GetRowNum() == (int)buttonPos.x && uiManager.CheckScreen(btn->GetScreen()))
			return btn;
	}
	return nullptr;
}

