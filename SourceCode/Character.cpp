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
	posX = 200;
	posY = 200;
	speed = 50.0f;
	direction = 0; // 0:下 1:左 2:右 3:上
	moveTimer = 0.0f;
	vx = 0;
	vy = 0;

	spr_Character = sprite_load(L"./Data/Images/Character_kari.png");

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

	if (moveTimer > 1.0f) //1秒ごとに方向変える（仮）
	{
		int r = rand() % 4;

		switch (r)
		{
		case 0: vx = 1; vy = 0; direction = 1; break; //左
		case 1: vx = -1; vy = 0; direction = 2; break; // 右
		case 2: vx = 0; vy = 1; direction = 0; break; // 下
		case 3: vx = 0; vy = -1; direction = 3; break; // 上
		}

		moveTimer = 0;
	}

	// 移動
	posX += vx * speed * (1.0f / 60.0f);
	posY += vy * speed * (1.0f / 60.0f);


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
	int sy = direction * frameHeight;

	sprite_render(spr_Character,posX, posY, 2, 2,
		sx, sy, frameWidth, frameHeight);

	if (spr_Character == nullptr) return;
}