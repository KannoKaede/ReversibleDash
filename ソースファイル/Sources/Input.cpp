#include "Input.h"

Input input;

void Input::CheckAllKey() {
	for (int i = 0; i < KEY_NUM; i++) {
		pastKey[i] = currentKey[i];
	}
	GetHitKeyStateAll(currentKey);
}

bool Input::KeyDown(int _keyName)const {
	// キーを押し込んだ瞬間を検出
	return pastKey[_keyName] == 0 && currentKey[_keyName] == 1;
}
bool Input::KeyPushing(int _keyName)const {
	// キーを押し続けている状態を検知
	return pastKey[_keyName] == 1 && currentKey[_keyName] == 1;
}
bool Input::KeyUp(int _keyName)const {
	// キーを離した瞬間を検知
	return pastKey[_keyName] == 1 && currentKey[_keyName] == 0;
}

