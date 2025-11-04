#pragma once
#include "DxLib.h"

enum SeType {	// SEの種類を定義
	BUTTON_MOVE,	// ボタン移動音
	BUTTON_BEEP,	// ボタン移動不可音
	BUTTON_SELECT,	// ボタン決定音
	SE_MAX_NUM		// SEの種類数
};

extern int se[SE_MAX_NUM];	// SEデータを格納する配列

enum BgmType {	// BGMの種類を定義
	TITLE_BGM,	// タイトルBGM
	INGAME_BGM,	// インゲームBGM
	BGM_MAX_NUM	// BGMの種類数
};

extern int bgm[BGM_MAX_NUM];	// BGMデータを格納する配列

/// <summary> 音源の読み込み、音量設定を行うメソッド </summary>
void AudioSetUp();

/// <summary> SEを再生するメソッド </summary>
void PlaySE(int seHandle);

extern int previousBGM;	// 前回再生したBGMのハンドルを格納する変数

/// <summary> BGMを再生するメソッド </summary>
void PlayBGM(int bgmHandle);
