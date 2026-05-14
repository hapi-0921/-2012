#include"Mapchip.h"
#include <sstream>
Map::Map()
{
	//出来てないところ
	//角度が内部は変わってるけど見た目は変わってない
	//基準点が００だから


	m.frame = 0;
	m.animTimer = 0.0f;
	m.direction = 0; // 0:下 1:右 2:左 3:上

	
	m.moveTimer = 0.0f;
	m.vx = 0;
	m.vy = 0;


	sprmap1	= sprite_load(L"./Data/Images/mapchip1.png");
	sprmap2	= sprite_load(L"./Data/Images/mapchip2.png");
	sprmap3	= sprite_load(L"./Data/Images/mapchip3.png");
	sprmap4	= sprite_load(L"./Data/Images/mapchip4.png");
	spr_Character = sprite_load(L"./Data/Images/Player_1.png");
	sprfield= sprite_load(L"./Data/Images/field.png");
	block[0][0].angle = 90;
	block[0][1].angle = 180;
	block[1][0].angle = 0;
	block[1][1].angle = 270;
	block[1][3].angle = 0;
	block[2][3].angle = 270;
	block[2][2].angle = 0;
	block[1][2].angle = 180;
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

	Road();
	Move();

	debug::setString("phase:%d", phase);
	debug::setString("map:%d x:%f y:%f topY:%f\n", map[mapY][mapX], m.pos.x, m.pos.y, top);
	debug::setString("MapX:%d MapY:%d", mapX,mapY);
	debug::setString("pass:%d", block[mapY][mapX].pass);
	debug::setString("Left:%f", top);
	debug::setString("Right:%f", bottom);



	if (m.dirX == 1)
	{
		m.direction = 1; // 右
	}
	else if (m.dirX == -1)
	{
		m.direction = 2; // 左
	}
	else if (m.dirY == 1)
	{
		m.direction = 0; // 下
	}
	else if (m.dirY == -1)
	{
		m.direction = 3; // 上
	}


}
void Map::Road()	//道情報
{
	for (int i = 0;i < STAGE_Y;i++) {					//いまマスがどの向きか
		for (int j = 0;j < STAGE_X;j++) {
			switch (block[i][j].angle) {
			case   0: block[i][j].RotationCount = 0;break;//直線の場合	ll 曲線の場合L
			case  90: block[i][j].RotationCount = 1;break;//直線の場合	二 曲線の場合「
			case 180: block[i][j].RotationCount = 2;break;//直線の場合	ll 曲線の場合７
			case 270: block[i][j].RotationCount = 3;break;//直線の場合	二 曲線の場合」
			}

			if (block[i][j].angle >= 360) { block[i][j].angle = 0; }
			

		}
	}
	//---------------------------------
	// プレイヤー足元
	//---------------------------------

	footX = m.pos.x + 32;
	footY = m.pos.y + 64;

	//---------------------------------
	// mobの画面座標 → マップ座標へ変換
	//---------------------------------

	localX = footX - X;
	localY = footY - Y;

	//---------------------------------
	// 今いるマス
	//---------------------------------

	mapX = (int)(localX / chipSize);
	mapY = (int)(localY / chipSize);
	if (mapX < 0 || mapX >= STAGE_X ||
		mapY < 0 || mapY >= STAGE_Y)
	{
		return;
	}
	//---------------------------------
	// マス境界（画面座標）
	//---------------------------------

	left = mapX * chipSize+X;
	right = left + chipSize;

	top = mapY * chipSize + Y ;
	bottom = top + chipSize ;

	//---------------------------------
	// マス中央（画面座標）
	//---------------------------------

	senterX = left+ MapCenter;
	senterY = top+ MapCenter;

	//---------------------------------
	// 周囲マス
	//---------------------------------

	upmapY = mapY - 1;
	downmapY = mapY + 1;

	leftmapX = mapX - 1;
	rightmapX = mapX + 1;

	
}


