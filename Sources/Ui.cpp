#include "Main.h"
#include "UI.h"
#include "Score.h"
#include "Stage.h"
#include "Button.h"
#include "Input.h"

/*UIManagerクラス---------------------------------------------------------------------------------------------------------*/

// 使用する全てのボタンのインスタンスをここで用意：UIManager::SetUpの中に入れると起動時にクラッシュする
Button startBtn			({ TITLE,		1, 1 },	{ { 50, 47 }, 12, 4 },	ButtonType::Start,			"GameStart",	LARGE);
Button stageSelectBtn	({ TITLE,		2, 1 },	{ { 50, 65 }, 12, 4 },	ButtonType::StageSelect,	"StageSelect",	LARGE);
Button quitBtn			({ TITLE,		3, 1 },	{ { 50, 83 }, 12, 4 },	ButtonType::Quit,			"GameQuit",		LARGE);
Button pickStage1Btn	({ STAGESELECT, 1, 1 },	{ { 28, 48 },  5, 6 },	ButtonType::PickStage,		"Lv.1",			MEDIUM);
Button pickStage2Btn	({ STAGESELECT, 1, 2 },	{ { 50, 48 },  5, 6 },	ButtonType::PickStage,		"Lv.2",			MEDIUM);
Button pickStage3Btn	({ STAGESELECT, 1, 3 },	{ { 72, 48 },  5, 6 },	ButtonType::PickStage,		"Lv.3",			MEDIUM);
Button pickStage4Btn	({ STAGESELECT, 2, 1 },	{ { 28, 77 },  5, 6 },	ButtonType::PickStage,		"Lv.4",			MEDIUM);
Button pickStage5Btn	({ STAGESELECT, 2, 2 },	{ { 50, 77 },  5, 6 },	ButtonType::PickStage,		"Lv.5",			MEDIUM);
Button pickStage6Btn	({ STAGESELECT, 2, 3 },	{ { 72, 77 },  5, 6 },	ButtonType::PickStage,		"Lv.6",			MEDIUM);
Button returnTitleBtn	({ STAGESELECT, 2, 4 },	{ { 90, 79 },  3, 4 },	ButtonType::ReturnTitle,	"Back",			MEDIUM);
Button resumeBtn		({ PAUSE,		1, 1 },	{ { 39, 63 },  7, 4 },	ButtonType::Resume,			"Resume",		LARGE);
Button pauseExitBtn		({ PAUSE,		1, 2 },	{ { 61, 63 },  7, 4 },	ButtonType::Exit,			"Exit",			LARGE);
Button retryBtn			({ GAMEOVER,	1, 1 },	{ { 37, 70 },  8, 4 },	ButtonType::Retry,			"Retry",		LARGE);
Button gameOverExitBtn	({ GAMEOVER,	1, 2 },	{ { 63, 70 },  8, 4 },	ButtonType::Exit,			"Exit",			LARGE);
Button nextBtn			({ STAGECLEAR,	1, 1 },	{ { 37, 70 },  8, 4 },	ButtonType::Next,			"Next",			LARGE);
Button stageClearExitBtn({ STAGECLEAR,	1, 2 },	{ { 63, 70 },  8, 4 },	ButtonType::Exit,			"Exit",			LARGE);
Button gameClearExitBtn ({ GAMECLEAR,	1, 1 },	{ { 50, 70 },  8, 4 },	ButtonType::Exit,			"Exit",			LARGE);

UIManager uiManager;
FadeManager fadeManager;

