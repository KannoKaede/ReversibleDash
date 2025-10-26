#include"DxLib.h"
#include"InGame.h"
#include "Player.h"
#include"Score.h"
#include "UI.h"
#include <Math.h>
#include <cmath>
bool isGameStop;	// ゲームが止まっているか
int stageNumber;	// ステージ番号
MAPDATA mapDataArray[MAX_STAGE_NUM][2][50] = {
   {{} ,{}},	// ステージ0は無いので何もない
   //{	// ステージ1
   //	{1,43,9,1,10,1,5,1,10,1},
   //	{12,1,5,1,5,1,10,1,5,1,5,32,10,1}
   //},
   {	// ステージ1
	   {{OBJECTTYPE::NONE,1},{OBJECTTYPE::SMALL_CAR,43},{OBJECTTYPE::NONE,9},{OBJECTTYPE::SMALL_CAR,1},{OBJECTTYPE::NONE,10},{OBJECTTYPE::SMALL_CAR,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::SMALL_CAR,1},{OBJECTTYPE::NONE,10},{OBJECTTYPE::LARGE_CAR,1}},
	   {{OBJECTTYPE::NONE,12},{OBJECTTYPE::SMALL_CAR,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::SMALL_CAR,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::SMALL_CAR,1},{OBJECTTYPE::NONE,10},{OBJECTTYPE::SMALL_CAR,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::SMALL_CAR,1},{OBJECTTYPE::NONE,5},{OBJECTTYPE::LARGE_CAR,1},{OBJECTTYPE::SMALL_CAR,31},{OBJECTTYPE::NONE,10},{OBJECTTYPE::LARGE_CAR,1}}
   },
   {// ステージ2
	   {},
	   {}
   },
   {// ステージ3
	   {},
	   {}
   },
   {// ステージ4
	   {},
	   {}
   },
   {// ステージ5
	   {},
	   {}
   },
   {// ステージ6
	   {},
	   {}
   }
};



float drawConePosX;
void DrawStage(int stageNum, Player player) {
	OBJECT_DATA objectData = { VGet(600,TOP_GROUND,0),SMALL_CAR_RADIUS * 54,-SMALL_CAR_HEIGHT };
	OBJECT_DATA groundData = { VGet(-360, BOTTOM_GROUND, 0), 10000, -50 };
	VECTOR topLeftFront = VGet(objectData.position.x - objectData.radius, objectData.position.y + objectData.height, objectData.position.z - objectData.radius);
	VECTOR topRightFront = VGet(objectData.position.x + objectData.radius, objectData.position.y + objectData.height, objectData.position.z - objectData.radius);
	VECTOR topLeftBack = VGet(objectData.position.x - objectData.radius, objectData.position.y + objectData.height, objectData.position.z + objectData.radius);
	VECTOR topRightBack = VGet(objectData.position.x + objectData.radius, objectData.position.y + objectData.height, objectData.position.z + objectData.radius);
	VECTOR bottomLeftFront = VGet(objectData.position.x - objectData.radius, objectData.position.y, objectData.position.z - objectData.radius);
	VECTOR bottomRightFront = VGet(objectData.position.x + objectData.radius, objectData.position.y, objectData.position.z - objectData.radius);
	VECTOR bottomLeftBack = VGet(objectData.position.x - objectData.radius, objectData.position.y, objectData.position.z + objectData.radius);
	VECTOR bottomRightBack = VGet(objectData.position.x + objectData.radius, objectData.position.y, objectData.position.z + objectData.radius);
	DrawLine3D(topLeftFront, topRightFront, GetColor(0, 0, 0));
	DrawLine3D(topRightFront, topRightBack, GetColor(0, 0, 0));
	DrawLine3D(topRightBack, topLeftBack, GetColor(0, 0, 0));
	DrawLine3D(topLeftBack, topLeftFront, GetColor(0, 0, 0));
	DrawLine3D(bottomLeftFront, bottomRightFront, GetColor(0, 0, 0));
	DrawLine3D(bottomRightFront, bottomRightBack, GetColor(0, 0, 0));
	DrawLine3D(bottomRightBack, bottomLeftBack, GetColor(0, 0, 0));
	DrawLine3D(bottomLeftBack, bottomLeftFront, GetColor(0, 0, 0));
	DrawLine3D(topLeftFront, bottomLeftFront, GetColor(0, 0, 0));
	DrawLine3D(topRightFront, bottomRightFront, GetColor(0, 0, 0));
	DrawLine3D(topRightBack, bottomRightBack, GetColor(0, 0, 0));
	DrawLine3D(topLeftBack, bottomLeftBack, GetColor(0, 0, 0));
	IsCollision(player, objectData, true);
	IsCollision(player, groundData, true);
}

void IsCollision(Player player, OBJECT_DATA obj, bool isTest) {
	VECTOR playerPos = player.GetPosition();
	float playerHeight = isBottomGround ? PLAYER_HEIGHT : -PLAYER_HEIGHT;
	if (playerPos.x + PLAYER_RADIUS > obj.position.x - obj.radius && playerPos.x - PLAYER_RADIUS < obj.position.x + obj.radius)return;
	
}
