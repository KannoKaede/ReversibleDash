#include "Audio.h"

int se[SE_MAX_NUM];		// SEデータを格納する配列
int bgm[BGM_MAX_NUM];	// BGMデータを格納する配列
int previousBGM;		// 前回再生したBGMのハンドルを格納する変数

void AudioSetUp() {
	// 音源の読み込み
	se[BUTTON_MOVE] = LoadSoundMem("Resource/Audios/SE_ButtonMove.mp3");
	se[BUTTON_BEEP] = LoadSoundMem("Resource/Audios/SE_ButtonBeep.mp3");
	se[BUTTON_SELECT] = LoadSoundMem("Resource/Audios/SE_ButtonSelect.mp3");
	bgm[TITLE_BGM] = LoadSoundMem("Resource/Audios/BGM_Title.mp3");
	bgm[INGAME_BGM] = LoadSoundMem("Resource/Audios/BGM_InGame.mp3");
	// 音量設定
	ChangeVolumeSoundMem(30, bgm[TITLE_BGM]);
	ChangeVolumeSoundMem(30, bgm[INGAME_BGM]);
}

void PlaySE(int seHandle) {
	PlaySoundMem(seHandle, DX_PLAYTYPE_BACK);
}

void PlayBGM(int bgmHandle) {
	// 同じBGMを何回も再生しないようにブロックする
	if (previousBGM != bgmHandle) {
		StopSoundMem(previousBGM);	// 前回のBGMを停止：停止しないと重なって再生される
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
		previousBGM = bgmHandle;
	}
}
