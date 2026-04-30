#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_SIZE	64
#define PLAYER_TEX_W            (64.0f)    // プレイヤーの画像1つの幅
#define PLAYER_TEX_H            (64.0f)    // プレイヤーの画像1つの高さ
#define PLAYER_PIVOT_X          (32.0f)     // プレイヤーの横方向の中心
#define PLAYER_PIVOT_Y          (64.0f)    // プレイヤーの縦方向の下端

#define PLAYER_SPEED_MAX      (8.0f)      // プレイヤーの速度の最大値

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

	//アニメーション


	int frame = 0;
	float animTimer = 0.0f;
	float posX = 200;
	float posY = 200;
	float speed = 50.0f;
	int direction = 0; // 0:下 1:左 2:右 3:上
	float moveTimer = 0.0f;
	float vx = 0;
	float vy = 0;

public:
	Player();
	~Player();

	

	bool IsHovered(Button button, float mouseX, float mouseY);

	bool prevMouseLeft;

	int GetCursorIndex();
	bool decided;
	bool IsDecided();

	bool MenuUpdate();

	void Draw();

	void reset();

	CursorPos getCursorpos();
};
#endif //PLAYER_H