void UIManager::SetUp() {
	// 使用する画像のロードとサイズ取得を行う
	keyWASD = { LoadGraph("Resource/Images/Keys/WASD.png") };
	GetGraphSize(keyWASD.image, &keyWASD.width, &keyWASD.height);
	keyEscape = { LoadGraph("Resource/Images/Keys/EscapeKey.png") };
	GetGraphSize(keyEscape.image, &keyEscape.width, &keyEscape.height);
	keySpace = { LoadGraph("Resource/Images/Keys/SpaceKey.png") };
	GetGraphSize(keySpace.image, &keySpace.width, &keySpace.height);
	explanations[0] = { LoadGraph("Resource/Images/Explanations/0_PlayerJump.png") };
	GetGraphSize(explanations[0].image, &explanations[0].width, &explanations[0].height);
	explanations[1] = { LoadGraph("Resource/Images/Explanations/0_JumpGauge.png") };
	GetGraphSize(explanations[1].image, &explanations[1].width, &explanations[1].height);
	explanations[2] = { LoadGraph("Resource/Images/Explanations/1_SmallCar.png") };
	GetGraphSize(explanations[2].image, &explanations[2].width, &explanations[2].height);
	explanations[3] = { LoadGraph("Resource/Images/Explanations/1_LargeCar.png") };
	GetGraphSize(explanations[3].image, &explanations[3].width, &explanations[3].height);
	explanations[4] = { LoadGraph("Resource/Images/Explanations/1_Cloud.png") };
	GetGraphSize(explanations[4].image, &explanations[4].width, &explanations[4].height);
	explanations[5] = { LoadGraph("Resource/Images/Explanations/1_ProgressBar.png") };
	GetGraphSize(explanations[5].image, &explanations[5].width, &explanations[5].height);
	explanations[6] = { LoadGraph("Resource/Images/Explanations/2_ScoreCar.png") };
	GetGraphSize(explanations[6].image, &explanations[6].width, &explanations[6].height);
	explanations[7] = { LoadGraph("Resource/Images/Explanations/2_ScoreCloud.png") };
	GetGraphSize(explanations[7].image, &explanations[7].width, &explanations[7].height);
}

void UIManager::DrawUI(Player& _player) {
	switch (currentScreen)
	{
	case TITLE:
		titleScene.Draw();
		if (input.KeyDown(KEY_INPUT_ESCAPE)) {
			fadeManager.ChangeUIState(EXPLANATION, NOTFADE);
			uiManager.explanationScene.SetCurrentPage(0);
		}
		break;
	case STAGESELECT:
		stageSelectScene.Draw();
		break;
	case PAUSE:
		pauseScene.Draw(_player);
		break;
	case GAMEOVER:
		gameOverScene.Draw();
		break;
	case STAGECLEAR:
	case GAMECLEAR:
		clearScene.Draw();
		break;
	case INGAME:
		inGameScene.Draw(_player);
		DrawJumpPct(_player.GetPressedJump());
		if (!isStartCountDown && input.KeyDown(KEY_INPUT_ESCAPE))  fadeManager.ChangeUIState(PAUSE, NOTFADE);
		break;
	case EXPLANATION:
		explanationScene.Draw();
		if (input.KeyDown(KEY_INPUT_ESCAPE)) fadeManager.ChangeUIState(TITLE, NOTFADE);
		break;
	}
}

// リファクタリング：文字を描画時の待機時間を実装できていない
/// <summary> スタートカウントダウンの描画を行うメソッド </summary>
void UIManager::DrawStartCountDown() {
	if (fadeManager.GetIsFading() || !isStartCountDown) return;	// フェード中、スタートカウントダウンの描画が終了したら処理に入らない
	if (startTime == 0) {	// 最初と文字を切り替えるタイミングのみ入る。
		if (drawCount >= 2) {	// 配列外に行ったら全て初期化して処理を止める
			isStartCountDown = false;
			drawCount = 0;
			startTime = 0;
			return;
		}
		// テキストの描画で使う変数をリセットする
		isFadeStart = true;	// フェードイン状態に切り替える
		startTime = GetNowCount();
		waitTime = START_WAITTIME[drawCount];
	}
	// 文字の描画
	fadeManager.DrawTextFade(DRAW_TEXT[drawCount], base.GetFontData(EXTRALARGE).handle, textFadeSpeed);
	// 一定時間経過したらテキストのフェード演出を開始する
	if (startTime + waitTime > GetNowCount())  return;

	// alpha値が0になったらalpha値を増やすように変更
	if (fadeManager.GetAlphaValue() == 0) {
		textFadeSpeed = TEXT_FADE_SPEED[drawCount][0];

		// フェードアウトで0になったらカウントを増やして描画する文字をリセットする
		if (!isFadeStart) {
			startTime = 0;	// 最初の待機に戻るために初期化
			drawCount++;
			return;
		}
	}

	// 文字を完全に描画出来たらフェードアウトするように切り替える
	else if (fadeManager.GetAlphaValue() == 255) {
		isFadeStart = false;
		if (drawCount == 1)base.SetIsGameStop(false);
		textFadeSpeed = TEXT_FADE_SPEED[drawCount][1];
	}
}

