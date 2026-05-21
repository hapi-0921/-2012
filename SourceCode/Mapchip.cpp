#include"Mapchip.h"
#include <sstream>
Map::Map()
{
	
	map.resize(STAGE_Y);

	for (int y = 0; y < STAGE_Y; y++)
	{
		map[y].resize(STAGE_X);
	}
	map= {
		{7,2,3,2,2,2,1,2,1,2,3,2},
		{2,3,3,2,3,1,3,1,2,6,3,2},
		{2,2,3,3,1,2,3,2,2,2,1,3},
		{1,3,3,1,3,3,2,2,1,3,2,2},
		{3,3,1,4,3,1,2,3,2,3,1,2},
		{2,2,3,2,3,3,3,2,3,1,2,2},
		{3,1,2,2,1,2,1,2,2,3,5,1}
	};
	srand((unsigned int)time(nullptr));
	m.move.frame = 0;
	m.move.animTimer = 0.0f;
	m.move.direction = 0; // 0:下 1:右 2:左 3:上


	m.move.moveTimer = 0.0f;
	m.move.vx = 0;
	m.move.vy = 0;

	c.move.frame = 0;
	c.move.animTimer = 0.0f;
	c.move.direction = 0; // 0:下 1:右 2:左 3:上
	
	c.move.moveTimer = 0.0f;
	c.move.vx = 0;
	c.move.vy = 0;

	sprmap1 = sprite_load(L"./Data/Images/mapchip1.png");
	sprmap2 = sprite_load(L"./Data/Images/mapchip2.png");
	sprnotmap2 = sprite_load(L"./Data/Images/Road_Straight_Yellow.png");

	sprmap3 = sprite_load(L"./Data/Images/mapchip3.png");
	sprmap4 = sprite_load(L"./Data/Images/park.png");
	sprmap5 = sprite_load(L"./Data/Images/House.png");
	sprmap6 = sprite_load(L"./Data/Images/Piano.png");
	sprmap7 = sprite_load(L"./Data/Images/School.png");
	sprpass1 = sprite_load(L"./Data/Images/pass1.png");
	sprpass2 = sprite_load(L"./Data/Images/pass2.png");
	spr_Character = sprite_load(L"./Data/Images/Player_1.png");
	sprfield = sprite_load(L"./Data/Images/field.png");
	sprCar = sprite_load(L"./Data/Images/Track-1.png");
	sprDanger= sprite_load(L"./Data/Images/ABUNAI.png");
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
	block[1][2].angle = 180;





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






	block[0][0].notmove = true;
	block[2][9].notmove = true;
	block[5][3].notmove = true;
	block[0][1].notmove = true;
	block[4][3].notmove = true;
	block[1][9].notmove = true;
	block[6][10].notmove = true;



	m.move.canRotate = true;

	c.move.canRotate = false;
	

	
}



Map::~Map()
{
	safe_delete(sprmap1);
	safe_delete(sprmap2);
	safe_delete(sprmap3);
	safe_delete(sprmap4);
	safe_delete(spr_Character);
	safe_delete(sprfield);
}



