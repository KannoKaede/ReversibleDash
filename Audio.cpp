#include "Audio.h"

int buttonMoveSE;
int buttonBeepSE;
int buttonSelectSE;
int bgm;
int bgm1;
int previousBGM;

void AudioSetUp() {
	buttonMoveSE = LoadSoundMem("Resource/カーソル移動8.mp3");
	buttonBeepSE = LoadSoundMem("Resource/ビープ音1.mp3");
	buttonSelectSE = LoadSoundMem("Resource/決定ボタンを押す23.mp3");
	bgm = LoadSoundMem("Resource/Bgm.mp3");
	bgm1 = LoadSoundMem("Resource/maou_14_shining_star.mp3");
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