void UIManager::DrawProgressRateBar(const Player& player, float startPct, float endPct, float heightPct) {
	float progressPct = base.ClampNumF(player.GetPosition().x / stageManager.GetGoalPosition(base.GetStageNumber()), 0, 1);	// スタートから進んだ割合を求める
	float playerPct = (endPct - startPct) * progressPct;	// バー左端と右端の長さに進んだ割合をかけてバー上でのプレイヤーの座標を取得

	// バー背景の長方形を描画
	DrawBox(base.ScreenDrawPosI(base.GetScreen().width, startPct), base.ScreenDrawPosI(base.GetScreen().height, heightPct - 1),
		base.ScreenDrawPosI(base.GetScreen().width, endPct), base.ScreenDrawPosI(base.GetScreen().height, heightPct + 1), COLOR_LIGHTGRAY, TRUE);
	// バー背景左端の丸を描画
	DrawCircleAA(base.ScreenDrawPosF(base.GetScreen().width, startPct), base.ScreenDrawPosF(base.GetScreen().height, heightPct),
		base.ScreenDrawPosF(base.GetScreen().width, 0.8f), 64, COLOR_MINTGREEN, TRUE);
	// バー背景右端の丸を描画
	DrawCircleAA(base.ScreenDrawPosF(base.GetScreen().width, endPct), base.ScreenDrawPosF(base.GetScreen().height, heightPct),
		base.ScreenDrawPosF(base.GetScreen().width, 0.8f), 64, COLOR_LIGHTGRAY, TRUE);
	// プレイヤーの位置を表す丸を描画する
	DrawCircleAA(base.ScreenDrawPosF(base.GetScreen().width, startPct + playerPct), base.ScreenDrawPosF(base.GetScreen().height, heightPct),
		base.ScreenDrawPosF(base.GetScreen().width, 0.8f), 64, COLOR_MINTGREEN, TRUE);	// プレイヤー座標
	// プレイヤーの丸が通った後を緑に染める四角を描画
	DrawBox(base.ScreenDrawPosI(base.GetScreen().width, startPct), base.ScreenDrawPosI(base.GetScreen().height, heightPct - 1),
		base.ScreenDrawPosI(base.GetScreen().width, startPct + playerPct), base.ScreenDrawPosI(base.GetScreen().height, heightPct + 1), COLOR_MINTGREEN, TRUE);
}

void UIManager::DrawJumpPct(int _pressedJump) {
	ScreenSize screen = base.GetScreen();
	// ゲージ枠の描画
	DrawRoundRect(0.9f, 59.9f, 3.1f, 90.1f, 1, COLOR_BLACK);
	DrawRoundRect(1, 60, 3, 90, 1, COLOR_WHITEGRAY);

	// ゲージ内側の描画座標を計算する
	float drawLength = 87.4f - 60.2f;													// ゲージの長さを求める
	float drawPct = base.ClampNumF((float(_pressedJump) / (float)JUMP_LOCK_TIME),0,1);	// 長押し時間を0～1で求める
	if (drawPct > 0.96f)drawPct = 1;													// ある程度押していたらゲージをマックスまで伸ばす：ズレ防止
	float drawPos = base.ClampNumF(87 - (drawLength * drawPct), 60.2f, 89.8f);			// 求めた%を元にゲージの頂点描画座標を計算する

	DrawRoundRect(1.2f, drawPos, 2.8f, 89.8f, 1, COLOR_MINTGREEN);						// ゲージ内側を描画する
}