void Map::Update()
{
	if (!goal)
	{
		RoadInfo Minfo = Road(m.move);
		RoadInfo Cinfo = Road(c.move);
		Move(m.move, Minfo);
		CarMoveChack(c.move, Cinfo);
		if (c.carmove)
		{
			Move(c.move, Cinfo);
		}
		GoHouse(m.move, Minfo);
		Gopiano(m.move, Minfo);
		Gopark(m.move, Minfo);
		if (m.housepoint)
		{
			goal = true;
		}
		if (HitBox(m.move.pos.x, m.move.pos.y,64,64,
			c.move.pos.x, c.move.pos.y,64,64)&&!m.invincible)
		{
			m.hit = true;
			m.hitTimer = 250;
			m.invincible = true;
			m.invincibleTimer = 260;
			if (c.move.dirX == -1)
			{
				m.knockbackX = -6;
				m.knockbackY = 0;
			}
			else if (c.move.dirX == 1)
			{
				m.knockbackX = 6;
				m.knockbackY = 0;
			}
			else if (c.move.dirY ==-1)
			{
				m.knockbackX = 0;
				m.knockbackY = -6;
			}
			else if (c.move.dirY == 1)
			{
				m.knockbackX = 0;
				m.knockbackY = 6;
			}
			
		}
		if (m.invincible)
		{
			m.invincibleTimer--;

			if (m.invincibleTimer <= 0)
			{
				m.invincible = false;
			}
		}
		if (m.hit)
		{
			m.move.pos.x += m.knockbackX;
			m.move.pos.y += m.knockbackY;

			m.knockbackX *= 0.9f;
			m.knockbackY *= 0.9f;
			m.hitTimer--;
			m.move.speed = 0;
			

			if (m.hitTimer <= 0)
			{
				m.move.speed = 1;
				m.hit = false;
			}

			return;
		}
	}
	if (c.move.cartocollide)//車が一回跳ね返ったら場外に出す
	{
		if (c.move.pos.y < Y - 100 ||
			c.move.pos.y > Y + map.size() * chipSize + 100 ||
			c.move.pos.x < X - 100 ||
			c.move.pos.x > X + map[0].size() * chipSize + 100)
		{
			c.move.active = false;
		}
	}
	if (!c.move.active)
	{
		c.move.cartimer++;
	}
	if (c.move.cartimer >= 300)
	{
		c.carmove = false;
		c.move.cartimer = 0;
		c.move.cartocollide = false;
	}
	gametimer++;
}
void Map::TutorialUpdate()
{
	
	RoadInfo Minfo = Road(m.move);
	RoadInfo Cinfo = Road(c.move);
	Move(m.move, Minfo);
}
Map::RoadInfo Map::Road(MoveObject& obj)
{
	//---------------------------------
	// マップチップの向き
	//---------------------------------

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {

			switch (block[i][j].angle) {

			case 0:
				block[i][j].RotationCount = 0;
				break;

			case 90:
				block[i][j].RotationCount = 1;
				break;

			case 180:
				block[i][j].RotationCount = 2;
				break;

			case 270:
				block[i][j].RotationCount = 3;
				break;
			}

			if (block[i][j].angle >= 360) {
				block[i][j].angle = 0;
			}
		}
	}
	RoadInfo info;
	info.footX = obj.pos.x + 32;
	info.footY = obj.pos.y + 64;

	info.localX = info.footX - X;
	info.localY = info.footY - Y;

	info.mapX = (int)(info.localX / chipSize);
	info.mapY = (int)(info.localY / chipSize);

	info.left = info.mapX * chipSize + X;
	info.right = info.left + chipSize;

	info.top = info.mapY * chipSize + Y;
	info.bottom = info.top + chipSize;

	info.senterX = info.left + MapCenter;
	info.senterY = info.top + MapCenter;

	info.upmapY = info.mapY - 1;
	info.downmapY = info.mapY + 1;

	info.leftmapX = info.mapX - 1;
	info.rightmapX = info.mapX + 1;

	return info;
}
void Map::Move(MoveObject& obj, RoadInfo& info)
{
	



	if (info.mapX < 0 || info.mapX >= map[0].size() ||
		info.mapY < 0 || info.mapY >= map.size())
	{


		if (obj.cartocollide)
		{
			obj.pos.x += obj.dirX * obj.speed;
			obj.pos.y += obj.dirY * obj.speed;
		}
		return;
	}

	Road2(obj, info);
	Road4(obj, info);


}
void Map::Road2(MoveObject& obj, RoadInfo& info)//直線の道の時
{

	if (map[info.mapY][info.mapX] == 2)//今のブロックが直線
	{

		if (block[info.mapY][info.mapX].RotationCount % 2 == 0)//縦向きの道の時
		{

			obj.pos.y += obj.dirY * obj.speed;//移動処理
			info.footY = obj.pos.y + 64;
			if (obj.dirY == -1)
			{

				if (info.footY <= info.top)		//今いるブロックの上端についたら
				{
					if (CanMove(obj,info,UP))
					{
						info.top -= 1;

						if (map[info.upmapY][info.mapX] == 3)
						{
							obj.phase = downsenter; // 下から真ん中へ
						}
					}
					else
					{

						if (obj.cartocollide)
						{
							// 車は場外へ出す
							obj.pos.y += obj.dirY * obj.speed;
							return;
						}
						if (&obj == &c.move)
						{
							obj.cartocollide = true;
						}
						SetMoveDown(obj);
						if (obj.canRotate&&!block[info.mapY][info.mapX].notmove)
						{
							block[info.mapY][info.mapX].pass += 1;
							Rotation(obj, info);
						}
						obj.pos.y += obj.dirY * obj.speed;//移動処理

					}
				}

			}



			// 下端
			if (obj.dirY == 1)
			{
				if (info.footY >= info.bottom)			//今いるブロックの下端についたら
				{
					if (CanMove(obj, info,DOWN))
					{
						info.bottom += 1;

						if (map[info.downmapY][info.mapX] == 3)
						{
							obj.phase = upsenter; // 上から真ん中へ
						}
					}
					else
					{
						if (obj.cartocollide)
						{
							// 車は場外へ出す
							obj.pos.y += obj.dirY * obj.speed;
							return;
						}
						if (&obj == &c.move)
						{
							obj.cartocollide = true;
						}

						SetMoveUp(obj);
						obj.pos.y += obj.dirY * obj.speed;//移動処理

						if (obj.canRotate&&!block[info.mapY][info.mapX].notmove)
						{
							block[info.mapY][info.mapX].pass += 1;
							Rotation(obj, info);
						}
					}
				}
			}

		}
		if (block[info.mapY][info.mapX].RotationCount % 2 == 1)//横向きの道
		{
			obj.pos.x += obj.dirX * obj.speed;//移動処理
			info.footX = obj.pos.x + 32;
			if (obj.dirX == -1)
			{
				if (info.footX <= info.left)		//今いるブロックの左端についたら
				{
					if (CanMove(obj, info,LEFT))
					{
						info.left -= 1;

						if (map[info.mapY][info.leftmapX] == 3)
						{
							obj.phase = rightsenter; // 右から真ん中へ
						}
					}
					else
					{
						if (obj.cartocollide)
						{
							// 車は場外へ出す
							obj.pos.x += obj.dirX * obj.speed;
							return;
						}
						if (&obj == &c.move)
						{
							obj.cartocollide = true;
						}
						SetMoveRight(obj);
						obj.pos.x += obj.dirX * obj.speed;//移動処理
						if (obj.canRotate && !block[info.mapY][info.mapX].notmove)
						{
							block[info.mapY][info.mapX].pass += 1;
							Rotation(obj, info);
						}
					}
				}

			}

			if (obj.dirX == 1)
			{
				if (info.footX >= info.right)		//今いるブロックの右端についたら
				{

					if (CanMove(obj, info,RIGHT))
					{
						info.right += 1;

						// 次が曲線なら phase変更
						if (map[info.mapY][info.rightmapX] == 3)
						{
							obj.phase = leftsenter; // 左から真ん中へ
						}
					}
					else
					{
						if (obj.cartocollide)
						{
							// 車は場外へ出す
							obj.pos.x += obj.dirX * obj.speed;
							return;
						}
						if (&obj == &c.move)
						{
							obj.cartocollide = true;
						}
						SetMoveLeft(obj);
						obj.pos.x += obj.dirX * obj.speed;//移動処理
						if (obj.canRotate && !block[info.mapY][info.mapX].notmove)
						{
							block[info.mapY][info.mapX].pass += 1;
							Rotation(obj, info);
						}
					}
				}

			}

		}
	}

}
void Map::Road4(MoveObject& obj, RoadInfo& info)//曲線の道の時
{


	if (map[info.mapY][info.mapX] == 3)
	{

		if (obj.phase == 0)//上から真ん中
		{

			// 縦移動
			obj.pos.y += obj.dirY * obj.speed;
			UpdateInfo(obj, info);

			if (info.footY >= info.senterY)//上から真ん中についたら
			{
				if (block[info.mapY][info.mapX].RotationCount == 0)//Lの時
				{
					SetMoveRight(obj);
					obj.pos.x += obj.dirX * obj.speed;
					obj.phase = senterright;	//次の動きに
				}
				else if (block[info.mapY][info.mapX].RotationCount == 3)//」の時
				{
					SetMoveLeft(obj);
					obj.pos.x += obj.dirX * obj.speed;
					obj.phase = senterleft;	//次の動きに
				}
				else
				{
					obj.phase = senterdown;
				}


			}
		}
		else if (obj.phase == 1)//真ん中から右
		{
			// 横移動
			obj.pos.x += obj.dirX * obj.speed;
			info.footX = obj.pos.x + 32;

			if (info.footX >= info.right)
			{

				if (CanMove(obj, info,RIGHT))
				{
					info.right += 1;
					
					// 次のマスが曲線なら
					if (map[info.mapY][info.rightmapX] == 3)
					{
						obj.phase = leftsenter;
					}
				}
				else
				{
					if (obj.canRotate && !block[info.mapY][info.mapX].notmove)
					{
						block[info.mapY][info.mapX].pass += 1;
						Rotation(obj, info);
					}
					if (&obj == &c.move)
					{
						obj.cartocollide = true;
					}					SetMoveLeft(obj);
					obj.pos.x += obj.dirX * obj.speed;
					obj.phase = rightsenter;
				}
			}
		}
		else if (obj.phase == 2)	//右から真ん中
		{

			obj.pos.x += obj.dirX * obj.speed;
			UpdateInfo(obj, info);

			if (info.footX <= info.senterX) //真ん中についたら 
			{

				if (block[info.mapY][info.mapX].RotationCount == 0)//Lの時
				{
					SetMoveUp(obj);
					obj.pos.y += obj.dirY * obj.speed;
					obj.phase = senterup;		//次の動き
				}
				else if (block[info.mapY][info.mapX].RotationCount == 1)//「の時
				{
					SetMoveDown(obj);
					obj.pos.y += obj.dirY * obj.speed;
					obj.phase = senterdown;		//次の動き
				}
				else
				{
					obj.phase = senterleft;
				}
			}
		}
		else if (obj.phase == 3)	//真ん中から上
		{

			obj.pos.y += obj.dirY * obj.speed;
			info.footY = obj.pos.y + 64;
			if (info.footY <= info.top) //上についたら 
			{

				if (CanMove(obj, info,UP))
				{
					info.top -= 1;
					
					if (map[info.upmapY][info.mapX] == 3)
					{
						obj.phase = downsenter;
					}
				}
				else
				{

					if (obj.canRotate && !block[info.mapY][info.mapX].notmove)
					{
						block[info.mapY][info.mapX].pass += 1;
						Rotation(obj, info);
					}
					if (&obj == &c.move)
					{
						obj.cartocollide = true;
					}					SetMoveDown(obj);
					obj.pos.y += obj.dirY * obj.speed;//移動処理 
					obj.phase = upsenter;//ループ

				}
			}

		}
		else if (obj.phase == 4)//真ん中から左
		{
			// 横移動
			obj.pos.x += obj.dirX * obj.speed;
			info.footX = obj.pos.x + 32;

			if (info.footX <= info.left)//左端についたら
			{
				if (CanMove(obj, info,LEFT))
				{
					info.left -= 1;
					if (map[info.mapY][info.leftmapX] == 3)
					{
						obj.phase = rightsenter;
					}
				}
				else
				{
					if (obj.canRotate && !block[info.mapY][info.mapX].notmove)
					{
						block[info.mapY][info.mapX].pass += 1;
						Rotation(obj, info);
					}
					if (&obj == &c.move)
					{
						obj.cartocollide = true;
					}					SetMoveRight(obj);
					obj.pos.x += obj.dirX * obj.speed;
					obj.phase = leftsenter;	//次の動き
				}
			}

		}
		else if (obj.phase == 5)	//左から真ん中
		{


			obj.pos.x += obj.dirX * obj.speed;
			UpdateInfo(obj, info);
			if (info.footX >= info.senterX) //真ん中についたら 
			{
				if (block[info.mapY][info.mapX].RotationCount == 2)//7の時
				{
					SetMoveDown(obj);
					obj.pos.y += obj.dirY * obj.speed;
					obj.phase = senterdown;		//次の動き
				}
				else if (block[info.mapY][info.mapX].RotationCount == 3)//」の時
				{
					SetMoveUp(obj);
					obj.pos.y += obj.dirY * obj.speed;
					obj.phase = senterup;		//次の動き
				}
				else
				{
					obj.phase = senterright;
				}
			}
		}
		else if (obj.phase == 6)	//下から真ん中
		{


			obj.pos.y += obj.dirY * obj.speed;
			UpdateInfo(obj,info);

			//if (info.footY <= info.senterY) //真ん中についたら 
			if (info.footY <= info.senterY) //真ん中についたら 
			{
				if (block[info.mapY][info.mapX].RotationCount == 1)//「の時
				{
					SetMoveRight(obj);
					obj.pos.y += obj.dirY * obj.speed;
					obj.phase = senterright;		//次の動き
				}
				else if (block[info.mapY][info.mapX].RotationCount == 2)//7の時
				{
					SetMoveLeft(obj);
					obj.pos.y += obj.dirY * obj.speed;
					obj.phase = senterleft;		//次の動き
				}
				else
				{
					obj.phase = senterup;
				}

			}
		}
		else if (obj.phase == 7)	//真ん中から下
		{


			obj.pos.y += obj.dirY * obj.speed;
			info.footY = obj.pos.y + 64;
			if (info.footY >= info.bottom) //下についたら 
			{
				if (CanMove(obj, info,DOWN))
				{
					info.bottom += 1;
					
					if (map[info.downmapY][info.mapX] == 3)
					{
						obj.phase = upsenter;
					}

				}
				else
				{
					if (obj.canRotate && !block[info.mapY][info.mapX].notmove)
					{
						block[info.mapY][info.mapX].pass += 1;
						Rotation(obj, info);
					}
					if (&obj == &c.move)
					{
						obj.cartocollide = true;
					}					SetMoveUp(obj);
					obj.pos.y += obj.dirY * obj.speed;
					obj.phase = downsenter;		//次の動き

				}



			}
		}
	}
}
void Map::CarMoveChack(MoveObject& obj, RoadInfo& info)
{
	static int r = 0;

	// 各方向の探索開始位置
	static int topStart = -1;
	static int bottomStart = -1;
	static int rightStart = -1;
	static int leftStart = -1;

	// 最初だけランダム
	if (topStart == -1)		topStart = rand() % map[0].size();
	if (bottomStart == -1)	bottomStart = rand() % map[0].size();
	if (rightStart == -1)	rightStart = rand() % map.size();
	if (leftStart == -1)	leftStart = rand() % map.size();

	if (!c.carmove)
	{
		int dirs[4] = { 0, 1, 2, 3 };

		// シャッフル
		for (int i = 0; i < 4; i++)
		{
			int j = rand() % 4;
			std::swap(dirs[i], dirs[j]);
		}

		for (int k = 0; k < 4; k++)
		{
			switch (0)
			{
				// 上
			case 0:
				for (int i = 0; i < map[0].size(); i++)
				{
					int j = (topStart + i) % map[0].size();

					if (map[0][j] == 2 &&
						block[0][j].RotationCount % 2 == 0)
					{
						UpdateInfo(j, 0, info);

						if (CanMove(obj, info, DOWN))
						{
							CarMove(obj, info, j, 0);
							
							topStart = (j + 1) % map[0].size();

							r = (r + 1) % 4;
							return;
						}
					}
				}
				break;

				// 下
			case 1:
				for (int i = 0; i < map[0].size(); i++)
				{
					int j = (bottomStart + i) % map[0].size();

					if (map[map.size() - 1][j] == 2 &&
						block[map.size() - 1][j].RotationCount % 2 == 0)
					{
						UpdateInfo(j, map.size() - 1, info);

						if (CanMove(obj, info, UP))
						{
							CarMove(obj, info, j, 1);

							

							bottomStart = (j + 1) % map[0].size();

							r = (r + 1) % 4;
							return;
						}
					}
				}
				break;

				// 右
			case 2:
				for (int i = 0; i < map.size(); i++)
				{
					int j = (rightStart + i) % map.size();

					if (map[j][map[0].size() - 1] == 2 &&
						block[j][map[0].size() - 1].RotationCount % 2 != 0)
					{
						UpdateInfo(map[0].size() - 1, j, info);

						if (CanMove(obj, info, LEFT))
						{
							CarMove(obj, info, j, 2);

							rightStart = (j + 1) % map.size();

							r = (r + 1) % 4;
							return;
						}
					}
				}
				break;

				// 左
			case 3:
				for (int i = 0; i < map.size(); i++)
				{
					int j = (leftStart + i) % map.size();

					if (map[j][0] == 2 &&
						block[j][0].RotationCount % 2 != 0)
					{
						UpdateInfo(0, j, info);

						if (CanMove(obj, info, RIGHT))
						{
							CarMove(obj, info, j, 3);
							leftStart = (j + 1) % map.size();

							r = (r + 1) % 4;
							return;
						}
					}
				}
				break;
			}
		}

		r = (r + 1) % 4;
	}

	
}

