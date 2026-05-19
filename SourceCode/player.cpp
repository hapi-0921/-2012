#include "../GameLib/game_lib.h"
#include "player.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "Mapchip.h"


int player_timer;

static bool prevMouseLeft;
static bool prevMouseX = 0;
static bool prevMouseY = 0;

//カーソル現在地
static int cursorRow = 0;
static int cursorCol = 0;

static bool isSelecting = false;

//最初に選択したマス
static int selectRow = 0;
static int selectCol = 0;


Player::Player()
{

	//spr_Character = sprite_load(L"./Data/Images/Player_1.png");

	cursorX = 0;
	cursorY = 0;

	 //メニュー用カーソル番号
	 GetcursorIndex = 0;

	 decided = false;
	//メニュー用カーソル番号
	GetcursorIndex = 0;

	decided = false;

	 prevMouseLeft = true;
	 useKeyboard = false;//操作方法

	player_timer = 0;

	prevMouseLeft = true;
	useKeyboard = false;//操作方法

}

Player::~Player()
{

}

//マウスの位置情報取得
CursorPos Player::getCursorpos()
{
	cursorX = getCursorPosX();
	cursorY = getCursorPosY();

	return{ cursorX,cursorY };
}

//ボタン上にマウスがあるかどうか
bool Player::IsHovered(Button button, float mouseX, float mouseY)
{
	return mouseX >= button.x && mouseX <= button.x + button.width &&
		mouseY >= button.y && mouseY <= button.y + button.height;
}

//メニュー画面(titleやresultで使う用)
bool Player::MenuUpdate(int menuMax)
{
	player_timer++;

	CursorPos pos = getCursorpos();

	//上下入力
	if (TRG(0) & PAD_LEFT || TRG(0) & PAD_UP) GetcursorIndex--;
	if (TRG(0) & PAD_RIGHT || TRG(0) & PAD_DOWN) GetcursorIndex++;

	if (GetcursorIndex < 0) GetcursorIndex = menuMax - 1;
	if (GetcursorIndex > menuMax - 1) GetcursorIndex = 0;
	
	//クリック取得、連続入力ならないように
	bool mouseLeft = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	bool mouseClick = (!prevMouseLeft && mouseLeft && player_timer > 30);	

	prevMouseLeft = mouseLeft;


	return mouseClick;

}

//ゲーム用
bool Player::GameUpdate(Map& mapchip)
{
	player_timer++;

	CursorPos pos = getCursorpos();

	//マスのサイズ

	const int CELLSIZE = 128;

	//操作方法の切り替え
	bool KeyInput = TRG(0) & PAD_LEFT || TRG(0) & PAD_RIGHT || TRG(0) & PAD_UP || TRG(0) & PAD_DOWN;

	bool mouseLeft = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	bool mouseClick = (!prevMouseLeft && mouseLeft && player_timer > 30);

	//キーボード操作に切り替え
	if (KeyInput)
	{
		useKeyboard = true;
	}

	//マウス操作に切り替え
	if (mouseClick)
	{
		useKeyboard = false;
	}

	if (useKeyboard)
	{
		if (TRG(0) & PAD_LEFT) cursorCol--;
		if (TRG(0) & PAD_RIGHT) cursorCol++;
		if (TRG(0) & PAD_UP) cursorRow--;
		if (TRG(0) & PAD_DOWN) cursorRow++;
	}
	else
	{
		cursorCol = (pos.x - X) / CELLSIZE;
		cursorRow = (pos.y - Y) / CELLSIZE;
	}

	//範囲外
	if (cursorRow < 0) cursorRow = 0;
	if (cursorRow > 7) cursorRow = 7;

	if (cursorCol < 0) cursorCol = 0;
	if (cursorCol > 12) cursorCol = 12;

	//前フレームの保存
	prevMouseLeft = mouseLeft;

	prevMouseX = pos.x;
	prevMouseY = pos.y;

	//クリック時

	if (mouseClick || TRG(0) & PAD_START) 
	if (mouseClick || TRG(0) & PAD_START)

	{
		music::play(3);
		//未選択
		if (!isSelecting)
		{
			//一個目選択
			selectRow = cursorRow;
			
			selectCol = cursorCol;

			

			isSelecting = true;
		}
		else
		{
			//同じ場所クリックでキャンセル
			if (cursorRow == selectRow && cursorCol == selectCol)
			{
				isSelecting = false;
				return true;
			}

			int dr = abs(cursorRow - selectRow);
			int dc = abs(cursorCol - selectCol);
			
			//上下左右なら入れ替え
			if (dr + dc == 1)
			{
<<<<<<< HEAD

				if ((selectRow == mapchip.infon.mapY && selectCol == mapchip.infon.mapX) ||
					(cursorRow == mapchip.infon.mapY && cursorCol == mapchip.infon.mapX))

				
=======
				//mobの位置取得
				int mobCol = (mapchip.m.move.pos.x + 32 - X) / CELLSIZE;
				int mobRow = (mapchip.m.move.pos.y + 64 - Y) / CELLSIZE;
				if ((selectRow == mapchip.infon.mapY && selectCol == mapchip.infon.mapX) ||
					(cursorRow == mapchip.infon.mapY && cursorCol == mapchip.infon.mapX))
				
				

				// mobがいるマスは動かせない
				if ((selectRow == mobRow && selectCol == mobCol) ||
					(cursorRow == mobRow && cursorCol == mobCol))
>>>>>>> fb6b1efc7c9ab129d8a5e2045412b2fd045421f2
				{
					isSelecting = false;
					return false;
				}

				//mobcarの位置取得
				int carCol = (mapchip.c.move.pos.x + 32 - X) / CELLSIZE;
				int carRow = (mapchip.c.move.pos.y + 64 - Y) / CELLSIZE;

				if ((selectRow == carRow && selectCol == carCol) ||
					(cursorRow == carRow && cursorCol == carCol))
				{
					isSelecting = false;
					return false;
				}

				// 動かせない特殊マス
				int selectType = mapchip.map[selectRow][selectCol];
				int cursorType = mapchip.map[cursorRow][cursorCol];

				// house(5) piano(6) school(7) は移動禁止
				if ((selectType >= 5 && selectType <= 7) ||
					(cursorType >= 5 && cursorType <= 7))
				{
					isSelecting = false;
					return false;
				}

				music::play(4);

				std::swap(mapchip.map[selectRow][selectCol],
						  mapchip.map[cursorRow][cursorCol]);

				std::swap(mapchip.block[selectRow][selectCol],
					mapchip.block[cursorRow][cursorCol]);
			}
			//選択解除
			isSelecting = false;
		}
	}

	return mouseClick;
}

//状態リセット
void Player::reset()
{
	prevMouseLeft = true;
	decided = false;
}


//決定状態取得
bool Player::IsDecided()
{
	return decided;
}

//メニューカーソル番号取得
int Player::GetCursorIndex()
{
	return GetcursorIndex;
}


bool Player::GetSelecting()
{
	return isSelecting;
}

int Player::GetSelectingRow()
{
	return selectRow;
}

int Player::GetSelectingCol()
{
	return selectCol;
}

int Player::GetCursorRow()
{
	return cursorRow;
}

int Player::GetCursorCol()
{
	return cursorCol;
}

bool Player::isKeyboardMode()
{
	return useKeyboard;
}