void UIManager::DrawStringCenter(float left, float top, float right, float bottom, std::string text, int fontType) {

	int drawPosX = base.TextDrawCenterPosX(left, right, text, base.GetFontData(fontType).handle);	// 左右中央を計算
	int drawPosY = base.TextDrawCenterPosY(top, bottom, base.GetFontData(fontType).size, text);	// 上下中央を計算
	// 左右上下中央に文字を描画
	DrawStringToHandle(drawPosX, drawPosY, text.c_str(), COLOR_BLACK, base.GetFontData(fontType).handle);
}

void UIManager::DrawString(float leftPct, float rightPct, float heightPct, std::string text, int font) {
	float drawLeftPos = base.ScreenDrawPosF(base.GetScreen().width, leftPct);	// 左端座標を計算
	float drawRightPos = base.ScreenDrawPosF(base.GetScreen().width, rightPct);	// 右端座標を計算

	// 右端の座標が左端の座標よりも小さかった場合は左端の座標を描画座標に設定
	// 右端の座標の方が大きかった場合は左右中央に描画するための座標を計算する
	int drawPosX = leftPct > rightPct ? (int)drawLeftPos : base.TextDrawCenterPosX(drawLeftPos, drawRightPos, text, font);
	int drawPosY = base.ScreenDrawPosI(base.GetScreen().height, heightPct);	// 描画座標Yを計算
	// 文字を描画
	DrawStringToHandle(drawPosX, drawPosY, text.c_str(), COLOR_BLACK, font);
	DrawStringToHandle(drawPosX, drawPosY, text.c_str(), COLOR_BLACK, font);
}

void UIManager::DrawImage(float leftPct, float topPct, ImageData image) {
	// 実装環境(WQHD)と比べてどのくらい画面サイズが違うのか調べる:同じ場合は1になる
	float widthPct = (float)base.GetScreen().width / 2560;
	float heightPct = (float)base.GetScreen().height / 1440;

	// 左上頂点座標を計算
	int x1 = base.ScreenDrawPosI(base.GetScreen().width, leftPct);
	int y1 = base.ScreenDrawPosI(base.GetScreen().height, topPct);

	// 右下頂点座標を計算
	int x2 = x1 + (int)((float)image.width * widthPct);
	int y2 = y1 + (int)((float)image.height * heightPct);

	// 計算した座標に合わせたサイズで画像を描画
	DrawExtendGraph(x1, y1, x2, y2, image.image, TRUE);
}

void UIManager::DrawRoundRect(float _leftPct, float _topPct, float _rightPct, float _bottomPct, float _radiusPct,int _color) {
	// 画面描画座標を計算
	float leftPos = base.ScreenDrawPosF(base.GetScreen().width, _leftPct);
	float rightPos = base.ScreenDrawPosF(base.GetScreen().width, _rightPct);
	float topPos = base.ScreenDrawPosF(base.GetScreen().height, _topPct);
	float bottomPos = base.ScreenDrawPosF(base.GetScreen().height, _bottomPct);
	float radius = base.ScreenDrawPosF(base.GetScreen().width, _radiusPct);

	DrawRoundRectAA(leftPos, topPos, rightPos, bottomPos, radius, radius, 64, _color, TRUE);
}

/*FadeManagerクラス---------------------------------------------------------------------------------------------------------*/

void FadeManager::DrawFadeController() {
	switch (fadeState)
	{
	case NONE:		// フェード処理をしない：即メソッドを抜ける
		isFading = false;
		return;
	case FADEOUT:	// 画面を暗転：処理開始時にフラグを立てる
		if (alphaValue == 255) fadeState = FADEWAIT;
		isFading = true;
		DrawFade(FADE_SPEED);
		break;
	case FADEIN:	// 画面を明転：処理終了時にフラグを折る
		if (alphaValue == 0) fadeState = NONE;
		DrawFade(-FADE_SPEED);
		break;

	case FADEWAIT:	// 指定時間待機：待機中にUIの切り替えを行う
		if (fadeStartCount == 0) {
			base.Initialization();
			fadeStartCount = GetNowCount();
		}
		if (fadeStartCount + FADE_WAIT_TIME <= GetNowCount()) {
			ChangeScene();
			fadeState = FADEIN;
			fadeStartCount = 0;
		}
		DrawFade(0);
		break;
	case NOTFADE:	// 画面の切り替え：変数の中身を変えるだけ
		ChangeScene();
		fadeState = NONE;
		break;
	}
}