void Map::CarMove(MoveObject& obj, RoadInfo& info,int j,int type)
{
	switch (type)
	{
	case 0://上から下
		SetPosFromMap(obj, j, 0);
		SetMoveDown(obj);
		DangerY = c.move.pos.y - 50;
		DangerX = c.move.pos.x + 32;
		Dangerangle = 180;
		c.move.pos.y -= 100;
		c.carmove = true;
		c.move.active = true;
		
		
		break;

	case 1://下から上
		SetPosFromMap(obj, j, map.size() - 1);
		SetMoveUp(obj);
		DangerY = c.move.pos.y + 50;
		c.carmove = true;
		c.move.active = true;
		c.move.pos.y += 64;
		DangerX = c.move.pos.x + 32;
		Dangerangle = 0;

		break;
	case 2://右から左
		SetPosFromMap(obj, map[0].size() - 1, j);
		SetMoveLeft(obj);
		DangerY = c.move.pos.y + 32;
		DangerX = c.move.pos.x + 50;
		Dangerangle = 270;
		c.carmove = true;
		c.move.active = true;
		c.move.pos.x += 64;
		break;

	case 3://左から右
		SetPosFromMap(obj, 0, j);
		SetMoveRight(obj);
		DangerY = c.move.pos.y + 32;
		DangerX = c.move.pos.x - 50;
		Dangerangle = 270;
		c.carmove = true;
		c.move.active = true;
		c.move.pos.x -= 100;

		break;
	}
}

	


