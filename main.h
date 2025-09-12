#pragma once

/// <summary> 画面の種類を定義する </summary>
enum SCREEN_TYPE
{
	TITLE,
	STAGESELECT,
	INGAME,
	PAUSE,
	GAMEOVER,
	STAGECLEAR
};
/// <summary> 現在の画面の状態 </summary>
__declspec(selectany) SCREEN_TYPE screenType;
/// <summary> ゲーム(exe)を終了するかのフラグ </summary>
__declspec(selectany) bool isGameQuit;
/// <summary> 画面の状態に対応したUIを表示する </summary>メモ：UIヘッダを作成して移動
void ScreenSwithing();