#pragma once
#include"../GameLib/game_lib.h"
#define STAGE_X 10
#define STAGE_Y 10
class Mapchip
{
	Mapchip();
	~Mapchip();
	void Render();
	void Update();
	

	int map[10][10];

	float posX[1][1];
	float posY[1][1];
	const int chipSize = 64; // 1マスのサイズ
	Sprite* sprmap1;//草
	Sprite* sprmap2;//直線
	Sprite* sprmap3;//曲がる
	Sprite* sprmap4;//T字

};