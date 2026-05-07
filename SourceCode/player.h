#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Mapchip.h"

struct CursorPos
{
	int x;
	int y;
};

struct Button
{
	float x;
	float y;
	float width;
	float height;
	int index;
};

class Player
{
private:
	int cursorX;
	int cursorY;
	int GetcursorIndex;

	Sprite* spr_Character;


public:
	Player();
	~Player();

	bool IsHovered(Button button, float mouseX, float mouseY);

	bool prevMouseLeft;

	int GetCursorIndex();
	bool decided;
	bool IsDecided();

	bool MenuUpdate();
	bool GameUpdate(Map& mapchip);

	void reset();

	CursorPos getCursorpos();

	Map mapchip;
};
#endif //PLAYER_H