void FadeManager::DrawFade(int fadeSpeed)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);	// 描画時のalpha値を指定の値に変更
	alphaValue = base.ClampNumI(alphaValue + fadeSpeed, 0, 255);	// alpha値が一定を超えないように増減させる
	DrawBox(0, 0, base.GetScreen().width, base.GetScreen().height, COLOR_BLACK, TRUE);	// 画面を覆うように黒い四角を描画：フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	// 他の描画に影響を与えないようにalpha値をリセットしておく
}

void FadeManager::DrawTextFade(std::string text, int font, int value) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaValue);
	alphaValue = base.ClampNumI(alphaValue + value, 0, 255);
	uiManager.DrawString(0, 100, 45, text, font);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FadeManager::ChangeScene() {
	uiManager.SetCurrentScreen(uiManager.GetNextScreen());	// 描画するUIを変更する

	// ボタンの座標を初期化
	buttonManager.SetButtonMovePos(buttonManager.START_BUTTON_POS);
	buttonManager.SetButtonPos(buttonManager.START_BUTTON_POS);
}

void FadeManager::ChangeUIState(SCREEN_TYPE screen, FADE_STATE fade) {
	uiManager.SetNextScreen(screen);
	fadeState = fade;
	base.SetIsGameStop(true);
}


/*描画内容をまとめたクラス---------------------------------------------------------------------------------------------------------*/

void TitleScene::Draw() {
	uiManager.DrawString(0, 100, 16, "ReversibleDash", base.GetFontData(EXTRALARGE).handle);	// タイトルの描画
	uiManager.DrawString(83, 0, 95, "Ver 0.7.00.00", base.GetFontData(MEDIUM).handle);	// バージョンの描画

	// 操作説明の描画
	uiManager.DrawImage(20, 95, uiManager.GetImageWASD());
	uiManager.DrawImage(32, 95, uiManager.GetImageSpace());
	uiManager.DrawImage(1.3f, 1.7f, uiManager.GetImageEscape());
	uiManager.DrawString(23.5f, 0, 95.7f, "Move", base.GetFontData(SMALL).handle);
	uiManager.DrawString(37.5f, 0, 95.7f, "Select", base.GetFontData(SMALL).handle);
	uiManager.DrawString(4, 0, 2, "Explanation", base.GetFontData(SMALL).handle);
}

void StageSelectScene::Draw() {
	uiManager.DrawString(0, 100, 16, "STAGESELECT", base.GetFontData(EXTRALARGE).handle);	// 見出しの描画

	// 操作説明の描画
	uiManager.DrawImage(20, 95, uiManager.GetImageWASD());
	uiManager.DrawImage(32, 95, uiManager.GetImageSpace());
	uiManager.DrawString(23.5f, 0, 95.7f, "Move", base.GetFontData(SMALL).handle);
	uiManager.DrawString(37.5f, 0, 95.7f, "Select", base.GetFontData(SMALL).handle);
}

void PauseScene::Draw(Player& _player) {
	// 背景枠の描画
	uiManager.DrawRoundRect(25, 25, 75, 75, 5,COLOR_WHITEGRAY);
	uiManager.DrawString(0, 100, 32, "PAUSE", base.GetFontData(EXTRALARGE).handle);	// 見出しの描画

	// 操作説明の描画
	uiManager.DrawImage(20, 95, uiManager.GetImageWASD());
	uiManager.DrawImage(32, 95, uiManager.GetImageSpace());
	uiManager.DrawString(23.5f, 0, 95.7f, "Move", base.GetFontData(SMALL).handle);
	uiManager.DrawString(37.5f, 0, 95.7f, "Select", base.GetFontData(SMALL).handle);

	uiManager.DrawProgressRateBar(_player, 50, 97, 96.5f);	// 進捗率バーの描画
}

