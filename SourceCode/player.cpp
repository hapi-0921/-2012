#include "../GameLib/game_lib.h"
#include "player.h"
#include "SceneTitle.h"


int player_timer;
static bool prevMouseLeft;


Player::Player()
{
	 cursorX = 0;
	 cursorY = 0;

	 GetcursorIndex = 0;
	 decided = false;

	 player_timer = 0;

	 prevMouseLeft = true;

}

Player::~Player()
{

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

	CursorPos pos = getCursorpos();

	if (TRG(0)&PAD_DOWN) GetcursorIndex++;
	if (TRG(0)&PAD_UP) GetcursorIndex--;
	
	

	bool mouseLeft = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	bool mouseClick = (!prevMouseLeft && mouseLeft && player_timer > 30);

	

	prevMouseLeft = mouseLeft;


	return mouseClick;

}

void Player::reset()
{
	prevMouseLeft = true;
	decided = false;
};

bool Player::IsDecided()
{
	return decided;
}

int Player::GetCursorIndex()
{
	return GetcursorIndex;
}