#include "Input.h"

char keyBuf[KEY_NUM];	// 現在のキー入力状態
char keyBuf_old[KEY_NUM];	// 1フレーム前のキー入力状態

void CheckAllKeyState() {
	// 1フレーム前のキー入力状態を保存
	for (int i = 0; i < KEY_NUM; i++) {
		keyBuf_old[i] = keyBuf[i];
	}
	GetHitKeyStateAll(keyBuf);	// 現在のキー入力状態を取得
}

bool CheckHitKeyDown(const int keyCode) {
	// キーを押し込んだ瞬間を検出
	return keyBuf_old[keyCode] == 0 && keyBuf[keyCode] == 1;
}
bool CheckHitKeyUp(const int keyCode) {
	// キーを離した瞬間を検出
	return keyBuf_old[keyCode] == 1 && keyBuf[keyCode] == 0;
}
