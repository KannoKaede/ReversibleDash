#include "Input.h"

Input input;

void Input::CheckAllKey() {
	for (int i = 0; i < KEY_NUM; i++) {
		pastKey[i] = currentKey[i];
	}
	GetHitKeyStateAll(currentKey);
}

bool Input::KeyDown(const int key) {
	// キーを押し込んだ瞬間を検出
	return pastKey[key] == 0 && currentKey[key] == 1;
}
bool Input::KeyPushing(const int key) {
	// キーを押し続けている状態を検知
	return pastKey[key] == 1 && currentKey[key] == 1;
}
bool Input::KeyUp(const int key) {
	// キーを離した瞬間を検知
	return pastKey[key] == 1 && currentKey[key] == 0;
}

