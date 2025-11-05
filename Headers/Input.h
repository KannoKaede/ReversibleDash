#pragma once
#include "DxLib.h"

const int KEY_NUM = 256;	// 配列の要素数

// キー入力を検知するクラス
class Input {
public:
	/// <summary> コンストラクタ </summary>
	Input():currentKey(),pastKey() {}
	/// <summary> 全てのキーの入力状態を保存するメソッド </summary>
	void CheckAllKey();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool KeyDown(const int key);
	bool KeyPushing(const int key);
	bool KeyUp(const int key);
private:
	char currentKey[KEY_NUM];
	char pastKey[KEY_NUM];
};

extern Input input;