void InGameScene::Draw(Player& _player) {
	uiManager.DrawString(1, 0, 95.7f, "SCORE : " + std::to_string(scoreManager.GetViewScore()), base.GetFontData(MEDIUM).handle);	// スコアの描画
	uiManager.DrawString(1, 0, 1, "STAGE" + std::to_string(base.GetStageNumber()), base.GetFontData(MEDIUM).handle);	// 現在遊んでいるステージがどこか描画
	uiManager.DrawStartCountDown();	// スタートカウントダウンの描画

	// 操作説明の描画
	uiManager.DrawImage(21, 95, uiManager.GetImageEscape());
	uiManager.DrawImage(32, 95, uiManager.GetImageSpace());
	uiManager.DrawString(23.5f, 0, 95.7f, "Pause", base.GetFontData(SMALL).handle);
	uiManager.DrawString(37.5, 0, 95.7f, "Jump", base.GetFontData(SMALL).handle);

	uiManager.DrawProgressRateBar(_player, 50, 97, 96.5f);	// 進捗率バーの描画
}

void GameOverScene::Draw() {
	// 背景枠の描画
	uiManager.DrawRoundRect(23, 18, 77, 82, 5, COLOR_WHITEGRAY);
	uiManager.DrawString(0, 100, 25, "GAMEOVER", base.GetFontData(EXTRALARGE).handle);	// 見出しの描画

	// スコアの描画
	uiManager.DrawString(27, 47, 43, "SCORE", base.GetFontData(LARGE).handle);
	uiManager.DrawString(27, 47, 51, std::to_string(scoreManager.GetScore()), base.GetFontData(LARGE).handle);

	// 操作説明の描画
	uiManager.DrawImage(20, 95, uiManager.GetImageWASD());
	uiManager.DrawImage(32, 95, uiManager.GetImageSpace());
	uiManager.DrawString(23.5f, 0, 95.7f, "Move", base.GetFontData(SMALL).handle);
	uiManager.DrawString(37.5f, 0, 95.7f, "Select", base.GetFontData(SMALL).handle);
}

void ClearScene::Draw() {
	// 背景枠の描画
	uiManager.DrawRoundRect(23, 18, 77, 82, 5, COLOR_WHITEGRAY);
	uiManager.DrawString(0, 100, 25, "STAGE CLEAR", base.GetFontData(EXTRALARGE).handle);	// 見出しの描画

	//スコアの描画
	uiManager.DrawString(27, 47, 43, "SCORE", base.GetFontData(LARGE).handle);
	uiManager.DrawString(27, 47, 51, std::to_string(scoreManager.GetScore()), base.GetFontData(LARGE).handle);

	// ハイスコアの描画
	uiManager.DrawString(53, 73, 43, "HIGHSCORE", base.GetFontData(LARGE).handle);
	uiManager.DrawString(53, 73, 51, std::to_string(scoreManager.GetHighScore(base.GetStageNumber())), base.GetFontData(LARGE).handle);

	// 操作説明の描画
	uiManager.DrawImage(20, 95, uiManager.GetImageWASD());
	uiManager.DrawImage(32, 95, uiManager.GetImageSpace());
	uiManager.DrawString(23.5f, 0, 95.7f, "Move", base.GetFontData(SMALL).handle);
	uiManager.DrawString(37.5f, 0, 95.7f, "Select", base.GetFontData(SMALL).handle);
}

