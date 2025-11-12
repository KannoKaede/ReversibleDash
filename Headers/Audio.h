#pragma once
#include "DxLib.h"

class AudioManager {
public:
	/// <summary> コンストラクタ </summary>
	AudioManager() :se(), bgm(), pastBgmType(BGM_MAX_NUM) {}

	// SEの種類を定義
	enum SeType {
		BUTTON_MOVE,		// ボタン移動
		BUTTON_BEEP,		// ボタン移動不可
		BUTTON_SELECT,		// ボタン選択
		JINGLE_CLEAR,		// クリアジングル
		JINGLE_GAMEOVER,	// ゲームオーバージングル
		SE_MAX_NUM			// SEの種類の最大数
	};

	// BGMの種類の定義
	enum BgmType {
		OUTGAME_BGM,		// インゲーム非描画時のBGM
		INGAME_BGM,			// インゲーム描画時のBGM
		BGM_MAX_NUM			// BGMの種類の最大数
	};

	/// <summary> コンストラクタでは設定できない音声データをロードする </summary>
	void SetUp();

	/// <summary> SEを再生する </summary>
	void PlaySE(SeType _seType)const;

	/// <summary> BGMを再生する </summary>
	void PlayBGM(BgmType _bgmType);

	/// <summary> 再生しているBGMを停止する </summary>
	void StopBGM();

	/// <summary> BGMの再生停止を管理 </summary>
	void PlayBGMControl();
private:
	int			se[SE_MAX_NUM];		// SEデータ
	int			bgm[BGM_MAX_NUM];	// BGMデータ
	BgmType		pastBgmType;		// 再生していたBGM
};

extern AudioManager audioManager;
