#pragma once
#include "DxLib.h"

// キー入力を検知するクラス
class Input {
public:
	/// <summary> コンストラクタ </summary>
	Input() :currentKey(), pastKey() {}

	/// <summary> 全てのキーの入力状態を保存するメソッド </summary>
	void CheckAllKey();

	/// <summary> 指定したキーを押し込んだ瞬間を検知 </summary>
	bool KeyDown(int _keyName)const;
	/// <summary> 指定したキーが押されているかを検知 </summary>
	bool KeyPushing(int _keyName)const;
	/// <summary> 指定したキーを離した瞬間を検知 </summary>
	bool KeyUp(int _keyName)const;
private:
	static constexpr int	KEY_NUM = 256;			// 配列の要素数(DxLibのキーコード範囲)
	char					currentKey[KEY_NUM];	// 現在押しているキー
	char					pastKey[KEY_NUM];		// 1フレーム前に押していたキー
};

extern Input input;