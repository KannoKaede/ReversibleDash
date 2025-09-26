#include"DxLib.h"
#include"InGame.h"
bool isGameStop;
int stageNumber;

void DrawStage(int stageNum) {
	DrawCone3D(VGet(30,70,0), VGet(30,0,0), 50, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
}