void Map::Move()
{
	//アニメーション
	m.animTimer += 1.0f / 60.0f;

	if (m.animTimer >= 0.2f)
	{
		m.frame++;
		if (m.frame >= 4) m.frame = 0;
		m.animTimer = 0;
	}



	if (mapX < 0 || mapX >= STAGE_X ||
		mapY < 0 || mapY >= STAGE_Y)
		return;

	
	Road2();
	Road4();
	
}
void Map::Road2()//直線の道の時
{
	if (map[mapY][mapX] == 2)//今のブロックが直線
	{
		
		if (block[mapY][mapX].RotationCount % 2 == 0)//縦向きの道の時
		{
			
			m.pos.y += m.dirY * m.speed;//移動処理
			footY = m.pos.y + 64;
			if (m.dirY==-1)
			{
				
					if (footY <= top )		//今いるブロックの上端についたら
					{
						if (CanMoveUp())
						{
							top -= 1;

							if (map[upmapY][mapX] == 3)
							{
								phase = 6; // 下から真ん中へ
							}
						}
						else
						{
							SetMoveDown();
							m.pos.y += m.dirY * m.speed;//移動処理
							block[mapY][mapX].pass += 1;
							Rotation();
						}
					}
				
			}
				
			
			
			// 下端
				if (m.dirY==1)
				{
					if (footY >= bottom)			//今いるブロックの下端についたら
					{
						if (CanMoveDown())
						{
							bottom += 1;

							if (map[downmapY][mapX] == 3)
							{
								phase = 0; // 上から真ん中へ
							}
						}
						else
						{
							SetMoveUp();
							m.pos.y += m.dirY * m.speed;//移動処理
							block[mapY][mapX].pass += 1;
							Rotation();
						}
					}
				}

		}
		if (block[mapY][mapX].RotationCount % 2 == 1)//横向きの道
		{
			m.pos.x += m.dirX * m.speed;//移動処理
			footX = m.pos.x + 32;
			if (m.dirX == -1)
			{
				if (footX <= left)		//今いるブロックの左端についたら
				{
					if (CanMoveLeft())
					{
						left -= 1;

						if (map[mapY][leftmapX] == 3)
						{
							phase = 2; // 右から真ん中へ
						}
					}
					else
					{
						SetMoveRight();
						m.pos.x += m.dirX * m.speed;//移動処理
						block[mapY][mapX].pass += 1;
						Rotation();
					}
				}

			}
			
			if (m.dirX == 1)
			{
				if (footX >= right)		//今いるブロックの右端についたら
				{
					if (CanMoveRight())
					{
						right += 1;

						// 次が曲線なら phase変更
						if (map[mapY][rightmapX] == 3)
						{
							phase = 5; // 左から真ん中へ
						}
					}
					else
					{
						SetMoveLeft();
						m.pos.x += m.dirX * m.speed;//移動処理
						block[mapY][mapX].pass += 1;
						Rotation();
					}
				}

			}

		}
	}
		
}
void Map::Road4()//曲線の道の時
{
	if (map[mapY][mapX] == 3)
	{

		if (phase == 0)//上から真ん中
		{

			// 縦移動
			m.pos.y += m.dirY * m.speed;
			footY = m.pos.y + 64;

			if (footY >= senterY)//上から真ん中についたら
			{
				if (block[mapY][mapX].RotationCount == 0)//Lの時
				{
					SetMoveRight();
					m.pos.x += m.dirX * m.speed;
					phase = 1;	//次の動きに
				}
				if (block[mapY][mapX].RotationCount == 3)//」の時
				{
					SetMoveLeft();
					m.pos.x += m.dirX * m.speed;
					phase = 4;	//次の動きに
				}


			}
		}
		if (phase == 1)//真ん中から右
		{
			// 横移動
			m.pos.x += m.dirX * m.speed;
			footX = m.pos.x + 32;
			
			if (footX >= right)
			{
				if (CanMoveRight())
				{
					right += 1;

					// 次のマスが曲線なら
					if (map[mapY][rightmapX] == 3)
					{
						phase = 5;
					}
				}
				else
				{
					block[mapY][mapX].pass += 1;
					Rotation();

					SetMoveLeft();
					m.pos.x += m.dirX * m.speed;
					phase = 2;
				}
			}
		}
		if (phase == 2)	//右から真ん中
		{

			m.pos.x += m.dirX * m.speed;
			footX = m.pos.x + 32;
			
			if (footX <= senterX) //真ん中についたら 
			{

				if (block[mapY][mapX].RotationCount == 0)//Lの時
				{
					SetMoveUp();
					m.pos.y += m.dirY * m.speed;
					phase = 3;		//次の動き
				}
				if (block[mapY][mapX].RotationCount == 1)//「の時
				{
					SetMoveDown();
					m.pos.y += m.dirY * m.speed;
					phase = 7;		//次の動き
				}
			}
		}
		if (phase == 3)	//真ん中から上
		{

			m.pos.y += m.dirY * m.speed;
			footY = m.pos.y + 64;
			if (footY <= top) //上についたら 
			{
				
				if (CanMoveUp())
				{
					top -= 1;
					if (map[upmapY][mapX] == 3)
					{
						phase = 6;
					}
				}
				else
				{

					block[mapY][mapX].pass += 1;
					Rotation();

					SetMoveDown();
					m.pos.y += m.dirY * m.speed;//移動処理 
					phase = 0;//ループ
					
				}
			}
			
		}
		if (phase == 4)//真ん中から左
		{
			// 横移動
			m.pos.x += m.dirX * m.speed;
			footX = m.pos.x + 32;
			
			if (footX <= left)//左端についたら
			{
				if (CanMoveLeft())
				{
					left -= 1;
					if (map[mapY][leftmapX] == 3)
					{
						phase = 2;
					}
				}
				else
				{
					block[mapY][mapX].pass += 1;
					Rotation();
					
					SetMoveRight();
						m.pos.x += m.dirX * m.speed;
						phase = 5;	//次の動き
				}
			}

		}
		if (phase == 5)	//左から真ん中
		{


			m.pos.x += m.dirX * m.speed;
			footX = m.pos.x + 32;
		
			if (footX >= senterX) //真ん中についたら 
			{
				if (block[mapY][mapX].RotationCount == 2)//7の時
				{
					SetMoveDown();
					m.pos.y += m.dirY * m.speed;
					phase = 7;		//次の動き
				}
				if (block[mapY][mapX].RotationCount == 3)//」の時
				{
					SetMoveUp();
					m.pos.y += m.dirY * m.speed;
					phase = 3;		//次の動き
				}
			}
		}
		if (phase == 6)	//下から真ん中
		{


			m.pos.y += m.dirY * m.speed;
			footY = m.pos.y + 64;
			if (footY <= senterY) //真ん中についたら 
			{

				if (block[mapY][mapX].RotationCount == 1)//「の時
				{
					SetMoveRight();
					m.pos.y += m.dirY * m.speed;
					phase = 1;		//次の動き
				}
				if (block[mapY][mapX].RotationCount == 2)//7の時
				{
					SetMoveLeft();
					m.pos.y += m.dirY * m.speed;
					phase = 4;		//次の動き
				}

			}
		}
		if (phase == 7)	//真ん中から下
		{


			m.pos.y += m.dirY * m.speed;
			footY = m.pos.y + 64;
			if (footY >= bottom) //下についたら 
			{
				if (CanMoveDown())
				{
					bottom += 1;
					if (map[downmapY][mapX] == 3)
					{
						phase = 0;
					}
					
				}
				else
				{
					block[mapY][mapX].pass += 1;
					Rotation();
					SetMoveUp();
					m.pos.y += m.dirY * m.speed;
					phase = 6;		//次の動き
					
				}



			}
		}
	}
}