void Map::Rotation(MoveObject& obj, RoadInfo& info)//回転させる関数
{

	BlockData& blockData = block[info.mapY][info.mapX];

	// 偶数回通過した瞬間だけ回転
	if (blockData.pass != 0 &&
		blockData.pass % 3 == 0 &&
		blockData.rotated == false)
	{
		blockData.rotated = true;

		int oldDirX = obj.dirX;
		int oldDirY = obj.dirY;
		// 回転

		blockData.angle += 90;

		int rot = (blockData.angle / 90) % 4;

		if (map[info.mapY][info.mapX] == 2)
		{

			// 縦になった
			if (rot % 2 == 0)
			{
				
				obj.pos.x = info.senterX - 32;
				if (oldDirX == -1)
				{
					SetMoveUp(obj);
				}
				else if (oldDirX == 1)
				{
					SetMoveDown(obj);
				}
			}
			// 横になった
			else
			{
				obj.pos.y = info.senterY - 64;
				
				if (oldDirY == -1)
				{
					SetMoveLeft(obj);
				}
				else if (oldDirY == 1)
				{
					SetMoveRight(obj);
				}
			}
		}
		if (map[info.mapY][info.mapX] == 3)
		{

			switch (rot)
			{
			case 0:

				if (oldDirX == -1)
				{
					SetMoveDown(obj);
					obj.phase = leftsenter;
				}
				else if (oldDirY == -1)
				{
					SetMoveRight(obj);
					obj.phase = upsenter;
				}

				break;

			case 1:

				if (oldDirY == 1)
				{
					SetMoveRight(obj);
					obj.phase = downsenter;
				}
				else if (oldDirX == -1)
				{
					SetMoveUp(obj);
					obj.phase = leftsenter;
				}

				break;

			case 2:

				if (oldDirX == 1)
				{
					SetMoveLeft(obj);
					obj.phase = rightsenter;
				}
				else if (oldDirY == 1)
				{
					SetMoveUp(obj);
					obj.phase = downsenter;
				}

				break;

			case 3:

				if (oldDirX == 1)
				{
					SetMoveDown(obj);
					obj.phase = rightsenter;
				}
				else if (oldDirY == -1)
				{
					SetMoveLeft(obj);
					obj.phase = upsenter;
				}

				break;

			}

			
		}
		blockData.RotationCount =
			(blockData.angle / 90) % 4;
	}
	// 奇数に戻ったら解除
	if (blockData.pass % 3 != 0)
	{
		blockData.rotated = false;
	}
}

