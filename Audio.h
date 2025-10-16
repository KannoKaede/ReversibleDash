#pragma once
#include "Main.h"
#ifndef INCLUDED_Audio_h
#define INCLUDED_Audio_h
extern int buttonMoveSE;
extern int buttonBeepSE;
extern int buttonSelectSE;
extern int bgm;
extern int bgm1;
extern int previousBGM;
void AudioSetUp();

void PlaySE(int seHandle);

void PlayBGM(int bgmHandle);
#endif