void Map::Rotation()//回転させる関数
{
	if (block[mapY][mapX].pass % 2 == 0 &&
		Rotationcheck == false && block[mapY][mapX].pass != 0)
	{
		// 偶数かつ回っていなければ（Rotationcheckがfalseのとき）
		Rotationcheck = true;
		block[mapY][mapX].nowangle = block[mapY][mapX].angle + 90;
	}
	else if (block[mapY][mapX].pass % 2 != 0 &&
		Rotationcheck == true && block[mapY][mapX].pass != 0)
	{
		// 奇数かつすでに回ってるのであれば（Rotationcheckがtrueのとき）
		Rotationcheck = false;
	}

	// 偶数になった瞬間だけ回転させる
	if (Rotationcheck &&
		block[mapY][mapX].nowangle != block[mapY][mapX].angle)
	{
		block[mapY][mapX].angle = block[mapY][mapX].nowangle;

		int nextRot = (block[mapY][mapX].angle / 90) % 4;

		// 縦になった
		if (nextRot % 2 == 0)
		{
			if (m.dirX == -1)
			{
				SetMoveUp();
			}
			else if (m.dirX == 1)
			{
				SetMoveDown();
			}
		}
		// 横になった
		else
		{
			if (m.dirY == -1)
			{
				SetMoveLeft();
			}
			else if (m.dirY == 1)
			{
				SetMoveRight();
			}
		}
	}
}