bool Map::CanMove(MoveObject& obj,RoadInfo& info, Direction dir)
{
	int checkX = info.mapX;
	int checkY = info.mapY;

	// 方向ごとの座標変更
	switch (dir)
	{
	case UP:
		checkY--;
		break;

	case DOWN:
		checkY++;
		break;

	case LEFT:
		checkX--;
		break;

	case RIGHT:
		checkX++;
		break;
	}

	
	// 範囲外チェック
	if (checkX < 0 || checkX >= map[0].size() ||
		checkY < 0 || checkY >= map.size())
	{
		return false;
	}
	
	int mapType = map[checkY][checkX];
	int rot = block[checkY][checkX].RotationCount;

	// 特殊マス
	if (mapType == 4)
	{
		if(obj.canRotate)
		return true;
		else
		{
			return false;
		}
	}

	if (mapType == 6)
	{
		if (obj.canRotate)
			return m.parkpoint;
		else
		{
			return false;
		}
		
	}

	if (mapType == 5)
	{
		if (obj.canRotate)
			return m.parkpoint && m.pianopoint;
		else
		{
			return false;
		}
		
	}
	
	// 直線
	if (mapType == 2)
	{
		if ((dir == UP || dir == DOWN) && rot % 2 == 0)
		{
			return true;
		}

		if ((dir == LEFT || dir == RIGHT) && rot % 2 == 1)
		{
			return true;
		}
	}

	// 曲線
	if (mapType == 3)
	{
		switch (dir)
		{
		case UP:
			return rot == 1 || rot == 2;

		case DOWN:
			return rot == 0 || rot == 3;

		case LEFT:
			return rot == 0 || rot == 1;

		case RIGHT:
			return rot == 2 || rot == 3;
		}
	}

	
	

	return false;
	
}

