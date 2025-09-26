#pragma once
#include "main.h"
#ifndef INCLUDED_InGame_h
#define INCLUDED_InGame_h

extern bool isGameStop;
extern int stageNumber;     // 現在のステージ番号
const int MAX_STAGE_NUM = 7;    //ステージの最大数：配列で使用するためステージ数＋１
const float goalPosition[MAX_STAGE_NUM] = { 0,500,100,100,100,100,100 };
#endif