bool Map::CanMoveUp()
{
	if (upmapY < 0) return false;

	// 直線
	if (map[upmapY][mapX] == 2 &&
		block[upmapY][mapX].RotationCount % 2 == 0)
	{
		return true;
	}

	// 曲線
	if (map[upmapY][mapX] == 3)
	{
		int rot = block[upmapY][mapX].RotationCount;

		if (rot == 1 || rot == 2)
			return true;
	}

	return false;
}
bool Map::CanMoveDown()
{
	if (downmapY >= STAGE_Y) return false;

	if (map[downmapY][mapX] == 2 &&
		block[downmapY][mapX].RotationCount % 2 == 0)
	{
		return true;
	}

	if (map[downmapY][mapX] == 3)
	{
		int rot = block[downmapY][mapX].RotationCount;

		if (rot == 0 || rot == 3)
			return true;
	}

	return false;
}
bool Map::CanMoveLeft()
{
	if (leftmapX < 0) return false;

	if (map[mapY][leftmapX] == 2 &&
		block[mapY][leftmapX].RotationCount % 2 == 1)
	{
		return true;
	}

	if (map[mapY][leftmapX] == 3)
	{
		int rot = block[mapY][leftmapX].RotationCount;

		if (rot == 0 || rot == 1)
			return true;
	}

	return false;
}
bool Map::CanMoveRight()
{
	if (rightmapX >= STAGE_X) return false;

	if (map[mapY][rightmapX] == 2 &&
		block[mapY][rightmapX].RotationCount % 2 == 1)
	{
		return true;
	}

	if (map[mapY][rightmapX] == 3)
	{
		int rot = block[mapY][rightmapX].RotationCount;

		if (rot == 2 || rot == 3)
			return true;
	}

	return false;
}
void Map::SetMoveRight()
{
	m.dirX = 1;
	m.dirY = 0;
}

void Map::SetMoveLeft()
{
	m.dirX = -1;
	m.dirY = 0;
}

void Map::SetMoveUp()
{
	m.dirX = 0;
	m.dirY = -1;
}

void Map::SetMoveDown()
{
	m.dirX = 0;
	m.dirY = 1;
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
	for (int i = 0;i < STAGE_Y;i++) {				//ブロック描画
		for (int j = 0;j < STAGE_X;j++) {
			posX = j * chipSize + X + MapCenter;
			posY = i * chipSize + Y + MapCenter;
			switch (map[i][j]) {
				//通後不可
			case 1:
				sprite_render(sprmap1,
					posX, posY,
					2, 2,
					0, 0,
					64, 64,
					32, 32,
					DegToRad(block[i][j].angle),
					1, 1, 1
				);
				break;
				//直線
			case 2:
				sprite_render(sprmap2,
					posX, posY,
					2, 2,
					0, 0,
					64, 64,
					32, 32,
					DegToRad(block[i][j].angle),
					1, 1, 1
				);
				break;
				//曲線
			case 3:
				sprite_render(sprmap3,
					posX, posY,
					2, 2,
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
					2, 2,
					0, 0,
					64,64,
					32, 32,
					DegToRad(block[i][j].angle),
					1, 1, 1
				);
				break;
			}

			// Debug表示
			std::stringstream tmp;
			tmp << block[i][j].angle;

			text_out(
				0,
				tmp.str(),
				posX, posY,
				1.5f, 1.5f,
				1, 0, 1, 1);
		}
	}

	//キャラの絵
	int sx = m.frame * CHARACTER_TEX_W;
	int sy = m.direction *  CHARACTER_TEX_H;

	if (spr_Character == nullptr) return;

	sprite_render(spr_Character, m.pos.x , m.pos.y, 1, 1,
		sx, sy, CHARACTER_TEX_W, CHARACTER_TEX_H);

	
	

	debug::display(1,0,1,2,2); // ← 最後に描く
}