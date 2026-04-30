#include"Mapchip.h"
Mapchip::Mapchip()
{


	sprmap1	= sprite_load(L"./Data/Images/mapchip1.png");
	sprmap2	= sprite_load(L"./Data/Images/mapchip2.png");
	sprmap3	= sprite_load(L"./Data/Images/mapchip3.png");
	sprmap4	= sprite_load(L"./Data/Images/mapchip4.png");
	sprmob= sprite_load(L"./Data/Images/mob.png");
	sprfield= sprite_load(L"./Data/Images/field.png");
}
Mapchip::~Mapchip()
{
	
}
void Mapchip::Update()
{
	Move();
}
void Mapchip::Road()
{
	for (int i = 0;i < STAGE_Y;i++) {
		for (int j = 0;j < STAGE_X;j++) {
			float posX = j * chipSize + 300;
			float posY = i * chipSize + 100;
			switch (map[i][j]) {
			case 1:

				break;
			}
		}
	}
}
void Mapchip::Move()
{

	int mapX = (m.pos.x - 300) / chipSize;//playerがいるマス
	int mapY = (m.pos.y - 100) / chipSize;//playerがいるマス

	if (mapX < 0 || mapX >= STAGE_X ||
		mapY < 0 || mapY >= STAGE_Y)
		return;

	//直線の場合
	if (map[mapY][mapX] == 2 || m.dirY != 0)
	{
		// 上端探す
		int topY = mapY;
		while (topY - 1 >= 0 && (map[topY - 1][mapX] == 2 || map[topY - 1][mapX] == 3))
		{
			topY--;
		}

		// 下端探す
		int bottomY = mapY;
		while (bottomY + 1 < STAGE_Y && (map[bottomY + 1][mapX] == 2 || map[bottomY + 1][mapX] == 3))
		{
			bottomY++;
		}

		float top = topY * chipSize + 100;
		float bottom = bottomY * chipSize + 100 + chipSize;

		// 移動
		m.pos.y += m.dirY * m.speed;
		// 上端
		if (m.pos.y <= top)
		{
			m.pos.y = top;
			m.dirY = 1;
			angle[mapY][mapX] += 90;
		}

		// 下端
		if (m.pos.y >= bottom)
		{
			m.pos.y = bottom;
			m.dirY = -1;
			angle[mapY][mapX] += 90;
		}
		debug::setString("y=%.1f dir=%d top=%.1f bottom=%.1f",
			m.pos.y, m.dirY, top, bottom);

	}

		//if (map[mapY][mapX] == 2 || m.dirY != 0)
		//{
		//	// 上端探す
		//	int topY = mapY;
		//	while (topY - 1 >= 0 && map[topY - 1][mapX] == 2)
		//	{
		//		topY--;
		//	}

		//	// 下端探す
		//	int bottomY = mapY;
		//	while (bottomY + 1 < STAGE_Y && map[bottomY + 1][mapX] == 2)
		//	{
		//		bottomY++;
		//	}

		//	float top = topY * chipSize + 100;
		//	float bottom = bottomY * chipSize + 100 + chipSize;

		//	// 移動
		//	m.pos.y += m.dirY * m.speed;
		//	// 上端
		//	if (m.pos.y <= top)
		//	{
		//		m.pos.y = top;
		//		m.dirY = 1;
		//	}

		//	// 下端
		//	if (m.pos.y >= bottom)
		//	{
		//		m.pos.y = bottom;
		//		m.dirY = -1;
		//	}
		
	
}
void Mapchip::Render()
{
	sprite_render(sprfield,
		300, 100,
		1, 1,
		0, 0,
		640, 640,
		0, 0,
		0,
		1, 1, 1
	);
	for (int i = 0;i < STAGE_Y;i++) {
		for (int j = 0;j < STAGE_X;j++) {
			float posX = j * chipSize+300;
			float posY = i * chipSize+100;
			switch (map[i][j]) {
				//通後不可
			case 1:
				sprite_render(sprmap1,
					posX, posY,
					1, 1,
					0, 0,
					chipSize, chipSize,
					0, 0,
					DegToRad(angle[i][j]),
					1, 1, 1
				);
				break;
				//直線
			case 2:
				sprite_render(sprmap2,
					posX, posY,
					1, 1,
					0, 0,
					chipSize, chipSize,
					0, 0,
					DegToRad(angle[i][j]),
					1, 1, 1
				);
				break;
				//曲線
			case 3:
				sprite_render(sprmap3,
					posX, posY,
					1, 1,
					0, 0,
					chipSize, chipSize,
					0, 0,
					DegToRad(angle[i][j]),
					1, 1, 1
				);
				break;
				//T字
			case 4:
				sprite_render(sprmap4,
					posX, posY,
					1, 1,
					0, 0,
					chipSize, chipSize,
					0, 0,
					DegToRad(angle[i][j]),
					1, 1, 1
				);
				break;
			}
		}
	}
	sprite_render(sprmob,
		m.pos.x, m.pos.y,
		1, 1,
		0, 0,
		64, 64,
		0, 0,
		0,
		1, 1, 1
	);

	debug::display(1,0,1,2,2); // ← 最後に描く
}