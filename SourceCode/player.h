#pragma once
#ifndef PLAYER_H
#define PLAYER_H



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

public:
	Player();
	~Player();

	

	bool IsHovered(Button button, float mouseX, float mouseY);

	bool prevMouseLeft;

	int GetCursorIndex();
	bool decided;
	bool IsDecided();

	bool MenuUpdate();

	void reset();

	CursorPos getCursorpos();
};
#endif //PLAYER_H