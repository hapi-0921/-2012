#include"Mapchip.h"
void Map::SetRoad()
{
	// 0行目
	block[0][1].angle = 90;
	block[0][2].angle = 180;
	block[0][3].angle = 0;
	block[0][4].angle = 90;
	block[0][5].angle = 0;
	block[0][6].angle = 0;
	block[0][7].angle = 90;
	block[0][8].angle = 0;
	block[0][9].angle = 90;
	block[0][10].angle = 180;
	block[0][11].angle = 0;
	//1行目
	block[1][0].angle = 0;
	block[1][1].angle = 0;
	block[1][2].angle = 90;
	block[1][3].angle = 0;
	block[2][3].angle = 270;
	block[2][2].angle = 0;


	block[1][4].angle = 90;
	block[1][5].angle = 0;
	block[1][6].angle = 180;
	block[1][7].angle = 0;
	block[1][8].angle = 0;
	block[1][9].angle = 0;
	block[1][10].angle = 270;
	block[1][11].angle = 0;
	//2行目
	block[2][0].angle = 90;
	block[2][1].angle = 90;
	block[2][2].angle = 270;
	block[2][3].angle = 180;
	block[2][4].angle = 0;
	block[2][5].angle = 0;
	block[2][6].angle = 0;
	block[2][7].angle = 90;
	block[2][8].angle = 90;
	block[2][9].angle = 0;
	block[2][10].angle = 0;
	block[2][11].angle = 0;

	//3行目

	block[3][0].angle = 0;
	block[3][1].angle = 0;
	block[3][2].angle = 180;
	block[3][3].angle = 0;
	block[3][4].angle = 90;
	block[3][5].angle = 0;
	block[3][6].angle = 90;
	block[3][7].angle = 90;
	block[3][8].angle = 0;
	block[3][9].angle = 270;
	block[3][10].angle = 90;
	block[3][11].angle = 90;
	//4行目
	block[4][0].angle = 0;
	block[4][1].angle = 270;
	block[4][2].angle = 0;
	block[4][3].angle = 0;
	block[4][4].angle = 90;
	block[4][5].angle = 0;
	block[4][6].angle = 0;
	block[4][7].angle = 90;
	block[4][8].angle = 90;
	block[4][9].angle = 180;
	block[4][10].angle = 0;
	block[4][11].angle = 0;
	//5行目
	block[5][0].angle = 90;
	block[5][1].angle = 90;
	block[5][2].angle = 270;
	block[5][3].angle = 0;
	block[5][4].angle = 0;
	block[5][5].angle = 180;
	block[5][6].angle = 0;
	block[5][7].angle = 0;
	block[5][8].angle = 0;
	block[5][9].angle = 0;
	block[5][10].angle = 90;
	block[5][11].angle = 90;
	//6行目
	block[6][0].angle = 180;
	block[6][1].angle = 0;
	block[6][2].angle = 90;
	block[6][3].angle = 0;
	block[6][4].angle = 0;
	block[6][5].angle = 0;
	block[6][6].angle = 0;
	block[6][7].angle = 90;
	block[6][8].angle = 90;
	block[6][9].angle = 180;
	block[6][10].angle = 00;
	block[6][11].angle = 0;


	block[0][0].notmove = true;
	block[2][9].notmove = true;
	block[5][3].notmove = true;
	block[0][1].notmove = true;
	block[4][3].notmove = true;
	block[1][9].notmove = true;
	block[6][10].notmove = true;

	block[3][0].stop = 2;
	block[3][3].stop = 3;
	block[6][4].stop = 2;
	block[4][10].stop = 3;
	block[0][8].stop = 2;
	block[0][6].stop = 3;
	block[1][5].stop = 2;
	block[2][4].stop = 3;
	block[3][8].stop = 2;
	block[5][10].stop = 3;
}

void Map::Setvariable()
{
	
	m = Mob{};
	c = Car{};
	n = Nabi{};
	for (int y = 0; y < STAGE_Y; y++)
	{
		for (int x = 0; x < STAGE_X; x++)
		{
			block[y][x] = BlockData{};
		}
	}
	goal = false;
	gametimer = 0;

	DangerX = 0;
	DangerY = 0;
	Dangerangle = 0;

	topStart = -1;
	bottomStart = -1;
	leftStart = -1;
	rightStart = -1;

	scale = tutorial ? 3 : 2;
	chipSize = tutorial ? 192 : 128;
}
