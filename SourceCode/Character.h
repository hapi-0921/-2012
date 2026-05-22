#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_SIZE	64
#define CHARACTER_TEX_W            (64.0f)    // プレイヤーの画像1つの幅
#define CHARACTER_TEX_H            (64.0f)    // プレイヤーの画像1つの高さ
#define CHARACTER_PIVOT_X          (32.0f)     // プレイヤーの横方向の中心
#define CHARACTER_PIVOT_Y          (64.0f)    // プレイヤーの縦方向の下端

#define PCHARACTER_SPEED_MAX      (8.0f)      // プレイヤーの速度の最大値


class Character
{
private:
	Sprite* spr_Character;
	
	//アニメーション
	int frame;
	float animTimer;
	float posX;
	float posY;
	float speed;
	int direction; // 0:下 1:左 2:右 3:上
	float moveTimer;
	float vx;
	float vy;
	


public:
	Character();
	~Character();

	void Move();
	void Draw();
	

};


#endif //CHARACTER_H