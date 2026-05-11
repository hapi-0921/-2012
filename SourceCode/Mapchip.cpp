#include"Mapchip.h"
Map::Map()
{
	//出来てないところ
	//角度が内部は変わってるけど見た目は変わってない
	//基準点が００だから

	sprmap1	= sprite_load(L"./Data/Images/mapchip1.png");
	sprmap2	= sprite_load(L"./Data/Images/mapchip2.png");
	sprmap3	= sprite_load(L"./Data/Images/mapchip3.png");
	sprmap4	= sprite_load(L"./Data/Images/mapchip4.png");
	sprmob= sprite_load(L"./Data/Images/mob.png");
	sprfield= sprite_load(L"./Data/Images/field.png");
	

}
Map::~Map()
{
	
}
void Map::Update()
{
	Move();
	Road();
	debug::setString("pacth:%d", phase);


}
void Map::Road()	//道情報
{
	for (int i = 0;i < STAGE_Y;i++) {					//いまマスがどの向きか
		for (int j = 0;j < STAGE_X;j++) {
			switch (block[i][j].angle) {
			case   0: block[i][j].RotationCount = 0;break;//直線の場合	
			case  90: block[i][j].RotationCount = 1;break;//
			case 180: block[i][j].RotationCount = 2;break;//
			case 270: block[i][j].RotationCount = 3;break;//
			}

			if (block[i][j].angle >= 360) { block[i][j].angle = 0; }
		}
	}
	mapX = (m.pos.x) / chipSize;			//playerがいるマス
	mapY = (m.pos.y) / chipSize;			//playerがいるマス
	top = mapY * chipSize;					//今いるブロックの上端
	bottom = mapY * chipSize + chipSize;	//今いるブロックの下端
	left = mapX * chipSize;					//今いるブロックの左端
	right = mapX * chipSize + chipSize;		//今いるブロックの右端

	downmapY = mapY + 1;
	upmapY = mapY - 1;

	rightmapX = mapX + 1;
	leftmapX = mapX - 1;
	
	senterX = mapX * chipSize + MapCenter;
	senterY = mapY * chipSize + MapCenter;
}


