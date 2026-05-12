#include"Mapchip.h"
#include <sstream>
Map::Map()
{
	//出来てないところ
	//角度が内部は変わってるけど見た目は変わってない
	//基準点が００だから


	frame = 0;
	animTimer = 0.0f;
	direction = 0; // 0:下 1:右 2:左 3:上

	
	moveTimer = 0.0f;
	vx = 0;
	vy = 0;


	sprmap1	= sprite_load(L"./Data/Images/mapchip1.png");
	sprmap2	= sprite_load(L"./Data/Images/mapchip2.png");
	sprmap3	= sprite_load(L"./Data/Images/mapchip3.png");
	sprmap4	= sprite_load(L"./Data/Images/mapchip4.png");
	spr_Character = sprite_load(L"./Data/Images/Player_1.png");
	sprfield= sprite_load(L"./Data/Images/field.png");
	/*block[0][0].angle = 90;
	block[0][1].angle = 180;
	block[1][0].angle = 0;
	block[1][1].angle = 270;
	block[1][3].angle = 0;
	block[2][3].angle = 270;
	block[2][2].angle = 0;
	block[1][2].angle = 180;*/
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

	Move();
	Road();

	debug::setString("phase:%d", phase);
	debug::setString("map:%d x:%f y:%f topY:%f\n", map[mapY][mapX], m.pos.x, m.pos.y, top);
	debug::setString("leftmapX = %d\n", leftmapX);
	debug::setString("m.dirY:%d", m.dirY);
	debug::setString("Left:%f", left);
	debug::setString("Right:%f", right);



	if (m.dirX == 1)
	{
		direction = 1; // 右
	}
	else if (m.dirX == -1)
	{
		direction = 2; // 左
	}
	else if (m.dirY == 1)
	{
		direction = 0; // 下
	}
	else if (m.dirY == -1)
	{
		direction = 3; // 上
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
	// mobの画面座標 → マップ座標へ変換
	//---------------------------------

	localX = m.pos.x - X;
	localY = m.pos.y - Y;

	//---------------------------------
	// 今いるマス
	//---------------------------------

	mapX = localX / chipSize;
	mapY = localY / chipSize;
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

	// 移動
	m.pos.x += vx * m.speed * (1.0f / 60.0f);
	m.pos.y += vy * m.speed * (1.0f / 60.0f);

	//アニメーション
	animTimer += 1.0f / 60.0f;

	if (animTimer >= 0.2f)
	{
		frame++;
		if (frame >= 4) frame = 0;
		animTimer = 0;
	}



	if (mapX < 0 || mapX >= STAGE_X ||
		mapY < 0 || mapY >= STAGE_Y)
		return;

	if (block[mapY][mapX].pass % 2 == 0 &&
		Rotationcheck == false)
	{
		// 偶数かつ回っていなければ（Rotationcheckがfalseのとき）
		Rotationcheck = true;
		block[mapY][mapX].nowangle = block[mapY][mapX].angle + 90;
	}
	else if (block[mapY][mapX].pass % 2 != 0 &&
			 Rotationcheck == true)
	{
		// 奇数かつすでに回ってるのであれば（Rotationcheckがtrueのとき）
		Rotationcheck = false;
	}

	// 偶数になった瞬間だけ回転させる
	if (Rotationcheck &&
		block[mapY][mapX].nowangle != block[mapY][mapX].angle)
	{
		//block[mapY][mapX].angle = block[mapY][mapX].nowangle+90;
		block[mapY][mapX].angle = block[mapY][mapX].nowangle;
		//Rotationcheck = false;
	}
	Road2();
	Road4();
	
}
void Map::Road2()//直線の道の時
{
	if (map[mapY][mapX] == 2)//今のブロックが直線
	{
		Road3();
		
		if (block[mapY][mapX].RotationCount % 2 == 0)//縦向きの道の時
		{
			
			m.pos.y += m.dirY * m.speed;//移動処理
			
			if (m.dirY==-1)
			{
				Road7();
			}
				if (m.pos.y-64<= top && blocheck == false)		//今いるブロックの上端についたら
				{
					m.dirY = 1;					//下に引き返す
					m.pos.y += m.dirY * m.speed;//移動処理
					block[mapY][mapX].pass += 1;
				}
			
			
			// 下端
				if (m.dirY==1)
				{
					Road6();
				}
				if (m.pos.y >= bottom && blocheck == false)			//今いるブロックの下端についたら
				{
					m.dirY = -1;				//上に引き返す
					m.pos.y += m.dirY * m.speed;//移動処理
					block[mapY][mapX].pass += 1;
				}

		}
		if (block[mapY][mapX].RotationCount % 2 == 1)//横向きの道
		{
			Road8();
			Road9();
			m.pos.x += m.dirX * m.speed;//移動処理
			

			if (m.pos.x <= left && blocheck == false)		//今いるブロックの左端についたら
			{
				
				m.dirX = 1;			//右に引き返す
				m.pos.x += m.dirX * m.speed;//移動処理
				block[mapY][mapX].pass += 1;
			}

			if (m.pos.x >= right && blocheck == false)	//今いるブロックの右端についたら
			{
				
				m.dirX = -1;		//左に引き返す
				m.pos.x += m.dirX * m.speed;//移動処理
				block[mapY][mapX].pass += 1;
			}
		}
	}
		
}
void Map::Road3()//次の道が直線の時
{
	if (upmapY >= 0 && map[upmapY][mapX] == 2 && block[upmapY][mapX].RotationCount % 2 == 0)
	{
		top -= chipSize;
		blocheck = true;
	}
	if (downmapY < STAGE_Y && map[downmapY][mapX] == 2 && block[downmapY][mapX].RotationCount % 2 == 0)
	{
		bottom += chipSize;
		blocheck = true;
	}
	if (rightmapX<STAGE_X&&map[mapY][rightmapX] == 2 && block[mapY][rightmapX].RotationCount % 2 == 1)
	{
		right += chipSize;
		blocheck = true;
	}
	if (leftmapX>=0&&map[mapY][leftmapX] == 2 && block[mapY][leftmapX].RotationCount % 2 == 1)
	{
		left -= chipSize;
		blocheck = true;
	}
}
void Map::Road4()//曲線の道の時
{
	if (map[mapY][mapX] == 3 )
	{
		

		Road3();
		
		if (phase == 0)//上から真ん中
		{

			// 縦移動
			m.pos.y += m.dirY * m.speed;

			
			if (m.pos.y >= senterY)//上から真ん中についたら
			{
				if (block[mapY][mapX].RotationCount == 0)//Lの時
				{
					m.dirY = 0;	//ｙ止める
					m.dirX = 1; // 右へ
					m.pos.x += m.dirX * m.speed;
					phase = 1;	//次の動きに
				}
				if (block[mapY][mapX].RotationCount == 3)//」の時
				{
					m.dirY = 0;	//ｙ止める
					m.dirX = -1; // 左へ
					m.pos.x += m.dirX * m.speed;
					phase = 4;	//次の動きに
				}
				

			}
		}
		else if (phase == 1)//真ん中から右
		{
		


			// 横移動
			m.pos.x += m.dirX * m.speed;

			if (m.pos.x >= right)//右端についたら
			{
				Road9();//曲線の左から右に行けるやつ
				if (blocheck == false)
				{
					block[mapY][mapX].pass += 1;

					if (block[mapY][mapX].RotationCount == 0)//Lの時
					{
						m.dirX = -1;	//ｘ反転	 
						m.dirY = 0;		//ｙ止める
						m.pos.x += m.dirX * m.speed;
						phase = 2;		//次の動き
					}
					if (block[mapY][mapX].RotationCount == 1)//「の時
					{
						m.dirX = -1;	//ｘ反転	 
						m.dirY = 0;		//ｙ止める
						m.pos.x += m.dirX * m.speed;
						phase = 2;		//次の動き
					}
				}

			}
		}
		else if (phase == 2)	//右から真ん中
		{
		
			m.pos.x += m.dirX * m.speed;
			if (m.pos.x <= senterX) //真ん中についたら 
			{

				if (block[mapY][mapX].RotationCount == 0)//Lの時
				{
					m.dirX = 0;		//ｘ止める
					m.dirY = -1;	//ｙ反転
					m.pos.y += m.dirY * m.speed;
					phase = 3;		//次の動き
				}
				if (block[mapY][mapX].RotationCount == 1)//「の時
				{
					m.dirX = 0;		//ｘ止める
					m.dirY = 1;	//ｙ反転
					m.pos.y += m.dirY * m.speed;
					phase = 7;		//次の動き
				}
			}
		}
		else if (phase == 3)	//真ん中から上
		{
		


			m.pos.y += m.dirY * m.speed;
			if (m.pos.y <= top) //真ん中についたら 
			{
				Road7();//曲線の下から上に行けるやつ
				if (blocheck == false)
				{
					block[mapY][mapX].pass += 1;

					if (block[mapY][mapX].RotationCount == 0)//Lの時
					{
						m.dirY = 1;		//ｙ反転
						m.pos.y += m.dirY * m.speed;//移動処理 
						phase = 0;//ループ
					}
					if (block[mapY][mapX].RotationCount == 3)//」の時
					{
						m.dirY = 1;		//ｙ反転
						m.pos.y += m.dirY * m.speed;//移動処理 
						phase = 0;	//ループ
					}
				}
			}
		}
			else if (phase == 4)//真ん中から左
			{
				
		

				// 横移動
				m.pos.x += m.dirX * m.speed;

				if (m.pos.x <= left)//左端についたら
				{
					Road8();//曲線の右から左に行けるやつ
					if (blocheck == false)
					{
						block[mapY][mapX].pass += 1;

						if (block[mapY][mapX].RotationCount == 2)//7の時
						{
							m.dirX = 1;	//ｘ反転	 
							m.dirY = 0;		//ｙ止める
							m.pos.x += m.dirX * m.speed;
							phase = 5;	//次の動き
						}
						if (block[mapY][mapX].RotationCount == 3)//」の時
						{

							m.dirX = 1;	//ｘ反転	 
							m.dirY = 0;		//ｙ止める
							m.pos.x += m.dirX * m.speed;
							phase = 5;
						}
					}

				}
			}
			else if (phase == 5)	//左から真ん中
			{
		

				m.pos.x += m.dirX * m.speed;
				if (m.pos.x >= senterX) //真ん中についたら 
				{
					if (block[mapY][mapX].RotationCount == 2)//7の時
					{
						m.dirX = 0;		//ｘ止める
						m.dirY = 1;		//ｙ反転
						m.pos.y += m.dirY * m.speed;
						phase = 7;		//次の動き
					}
					if (block[mapY][mapX].RotationCount == 3)//」の時
					{
						m.dirX = 0;		//ｘ止める
						m.dirY = -1;	//ｙ反転
						m.pos.y += m.dirY * m.speed;
						phase = 3;		//次の動き
					}
				}
			}
			else if (phase == 6)	//下から真ん中
			{
				

				m.pos.y += m.dirY * m.speed;
				if (m.pos.y <= senterY) //真ん中についたら 
				{
					
						if (block[mapY][mapX].RotationCount == 1)//「の時
						{
							m.dirX = 1;		//x反転
							m.dirY = 0;		//y止める
							m.pos.y += m.dirY * m.speed;
							phase = 1;		//次の動き
						}
						if (block[mapY][mapX].RotationCount == 2)//7の時
						{
							m.dirX = -1;		//x反転
							m.dirY = 0;		//y止める
							m.pos.y += m.dirY * m.speed;
							phase = 4;		//次の動き
						}
					
				}
			}
			else if (phase == 7)	//真ん中から下
			{
			
				
				m.pos.y += m.dirY * m.speed;
				if (m.pos.y >= bottom) //下についたら 
				{
					Road6();
					if (blocheck == false)
					{
						block[mapY][mapX].pass += 1;

						if (block[mapY][mapX].RotationCount == 1)//「の時
						{
							m.dirX = 0;		//ｘ止める
							m.dirY = -1;	//ｙ反転
							m.pos.y += m.dirY * m.speed;
							phase = 6;		//次の動き
						}
						if (block[mapY][mapX].RotationCount == 2)//7の時
						{
							m.dirX = 0;		//ｘ止める
							m.dirY = -1;	//ｙ反転
							m.pos.y += m.dirY * m.speed;
							phase = 6;		//次の動き
						}

					}
				}
			}
		}
	}

void Map::Road5()//上下左右がL字の時
{
	
}
void Map::Road6()//曲線の上から下に行けるやつ
{
	if (downmapY < STAGE_Y &&map[downmapY][mapX] == 3 && block[downmapY][mapX].RotationCount == 0)//下がL字の時
	{
		bottom += 1;
		phase = 0;
		blocheck = true;
	}
	else if (downmapY < STAGE_Y &&map[downmapY][mapX] == 3 && block[downmapY][mapX].RotationCount == 3)//下が」字の時
	{
		phase = 0;
		bottom += 1;
		blocheck = true;
	}
	else
	{
		blocheck = false;
	}
}

void Map::Road7()//曲線の下から上に行けるやつ
{

	if (upmapY >= 0 &&map[upmapY][mapX] == 3 && block[upmapY][mapX].RotationCount == 1)//上が「字の時
	{
		phase = 6;
		top -= 1;
		blocheck = true;
	}
	else if (upmapY >=0 &&map[upmapY][mapX] == 3 && block[upmapY][mapX].RotationCount == 2)//上が7字の時
	{
		phase = 6;
		top -= 1;
		blocheck = true;
	}
	else
	{
		blocheck = false;
	}

}
void Map::Road8()//曲線の右から左に行けるやつ
{
	if (leftmapX >= 0 && map[mapY][leftmapX] == 3 && block[mapY][leftmapX].RotationCount == 0)//左がL字の時
	{
		phase = 2;
		left -= 1;
		blocheck = true;
	}
	else if (leftmapX >= 0 && map[mapY][leftmapX] == 3 && block[mapY][leftmapX].RotationCount == 1)//左が「字の時
	{
		phase = 2;
		left -= 1;
		blocheck = true;
	}
	else
	{
		blocheck = false;
	}
}
void Map::Road9()//曲線の左から右に行けるやつ
{
	if (rightmapX < STAGE_X &&map[mapY][rightmapX] == 3 && block[mapY][rightmapX].RotationCount == 2)//右が7字の時
	{
		phase = 5;
		right += 1;
		blocheck = true;
	}

	else if (rightmapX < STAGE_X &&map[mapY][rightmapX] == 3 && block[mapY][rightmapX].RotationCount == 3)//右が」字の時
	{
		right += 1;
		phase = 5;
		blocheck = true;
	}
	else
	{
		blocheck = false;
	}
}
/////////////////////////////////////////////////////////////////////
void Map::SwapBlocks(const SwapData& sd)
{
	
	BlockData tmp = block[sd.curRow][sd.curCol];
	block[sd.curRow][sd.curCol].angle = block[sd.selRow][sd.selCol].angle;
	block[sd.curRow][sd.curCol].nowangle = block[sd.selRow][sd.selCol].nowangle;
	block[sd.curRow][sd.curCol].pass = block[sd.selRow][sd.selCol].pass;
	block[sd.curRow][sd.curCol].RotationCount = block[sd.selRow][sd.selCol].RotationCount;

	block[sd.selRow][sd.selCol].angle = tmp.angle;
	block[sd.selRow][sd.selCol].nowangle = tmp.nowangle;
	block[sd.selRow][sd.selCol].pass = tmp.pass;
	block[sd.selRow][sd.selCol].RotationCount = tmp.RotationCount;
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
	int sx = frame * CHARACTER_TEX_W;
	int sy = direction *  CHARACTER_TEX_H;

	if (spr_Character == nullptr) return;

	sprite_render(spr_Character, m.pos.x - 16, m.pos.y - 16, 1, 1,
		sx, sy, CHARACTER_TEX_W, CHARACTER_TEX_H);

	
	

	debug::display(1,0,1,2,2); // ← 最後に描く
}