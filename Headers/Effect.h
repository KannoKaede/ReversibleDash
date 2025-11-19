#pragma once
#include "DxLib.h"

class Effect {
public:
	Effect() {}
	void SetUp();
	void PlayEffect();
	void Update(VECTOR _position);
private:
	int playingEffectHandle;
	int effectHandle;
};
extern Effect effect;