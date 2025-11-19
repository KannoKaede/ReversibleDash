#include "Effect.h"
#include <EffekseerForDXLib.h>

Effect effect;

void Effect::SetUp() {
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	//Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	effectHandle = LoadEffekseerEffect("Resource/wind.efk", 100);
}

void Effect::PlayEffect() {
	PlayEffekseer3DEffect(effectHandle);
}

void Effect::Update(VECTOR _position) {
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, _position.x, _position.y, _position.z);
	UpdateEffekseer3D();
	DrawEffekseer3D();
}