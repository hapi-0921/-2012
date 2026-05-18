#include "../GameLib/game_lib.h"
#include "player.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "Mapchip.h"


int player_timer;
static bool prevMouseLeft;

static int cursorRow = 0;
static int cursorCol = 0;

static bool isSelecting = false;
static int selectRow = 0;
static int selectCol = 0;

Player::Player()
{

	spr_Character = sprite_load(L"./Data/Images/Player_1.png");

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

bool Player::GameUpdate(Map& mapchip)
{
	player_timer++;

	CursorPos pos = getCursorpos();

	const int CELLSIZE = 100;

	cursorCol = (pos.x+X) / CELLSIZE;
	cursorRow = (pos.y+Y) / CELLSIZE;

	if (cursorRow < 0 || cursorRow >= 8) return false;
	if (cursorCol < 0 || cursorCol >= 8) return false;

	bool mouseLeft = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	bool mouseClick = (!prevMouseLeft && mouseLeft && player_timer > 30);

	prevMouseLeft = mouseLeft;

	if (mouseClick)
	{
		if (!isSelecting)
		{
			selectRow = cursorRow;
			selectCol = cursorCol;
			isSelecting = true;
		}
		else
		{
			if (cursorRow == selectRow && cursorCol == selectCol)
			{
				isSelecting = false;
				return true;
			}

			int dr = abs(cursorRow - selectRow);
			int dc = abs(cursorCol - selectCol);

			if (dr + dc == 1)
			{
				std::swap(mapchip.map[selectRow][selectCol], 
						  mapchip.map[cursorRow][cursorCol]);
			}

			isSelecting = false;
		}
	}

	return mouseClick;
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