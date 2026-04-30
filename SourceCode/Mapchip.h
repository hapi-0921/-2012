#pragma once
#include"../GameLib/game_lib.h"
#define STAGE_X 8
#define STAGE_Y 8
class Mapchip
{
public:
	Mapchip();
	~Mapchip();
	void Render();
	void Update();
	

	int map[8][8]=   { 1,1,1,1,2,1,1,1,
					   1,2,1,1,1,1,1,1,
					   1,1,3,1,1,4,1,1,
					   1,1,1,2,1,1,1,1,
					   1,1,1,1,3,1,1,1,
					   1,4,1,1,1,2,1,1,
					   1,1,4,1,1,1,3,1,
					   1,1,1,2,1,1,3,1,
	};

	float posX[1][1]={};
	float posY[1][1] = {};
	const int chipSize = 100; // 1マスのサイズ
	Sprite* sprmap1;//草
	Sprite* sprmap2;//直線
	Sprite* sprmap3;//曲がる
	Sprite* sprmap4;//T字

};