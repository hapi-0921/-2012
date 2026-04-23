#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
	float cursorX;
	float cursorY;

public:
	Player();
	~Player();
	void player_update();
	void player_render();

	void getCursorpos(float x,float y);
};
#endif //PLAYER_H