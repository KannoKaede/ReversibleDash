#include "Audio.h"
#include "UI.h"
#include "Input.h"

AudioManager audioManager;

void AudioManager::SetUp() {
	// 音源の読み込み
	se[BUTTON_MOVE] = LoadSoundMem("Resource/Audios/SE_ButtonMove.mp3");
	se[BUTTON_BEEP] = LoadSoundMem("Resource/Audios/SE_ButtonBeep.mp3");
	se[BUTTON_SELECT] = LoadSoundMem("Resource/Audios/SE_ButtonSelect.mp3");
	se[JINGLE_CLEAR] = LoadSoundMem("Resource/Audios/JINGLE_Clear.mp3");
	se[JINGLE_GAMEOVER] = LoadSoundMem("Resource/Audios/JINGLE_GameOver.mp3");
	bgm[OUTGAME_BGM] = LoadSoundMem("Resource/Audios/BGM_Title.mp3");
	bgm[INGAME_BGM] = LoadSoundMem("Resource/Audios/BGM_InGame.mp3");
	// 音量設定
	ChangeVolumeSoundMem(50, bgm[OUTGAME_BGM]);
	ChangeVolumeSoundMem(50, bgm[INGAME_BGM]);
	ChangeVolumeSoundMem(50, se[JINGLE_CLEAR]);
}

void AudioManager::PlaySE(SeType seHandle)const {
	PlaySoundMem(se[seHandle], DX_PLAYTYPE_BACK);
}

void AudioManager::PlayBGM(BgmType bgmType) {
	// 同じBGMを何回も再生しないようにブロックする
	if (pastBgmType != bgmType) {
		StopSoundMem(bgm[pastBgmType]);	// 前回のBGMを停止
		PlaySoundMem(bgm[bgmType], DX_PLAYTYPE_LOOP);
		pastBgmType = bgmType;
	}
}

void AudioManager::StopBGM() {
	StopSoundMem(bgm[pastBgmType]);
	pastBgmType = BGM_MAX_NUM;	// 使用していないBGMナンバーに初期化
}

void AudioManager::PlayBGMControl(){
	if (!fadeManager.GetIsFading()) {
		if (uiManager.CheckScreen(TITLE)||uiManager.CheckScreen(STAGESELECT) || uiManager.CheckScreen(EXPLANATION)) {
			PlayBGM(OUTGAME_BGM);
		}
		// スタートカウントダウンが終了したタイミングで再生
		else if (uiManager.CheckScreen(INGAME) && !uiManager.GetIsStartCountDown()) {
			PlayBGM(INGAME_BGM);
		}
		// 上記シーン以外ならBGMを停止
		else {
			StopBGM();
		}
	}
	else {	// フェード中もBGMを停止
		StopBGM();
	}
}
