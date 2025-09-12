#pragma once

enum SCREEN_TYPE
{
	TITLE,
	STAGESELECT,
	INGAME,
	PAUSE,
	GAMEOVER,
	STAGECLEAR
};
SCREEN_TYPE screenType = TITLE;

void Sgoi() {
	printfDx("sugoi");
}