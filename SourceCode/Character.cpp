#include "../GameLib/game_lib.h"
#include "Character.h"
#include "player.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "Mapchip.h"

Character::Character()
{
	frame = 0;
	animTimer = 0.0f;
	posX = 830;
	posY = 540;
	speed = 50.0f;
	direction = 0; // 0:下 1:左 2:右 3:上
	moveTimer = 0.0f;
	vx = 0;
	vy = 0;

	spr_Character = sprite_load(L"./Data/Images/Player_1.png");

	

	if (spr_Character == nullptr)
	{
		printf("画像ロード失敗\n");
	}
}

Character::~Character()
{
	safe_delete(spr_Character);

	

}

void Character::Move()
{
	moveTimer += 1.0f / 60.0f;

	

	


	//アニメーション
	animTimer += 1.0f / 60.0f;

	if (animTimer >= 0.2f)
	{
		frame++;
		if (frame >= 4) frame = 0;
		animTimer = 0;
	}

}

void Character::Draw()
{
	int frameWidth = CHARACTER_TEX_W ;
	int frameHeight = CHARACTER_TEX_H ;

	int sx = frame * frameWidth;
	int sy = 0;

	sprite_render(spr_Character,posX, posY, 4, 4,
		sx, sy, frameWidth, frameHeight);

	if (spr_Character == nullptr) return;
}

