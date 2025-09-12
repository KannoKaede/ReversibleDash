#include "DxLib.h"
#include "main.h"

/// <summary> âÊñ ÇÃèÛë‘Ç…ëŒâûÇµÇΩUIÇï\é¶Ç∑ÇÈ </summary>
void ScreenSwithing()
{
	switch (screenType)
	{
	case TITLE:
		printfDx("TITLE\n");
		break;
	case STAGESELECT:
		printfDx("STAGESELECT\n");
		break;
	case INGAME:
		printfDx("INGAME\n");
		break;
	case PAUSE:
		printfDx("PAUSE\n");
		break;
	case GAMEOVER:
		printfDx("GAMEOVER\n");
		break;
	case STAGECLEAR:
		printfDx("STAGECLEAR\n");
		break;
	default:
		break;
	}
}