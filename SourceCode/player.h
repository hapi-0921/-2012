#pragma once
#ifndef PLAYER_H
#define PLAYER_H

struct CursorPos
{
	int x;
	int y;
};

class Player
{
private:
	int cursorX;
	int cursorY;

public:
	Player();
	~Player();
	void player_update();
	void player_render();

	CursorPos getCursorpos();
};
#endif //PLAYER_H