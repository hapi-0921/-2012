#include "player.h"
#include "../GameLib/game_lib.h"

Player::Player()
{
	 cursorX = 0;
	 cursorY = 0;
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

void Player::player_update()
{

}

void Player::player_render()
{

}