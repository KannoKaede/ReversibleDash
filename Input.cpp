#include "Input.h"

char keyBuf[KEY_NUM];	// 現在のキー入力状態
char keyBuf_old[KEY_NUM];	// 1フレーム前のキー入力状態

void CheckAllKeyState() {
	for (int i = 0; i < KEY_NUM; i++) {
		keyBuf_old[i] = keyBuf[i];
	}
	GetHitKeyStateAll(keyBuf);
}

bool CheckHitKeyDown(const int keyCode) {
	return keyBuf_old[keyCode] == 0 && keyBuf[keyCode] == 1;
}
bool CheckHitKeyUp(const int keyCode) {
	return keyBuf_old[keyCode] == 1 && keyBuf[keyCode] == 0;
}
