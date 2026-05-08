#pragma once
#include"../GameLib/game_lib.h"
#include <stdio.h>

#define STAGE_X 8
#define STAGE_Y 8

#define MapCenter chipSize/2 //マップの真ん中になる
#define MapDown chipSize      //マップの下、右になる

#define Mobsoze 64
class Map
{
public:
	Map();
	~Map();
	void Render();
	void Update();
	void Road();
	void Move();
	void Road2();
	void Road3();
	void Road4();
	void Road5();

	int map[STAGE_X][STAGE_Y] =
	{ 2,2,2,2,1,1,1,1,
	  2,1,2,1,1,1,1,1,
	  2,1,1,3,1,4,1,1,
	  3,1,1,1,2,1,1,1,
	  1,1,1,1,1,1,1,1,
	  1,4,1,1,1,2,1,1,
	  1,1,4,1,1,1,3,1,
	  1,1,1,2,1,1,3,1,
	};

	float posX[1][1] = {};
	float posY[1][1] = {};

	int prevX = -1;
	int prevY = -1;
	int phase = 0;
	bool moving = false;
	int mapX = (m.pos.x) / chipSize;				//playerがいるマス
	int mapY = (m.pos.y) / chipSize;				//playerがいるマス

	float top = mapY * chipSize;					//今いるブロックの上端
	float bottom = mapY * chipSize + chipSize;		//今いるブロックの下端
	float left = mapX * chipSize;					//今いるブロックの左端
	float right = mapX * chipSize + chipSize;		//今いるブロックの右端
	float senterX = mapX * chipSize + MapCenter;	//今いるブロックの真ん中
	float senterY = mapY * chipSize + MapCenter;	//今いるブロックの真ん中


	int downmapY = mapY + 1;						//一個下のブロック
	int upmapY = mapY - 1;							//一個上のブロック
	int rightmapX = mapX + 1;						//一個右のブロック
	int leftmapX = mapX - 1;						//一個左のブロック


	struct Mob
	{
		VECTOR2 pos{ 0,0 };
		int pivot = Mobsoze * 0.5f;
		int angle = 0;
		int dirY = 1; // 1=下, -1=上
		int dirX = 1; // 1=右, -1=左
		int speed = 1;
	};
	struct BlockData
	{

		int angle;
		int RotationCount = 0;
	};
	Mob m;
	const int chipSize = 100; // 1マスのサイズ
	Sprite* sprmap1;//草
	Sprite* sprmap2;//直線
	Sprite* sprmap3;//曲がる
	Sprite* sprmap4;//T字
	Sprite* sprmob;//動くやつ
	Sprite* sprfield;

	BlockData block[STAGE_Y][STAGE_X] = {};//ひとマスの情報

	float DegToRad(float degree)
	{
		const float PI = 3.1415926535f;
		return degree * PI / 180.0f;
	}

};