void ExplanationScene::Draw() {
	ScreenSize  screen = base.GetScreen();	// 描画用に一時的に取得
	// ページの操作処理
	if (input.KeyDown(KEY_INPUT_LEFT) || input.KeyDown(KEY_INPUT_A)) currentPage = base.ClampNumI(--currentPage, 0, 2);
	if (input.KeyDown(KEY_INPUT_RIGHT) || input.KeyDown(KEY_INPUT_D)) currentPage = base.ClampNumI(++currentPage, 0, 2);
	uiManager.DrawString(0, 100, 5, "Exception", base.GetFontData(EXTRALARGE).handle);	// 見出し
	DrawBox(base.ScreenDrawPosI(screen.width, 5), base.ScreenDrawPosI(screen.height, 33), base.ScreenDrawPosI(screen.width, 95), base.ScreenDrawPosI(screen.height, 93), COLOR_WHITE, TRUE);

	// 選択してるページを強調表示する
	DrawBox(base.ScreenDrawPosI(screen.width, 5), base.ScreenDrawPosI(screen.height, 25),base.ScreenDrawPosI(screen.width, 35), base.ScreenDrawPosI(screen.height, 33),currentPage == 0 ? COLOR_WHITE : COLOR_LIGHTGRAY, TRUE);
	DrawBox(base.ScreenDrawPosI(screen.width, 35), base.ScreenDrawPosI(screen.height, 25),base.ScreenDrawPosI(screen.width, 65), base.ScreenDrawPosI(screen.height, 33),currentPage == 1 ? COLOR_WHITE : COLOR_LIGHTGRAY, TRUE);
	DrawBox(base.ScreenDrawPosI(screen.width, 65), base.ScreenDrawPosI(screen.height, 25),base.ScreenDrawPosI(screen.width, 95), base.ScreenDrawPosI(screen.height, 33),currentPage == 2 ? COLOR_WHITE : COLOR_LIGHTGRAY, TRUE);
	// 上のボックスの中にテキストを表示
	uiManager.DrawString(5, 35, 25, "Player", base.GetFontData(LARGE).handle);
	uiManager.DrawString(35, 65, 25, "Object", base.GetFontData(LARGE).handle);
	uiManager.DrawString(65, 95, 25, "Score", base.GetFontData(LARGE).handle);


	if (currentPage != 0) {
		// 左矢印
		DrawTriangleAA(base.ScreenDrawPosF(screen.width, 4), base.ScreenDrawPosF(screen.height, 26.5f),
			base.ScreenDrawPosF(screen.width, 4), base.ScreenDrawPosF(screen.height, 31.5f),
			base.ScreenDrawPosF(screen.width, 1), base.ScreenDrawPosF(screen.height, 29), COLOR_WHITE, TRUE);
	}
	if (currentPage != 2) {
		// 右矢印
		DrawTriangleAA(base.ScreenDrawPosF(screen.width, 96), base.ScreenDrawPosF(screen.height, 26.5f),
			base.ScreenDrawPosF(screen.width, 96), base.ScreenDrawPosF(screen.height, 31.5f),
			base.ScreenDrawPosF(screen.width, 99), base.ScreenDrawPosF(screen.height, 29), COLOR_WHITE, TRUE);
	}
	//表示しているページに応じて表示する説明を変更する
	switch (currentPage)
	{
	case 0:
		uiManager.DrawString(0, 100, 50, "ジャンプのしようをかく", base.GetFontData(LARGE).handle);
		uiManager.DrawImage(15, 40, uiManager.GetExplanations(0));
		uiManager.DrawImage(17.5f, 65, uiManager.GetExplanations(1));
		break;
	case 1:
		uiManager.DrawString(0, 100, 50, "くるま、くものしようをかく", base.GetFontData(LARGE).handle);
		uiManager.DrawImage(13, 44, uiManager.GetExplanations(2));
		uiManager.DrawImage(25.5f, 38, uiManager.GetExplanations(3));
		uiManager.DrawImage(68, 40, uiManager.GetExplanations(4));
		uiManager.DrawImage(35, 75, uiManager.GetExplanations(5));
		break;
	case 2:
		uiManager.DrawString(0, 100, 50, "スコアのしようをかく", base.GetFontData(LARGE).handle);
		uiManager.DrawImage(19, 38, uiManager.GetExplanations(6));
		uiManager.DrawImage(54, 38, uiManager.GetExplanations(7));
		break;
	}
	
	// 操作説明の描画
	uiManager.DrawImage(1.3f, 1.7f, uiManager.GetImageEscape());
	uiManager.DrawImage(20, 95, uiManager.GetImageWASD());
	uiManager.DrawString(4, 0, 2, "Title", base.GetFontData(SMALL).handle);
	uiManager.DrawString(23.5f, 0, 95.7f, "Move", base.GetFontData(SMALL).handle);
}