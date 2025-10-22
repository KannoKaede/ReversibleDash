#include "Audio.h"

int buttonMoveSE;
int buttonBeepSE;
int buttonSelectSE;
int bgm;
int bgm1;
int previousBGM;

void AudioSetUp() {
	buttonMoveSE = LoadSoundMem("Resource/Audios/SE_ButtonMove.mp3");
	buttonBeepSE = LoadSoundMem("Resource/Audios/SE_ButtonBeep.mp3");
	buttonSelectSE = LoadSoundMem("Resource/Audios/SE_ButtonSelect.mp3");
	bgm = LoadSoundMem("Resource/Audios/BGM_Title.mp3");
	bgm1 = LoadSoundMem("Resource/Audios/BGM_InGame.mp3");
	ChangeVolumeSoundMem(30, bgm);
	ChangeVolumeSoundMem(30, bgm1);
}

void PlaySE(int seHandle) {
	PlaySoundMem(seHandle, DX_PLAYTYPE_BACK);
}
void PlayBGM(int bgmHandle) {
	if (previousBGM != bgmHandle) {
		StopSoundMem(previousBGM);
		PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
		previousBGM = bgmHandle;
	}
}

void PlayJINGLE(int jingleHandle) {
	StopSoundMem(previousBGM);
	PlaySoundMem(jingleHandle, DX_PLAYTYPE_BACK);
}