bool Map::Gopark(MoveObject& obj, RoadInfo& info)
{
	if (map[info.mapY][info.mapX] == 4)
	{
		m.parkpoint = true;
		SetPosFromMap(obj, 3, 5);
		SetMoveDown(obj);
	}
	return false;
}



bool Map::Gopiano(MoveObject& obj, RoadInfo& info)
{
	if (map[info.mapY][info.mapX] == 6)
	{
		m.pianopoint = true;
		SetPosFromMap(obj, 9, 2);
		SetMoveDown(obj);
	}
	return false;
}
bool Map::GoHouse(MoveObject& obj, RoadInfo& info)
{
	if (map[info.mapY][info.mapX] == 5)
	{
		m.housepoint = true;
		
	}
	return false;
}

void Map::UpdateInfo(MoveObject& obj, RoadInfo& info)
{
	info.footX = obj.pos.x + 32;
	info.footY = obj.pos.y + 64;

	info.localX = info.footX - X;
	info.localY = info.footY - Y;

	int mapX = (int)(info.localX / chipSize);
	int mapY = (int)(info.localY / chipSize);

	UpdateInfo(mapX, mapY, info);
}
void Map::UpdateInfo(
	int mapX,
	int mapY,
	RoadInfo& info)
{
	info.mapX = mapX;
	info.mapY = mapY;

	info.left = mapX * chipSize + X;
	info.right = info.left + chipSize;

	info.top = mapY * chipSize + Y;
	info.bottom = info.top + chipSize;

	info.senterX = info.left + MapCenter;
	info.senterY = info.top + MapCenter;

	info.upmapY = mapY - 1;
	info.downmapY = mapY + 1;

	info.leftmapX = mapX - 1;
	info.rightmapX = mapX + 1;
}
void Map::SetMoveRight(MoveObject& obj)
{
	obj.dirX = 1;
	obj.dirY = 0;
}
void Map::SetMoveLeft(MoveObject& obj)
{
	obj.dirX = -1;
	obj.dirY = 0;
}

