#pragma once
#include"../GameLib/game_lib.h"
#include <stdio.h>

#define STAGE_X 8
#define STAGE_Y 8

#define MapUCenter chipSize/2 //足し算するとマップの真ん中になる
#define MapDown chipSize      //足し算するとマップの下、右になる

class Mapchip
{
public:
	Mapchip();
	~Mapchip();
	void Render();
	void Update();
	void Road();
	void Move();

	int map[8][8]=   { 1,1,1,1,2,1,1,1,
					   1,2,1,1,2,1,1,1,
					   1,1,3,1,2,4,1,1,
					   1,1,1,2,2,1,1,1,
					   1,1,1,1,3,1,1,1,
					   1,4,1,1,1,2,1,1,
					   1,1,4,1,1,1,3,1,
					   1,1,1,2,1,1,3,1,
	};

	float posX[1][1]={};
	float posY[1][1] = {};
	int angle [8][8] = {};
	

	int prevX = -1;
	int prevY = -1;
	float moveTop;
	float moveBottom;
	bool moving = false;
	struct Mob
	{
		VECTOR2 pos{715,100};
		int angle = 0 ;
		int dirY = 1; // 1=下, -1=上
		int speed = 1;
	};
	Mob m;
	const int chipSize = 100; // 1マスのサイズ
	Sprite* sprmap1;//草
	Sprite* sprmap2;//直線
	Sprite* sprmap3;//曲がる
	Sprite* sprmap4;//T字
	Sprite* sprmob;//動くやつ
	Sprite* sprfield;
	float DegToRad(float degree)
	{
		const float PI = 3.1415926535f;
		return degree * PI / 180.0f;
	}

};