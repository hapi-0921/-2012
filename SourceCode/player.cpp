#include "../GameLib/game_lib.h"
#include "player.h"
#include "SceneTitle.h"


int player_timer;
static bool prevMouseLeft;


Player::Player()
{

	spr_Character = sprite_load(L"./Data/Images/Character_kari.png");

	 cursorX = 0;
	 cursorY = 0;

	 GetcursorIndex = 0;
	 decided = false;

	 player_timer = 0;

	 prevMouseLeft = true;

}

Player::~Player()
{
	safe_delete(spr_Character);
}

CursorPos Player::getCursorpos()
{
	 cursorX = getCursorPosX();
	 cursorY = getCursorPosY();
	
	 return{ cursorX,cursorY };
}

bool Player::IsHovered(Button button, float mouseX, float mouseY)
{
	return mouseX >= button.x && mouseX <= button.x + button.width &&
		 mouseY >= button.y && mouseY <= button.y + button.height;
}

bool Player::MenuUpdate()
{
	player_timer++;

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

	CursorPos pos = getCursorpos();

	if (TRG(0)&PAD_DOWN) GetcursorIndex++;
	if (TRG(0)&PAD_UP) GetcursorIndex--;
	
	

	bool mouseLeft = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	bool mouseClick = (!prevMouseLeft && mouseLeft && player_timer > 30);

	

	prevMouseLeft = mouseLeft;


	return mouseClick;

}

void Player::Draw()
{
	int frameWidth = PLAYER_TEX_W ;
	int frameHeight = PLAYER_TEX_H ;

	int sx = frame * frameWidth;
	int sy = direction * frameHeight;

	sprite_render(spr_Character,posX, posY, 2, 2,
		sx, sy, frameWidth, frameHeight);
}



void Player::reset()
{
	prevMouseLeft = true;
	decided = false;
}

bool Player::IsDecided()
{
	return decided;
}

int Player::GetCursorIndex()
{
	return GetcursorIndex;
}