void Map::SetMoveUp(MoveObject& obj)
{
	obj.dirX = 0;
	obj.dirY = -1;
}

void Map::SetMoveDown(MoveObject& obj)
{
	obj.dirX = 0;
	obj.dirY = 1;
}
void Map::SetPosFromMap(MoveObject& obj,int mapX,int mapY)
{
	obj.pos.x = mapX * chipSize + X+32;
	obj.pos.y = mapY * chipSize + Y;
}

bool Map::HitBox(float ax, float ay, float aw, float ah,
	float bx, float by, float bw, float bh)
{
	return (ax < bx + bw &&
		ax + aw > bx &&
		ay < by + bh &&
		ay + ah > by);
}

void Map::Animation(MoveObject& obj,Sprite*spr)
{
	if (!tutorial)
	{
		//アニメーション

		obj.animTimer += 1.0f / 60.0f;
	}
	

	if (obj.animTimer >= 0.2f)
	{
		obj.frame++;
		if (obj.frame >= 4) obj.frame = 0;
		obj.animTimer = 0;
	}
	if (obj.dirX == 1)
	{
		obj.direction = 1; // 右
	}
	else if (obj.dirX == -1)
	{
		obj.direction = 2; // 左
	}
	else if (obj.dirY == 1)
	{
		obj.direction = 0; // 下
	}
	else if (obj.dirY == -1)
	{
		obj.direction = 3; // 上
	}
	int sx = obj.frame * CHARACTER_TEX_W;
	int sy = obj.direction * CHARACTER_TEX_H;

	if (spr== nullptr) return;
	sprite_render(spr, obj.pos.x, obj.pos.y,
		1, 1,
		sx, sy,
		CHARACTER_TEX_W, CHARACTER_TEX_H);

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
	if (!tutorial)
	{
		scale = 2;
		chipSize = 128;
	}
	else
	{
		scale = 3;
		chipSize = 192;
	}
		for (int i = 0;i < map.size();i++) {				//ブロック描画
			for (int j = 0;j < map[i].size();j++) {
				posX = j * chipSize + X + MapCenter;
				posY = i * chipSize + Y + MapCenter;
				switch (map[i][j]) {
					//通後不可
				case 1:
					sprite_render(sprmap1,
						posX, posY,
						scale, scale,
						0, 0,
						64, 64,
						32, 32,
						DegToRad(block[i][j].angle),
						1, 1, 1
					);
					break;
					//直線
				case 2:
					if (block[i][j].notmove)
					{
						sprite_render(sprnotmap2,
							posX, posY,
							scale, scale,
							0, 0,
							64, 64,
							32, 32,
							DegToRad(block[i][j].angle),
							1, 1, 1
						);
					}
					else
					{
						sprite_render(sprmap2,
							posX, posY,
							scale, scale,
							0, 0,
							64, 64,
							32, 32,
							DegToRad(block[i][j].angle),
							1, 1, 1
						);
					}
					break;
					//曲線
				case 3:
					sprite_render(sprmap3,
						posX, posY,
						scale, scale,
						0, 0,
						64, 64,
						32, 32,
						DegToRad(block[i][j].angle),
						1, 1, 1
					);
					break;
					//T字
				case 4:
					sprite_render(sprmap4,
						posX, posY,
						scale, scale,
						0, 0,
						64, 64,
						32, 32,
						DegToRad(block[i][j].angle),
						1, 1, 1
					);
					break;
				case 5:
					sprite_render(sprmap5,
						posX, posY,
						scale, scale,
						0, 0,
						64, 64,
						32, 32,
						DegToRad(block[i][j].angle),
						1, 1, 1
					);
					break;
				case 6:
					sprite_render(sprmap6,
						posX, posY,
						2, 2,
						0, 0,
						64, 64,
						32, 32,
						DegToRad(block[i][j].angle),
						1, 1, 1
					);
					break;
				case 7:
					sprite_render(sprmap7,
						posX, posY,
						scale, scale,
						0, 0,
						64, 64,
						32, 32,
						DegToRad(block[i][j].angle),
						1, 1, 1
					);
					break;
				}
				switch (block[i][j].pass % 3)
				{
				case 1:
					sprite_render(sprpass1,
						posX, posY,
						scale, scale,
						0, 0,
						64, 64,
						32, 32,
						DegToRad(block[i][j].angle),
						1, 1, 1
					);
					break;



	debug::display(1, 0, 1, 2, 2); // ← 最後に描く


				case 2:
					sprite_render(sprpass2,
						posX, posY,
						scale, scale,
						0, 0,
						64, 64,
						32, 32,
						DegToRad(block[i][j].angle),
						1, 1, 1);
					break;

				}
				// Debug表示
				std::stringstream tmp;
				tmp << block[i][j].pass;

				text_out(
					0,
					tmp.str(),
					posX, posY,
					1.5f, 1.5f,
					1, 0, 1, 1);
			}
		}
	
	
	
		


	//キャラの絵


	Animation(m.move, spr_Character);
	Animation(c.move, sprCar);
	if(gametimer >> 6 & 0x01)
	sprite_render(sprDanger, DangerX, DangerY, 1, 1, 1, 1, 64, 64, 32, 32, DegToRad(Dangerangle));

	
	debug::display(1, 0, 1, 2, 2); // ← 最後に描く


	debug::display(1, 0, 1, 2, 2); // ← 最後に描く

	int carsx = m.move.frame * CHARACTER_TEX_W;
	int carsy = m.move.direction * CHARACTER_TEX_H;
	if (spr_Character == nullptr) return;



	/*sprite_render(spr_Character, m.move.pos.x, m.move.pos.y, 1, 1,
		m.move.vx, m.move.vy, CHARACTER_TEX_W, CHARACTER_TEX_H);

	sprite_render(sprCar, c.move.pos.x, c.move.pos.y, 1, 1,
		1, 1, CHARACTER_TEX_W, CHARACTER_TEX_H);*/



	debug::display(1, 0, 1, 2, 2); // ← 最後に描く







	debug::display(1, 0, 1, 2, 2); // ← 最後に描く
}