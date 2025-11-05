#include "Audio.h"

AudioManager audioManager;

void AudioManager::SetUp() {
	// 音源の読み込み
	se[BUTTON_MOVE] = LoadSoundMem("Resource/Audios/SE_ButtonMove.mp3");
	se[BUTTON_BEEP] = LoadSoundMem("Resource/Audios/SE_ButtonBeep.mp3");
	se[BUTTON_SELECT] = LoadSoundMem("Resource/Audios/SE_ButtonSelect.mp3");
	bgm[OUTGAME_BGM] = LoadSoundMem("Resource/Audios/BGM_Title.mp3");
	bgm[INGAME_BGM] = LoadSoundMem("Resource/Audios/BGM_InGame.mp3");
	// 音量設定
	ChangeVolumeSoundMem(30, bgm[OUTGAME_BGM]);
	ChangeVolumeSoundMem(30, bgm[INGAME_BGM]);
}

void AudioManager::PlaySE(SeType seHandle) {
	PlaySoundMem(se[seHandle], DX_PLAYTYPE_BACK);
}

void AudioManager::PlayBGM(BgmType bgmType) {
	// 同じBGMを何回も再生しないようにブロックする
	if (pastBgmtype != bgmType) {
		StopSoundMem(bgm[pastBgmtype]);	// 前回のBGMを停止
		PlaySoundMem(bgm[bgmType], DX_PLAYTYPE_LOOP);
		pastBgmtype = bgmType;
	}
}
