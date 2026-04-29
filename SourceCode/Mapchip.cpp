#include"Mapchip.h"
Mapchip::Mapchip()
{
	sprmap1	= sprite_load(L"./Data/Images/mapchip1.png");
	sprmap2	= sprite_load(L"./Data/Images/mapchip2.png");
	sprmap3	= sprite_load(L"./Data/Images/mapchip3.png");
	sprmap4	= sprite_load(L"./Data/Images/mapchip4.png");
}
Mapchip::~Mapchip()
{

}
void Mapchip::Render()
{
	for (int i = 0;i < STAGE_Y;i++) {
		for (int j = 0;j < STAGE_X;j++) {
			float posX = j * chipSize;
			float posY = i * chipSize;
			switch (map[i][j]) {
				
			case 1:
				  sprite_render(sprmap1,
					  posX, posY,
					1, 1,
					0, 0,
					128, 128,
					0, 0,
					0,
					1, 1, 1
				);
				break;
				//経験値
			case 2:
				sprite_render(sprmap2,
					posX, posY,
					1, 1,
					0, 0,
					128, 128,
					0, 0,
					0,
					1, 1, 1
				);
				break;
				//アイテム
			case 3:
				sprite_render(sprmap3,
					posX, posY,
					1, 1,
					0, 0,
					128, 128,
					0, 0,
					0,
					1, 1, 1
				);
				break;
				//ダメージ
			case 4:
				sprite_render(sprmap4,
					posX, posY,
					1, 1,
					0, 0,
					128, 128,
					0, 0,
					0,
					1, 1, 1
				);
				break;
			}
		}
	}
	
}