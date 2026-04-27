#include "../GameLib/game_lib.h"
#include "player.h"
#include "SceneTitle.h"


Button startButton = { 300,200,200,50,0 };
Button howtoButton = { 300,280,200,50,1 };

int player_timer;
static bool prevMouseLeft;

Player::Player()
{
	 cursorX = 0;
	 cursorY = 0;

	 cursorIndex = 0;
	 decided = false;

	 player_timer = 0;
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

void Player::MenuUpdate()
{
	player_timer++;

	CursorPos pos = getCursorpos();

	if (TRG(0)&PAD_DOWN) cursorIndex++;
	if (TRG(0)&PAD_UP) cursorIndex--;
	
	if (cursorIndex < 0)cursorIndex = startButton.index;
	if (cursorIndex > 1)cursorIndex = howtoButton.index;
	if (IsHovered(startButton, pos.x, pos.y)) cursorIndex = startButton.index;
	if (IsHovered(howtoButton, pos.x, pos.y)) cursorIndex = howtoButton.index;

	bool mouseLeft = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	bool mouseClick = (!prevMouseLeft && mouseLeft && player_timer > 30);

	if ((TRG(0) & PAD_START) || mouseClick)
	{
		decided = true;
	}

	prevMouseLeft = mouseLeft;
}

bool Player::IsDecided()
{
	return decided;
}

int Player::GetCursorIndex()
{
	return cursorIndex;
}