void Map::Move()
{
	
	

	if (mapX < 0 || mapX >= STAGE_X ||
		mapY < 0 || mapY >= STAGE_Y)
		return;
	
	Road2();
	Road4();

	 
	


	debug::setString("map:%d x:%f y:%f right:%f\n", map[mapY][mapX], m.pos.x, m.pos.y,right);


		
}
void Map::Road2()//直線の道の時
{
	if (map[mapY][mapX] == 2)//今のブロックが直線
	{
		Road3();
		Road5();

		if (block[mapY][mapX].RotationCount % 2 == 0)//縦向きの道の時
		{
			m.pos.y += m.dirY * m.speed;//移動処理

			if (m.pos.y - 64 <= top)		//今いるブロックの上端についたら
			{
				//m.pos.y = top;
				m.dirY = 1;					//下に引き返す
				m.pos.y += m.dirY * m.speed;//移動処理
			}

			// 下端

			if (m.pos.y >= bottom)			//今いるブロックの下端についたら
			{
				//m.pos.y = bottom;
				m.dirY = -1;				//上に引き返す
				m.pos.y += m.dirY * m.speed;//移動処理
			}

		}
		if (block[mapY][mapX].RotationCount % 2 == 1)//横向きの道
		{
			m.pos.x += m.dirX * m.speed;//移動処理
			if (map[mapY][rightmapX] == 2 && block[mapY][rightmapX].RotationCount % 2 == 1)//次のブロックが直線の道の時かつ横向きの道の時
			{
				right += chipSize;
			}
			if (map[mapY][leftmapX] == 2 && block[mapY][leftmapX].RotationCount % 2 == 1)//前のブロックが直線の道の時かつ横向きの道の時
			{
				left -= chipSize;
			}

			if (m.pos.x <= left)		//今いるブロックの左端についたら
			{
				m.dirX = 1;			//右に引き返す
				m.pos.x += m.dirX * m.speed;//移動処理
				block[mapX][mapY].angle += 90;
			}

			// 下端

			if (m.pos.x >= right)	//今いるブロックの右端についたら
			{
				m.dirX = -1;		//左に引き返す
				m.pos.x += m.dirX * m.speed;//移動処理
			}
		}
	}
		
}
void Map::Road3()
{
	if (map[upmapY][mapX] == 2 && block[upmapY][mapX].RotationCount % 2 == 0)
	{
		top -= chipSize;
	}
	if (map[downmapY][mapX] == 2 && block[downmapY][mapX].RotationCount % 2 == 0)
	{
		bottom += chipSize;
	}
	if (map[mapY][rightmapX] == 2 && block[mapY][rightmapX].RotationCount % 2 == 1)
	{
		right += chipSize;
	}
	if (map[mapY][leftmapX] == 2 && block[mapY][leftmapX].RotationCount % 2 == 1)
	{
		left -= chipSize;
	}
}
void Map::Road4()
{
	if (map[mapY][mapX] == 3 && block[mapY][mapX].RotationCount == 0)//L字の時
	{
		Road3();
		if (phase == 0)//上からスタート
		{
			// 縦移動
			m.pos.y += m.dirY * m.speed;

			if (m.pos.y >= senterY)//真ん中についたら
			{
				m.dirY = 0;	//ｙ止める
				m.dirX = 1; // 右へ
				m.pos.x += m.dirX * m.speed;
				phase = 1;	//次の動きに

			}
		}
		else if (phase == 1)//真ん中から右
		{
			// 横移動
			m.pos.x += m.dirX * m.speed;

			if (m.pos.x >= 80)//右端についたら
			{
				m.dirX = -1;	//ｘ反転	 
				m.dirY = 0;		//ｙ止める
				m.pos.x += m.dirX * m.speed;
				phase = 2;		//次の動き
			}
		}
		else if (phase == 2)	//右から真ん中
		{
			m.pos.x += m.dirX * m.speed;
			if (m.pos.x <= senterX) //真ん中についたら 
			{
				m.dirX = 0;		//ｘ止める
				m.dirY = -1;	//ｙ反転
				m.pos.y += m.dirY * m.speed;
				phase = 3;		//次の動き
			}
		}
		else if (phase == 3)	//真ん中から上
		{
			m.pos.y += m.dirY * m.speed;
			if (m.pos.y <= top) //真ん中についたら 
			{
				m.dirY = 1;		//ｙ反転
				m.pos.y += m.dirY * m.speed;//移動処理 
				phase = 0;	//ループ
			}
		}
	}
}
void Map::Road5()//上下左右がL字の時
{
	if (map[upmapY][mapX] == 2 && block[upmapY][mapX].RotationCount % 2 == 0)
	{
		top -= chipSize;
	}
	if (map[downmapY][mapX] == 3 && block[downmapY][mapX].RotationCount == 0)
	{
		bottom += 1;
		phase = 0;
	}
	if (map[mapY][rightmapX] == 2 && block[mapY][rightmapX].RotationCount % 2 == 1)
	{
		right += chipSize;
	}
	if (map[mapY][leftmapX] == 2 && block[mapY][leftmapX].RotationCount % 2 == 1)
	{
		left -= chipSize;
	}
}
void Map::Render()
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
			float posX = j * chipSize;
			float posY = i * chipSize;
			switch (map[i][j]) {
				//通後不可
			case 1:
				sprite_render(sprmap1,
					posX, posY,
					1, 1,
					0, 0,
					chipSize, chipSize,
					0, 0,
					DegToRad(block[i][j].angle),
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
					DegToRad(block[i][j].angle),
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
					DegToRad(block[i][j].angle),
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
					DegToRad(block[i][j].angle),
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
		Mobsoze, Mobsoze,
		32	,64,
		0,
		1, 1, 1
	);


	debug::display(1,0,1,2,2); // ← 最後に描く
}