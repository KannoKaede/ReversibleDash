#pragma once
#include "DxLib.h"
#ifndef Input_h
#define INput_h

const int KEY_NUM = 256;	// 配列の要素数
extern char keyBuf[KEY_NUM];	// 現在のキー入力状態
extern char keyBuf_old[KEY_NUM];	// 1フレーム前のキー入力状態

/// <summary> キーの入力状態を調べるメソッド </summary>
void CheckAllKeyState();

/// <summary> 指定のキーが押された瞬間だけtrueを返すメソッド </summary>
/// <param name="keyCode"> 入力状態を調べたいキー </param>
bool CheckHitKeyDown(int keyCode);

/// <summary> 指定のキーが離された瞬間だけtrueを返すメソッド </summary>
/// <param name="keyCode"> 入力状態を調べたいキー </param>
bool CheckHitKeyUp(int keyCode);
#endif
