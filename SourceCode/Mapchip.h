#pragma once
#include"../GameLib/game_lib.h"
#include <stdio.h>
#include <vector>

#define STAGE_X 12
#define STAGE_Y 7

#define MapCenter chipSize/2//マップの真ん中になる
#define MapDown	  64      //マップの下、右になる

#define X 100
#define Y 100


#define CHARACTER_TEX_W            (64.0f)    // プレイヤーの画像1つの幅
#define CHARACTER_TEX_H            (64.0f)    // プレイヤーの画像1つの高さ




class Map
{
public:
	std::vector<std::vector<int>> map; 

	
	int prevX = -1;
	float posX;
	float posY;

	int prevY = -1;
	 float chipSize = 128; // 1マスのサイズ

	bool blocheck = false;
	bool Rotationcheck = false;
	struct RoadInfo
	{
		int mapX;
		int mapY;

		float left;
		float right;
		float top;
		float bottom;

		float senterX;
		float senterY;

		int upmapY;
		int downmapY;

		int leftmapX;
		int rightmapX;

		float footX;
		float footY;

		float localX;
		float localY;
	};
	struct MoveObject
	{
		VECTOR2 pos{  };

		int dirY = 1;
		int dirX = 1;
		int speed = 1;
		int phase = 0;
		bool moving = false;
		bool canRotate = true;//車かモブか
		bool cartocollide = false;//車が壁にぶつかったか
		bool active = false;
		float carsporntimer = 0;//車がいなくなったら動くタイマー
		int frame;
		float animTimer;
		int direction; // 0:下 1:右 2:左 3:上

		float moveTimer;
		float vx;
		float vy;
	};
	struct Mob
	{
		bool hit = false;
		int hitTimer = 0;
		float knockbackX = 0;
		float knockbackY = 0;
		bool invincible = false;
		int invincibleTimer = 0;
		bool parkpoint = false;
		bool housepoint = false;
		bool pianopoint = false;
		bool tocollide = false;
		MoveObject move;
	};
	Mob m;
	bool goal = false;
	struct Car
	{
		MoveObject move;
		bool carmove = false;
		int cartimer = 0;

		int warningTimer = 0;
		bool warning = false;
		int spawnType = -1;
		int spawnIndex = -1;
	};
	Car c;
	struct BlockData
	{
		
		int nowangle;
		int angle;
		int RotationCount = 0;
		int pass = 0;
		bool rotated=false;
		bool notmove = false;
	};

	enum phase
	{
		upsenter,
		senterright,
		rightsenter,
		senterup,
		senterleft,
		leftsenter,
		downsenter,
		senterdown,
	};
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	int DangerX = 0;
	int DangerY = 0;
	int Dangerangle = 0;
	int gametimer = 0;
	bool tutorial = false;
	int scale = 0;
	RoadInfo infon = Road(m.move);

	Sprite* sprmap1;//草
	Sprite* sprmap2;//直線
	Sprite* sprnotmap2;

	Sprite* sprmap3;//曲がる
	Sprite* sprmap4;//T字
	Sprite* spr_Character;//動くやつ
	Sprite* sprfield;
	Sprite* sprCar;
	Sprite*sprmap5;
	Sprite*sprmap6;
	Sprite*sprmap7;
	Sprite* sprpass1;
	Sprite* sprpass2;
	Sprite* sprDanger;

	BlockData block[STAGE_Y][STAGE_X] = {};//ひとマスの情報
	Map();
	~Map();
	void Render();
	void Update();
	void TutorialUpdate();
	void TutorialCar();
	RoadInfo Road(MoveObject& obj);
	void Move(MoveObject& obj, RoadInfo& info);
	void Road2(MoveObject& obj ,RoadInfo& info);		   //直線の道の時
	void Road4(MoveObject& obj, RoadInfo& info);		   //曲線の道の時
	void CarMoveChack(MoveObject& obj, RoadInfo& info);
	void CarMove(MoveObject& obj, RoadInfo& info, int j,int type);
	void Rotation(MoveObject& obj, RoadInfo& info);	   //道を回転させる

	bool CanMove(MoveObject& obj,RoadInfo& info, Direction dir);

	void SetMoveUp(MoveObject& obj);	   //上の向きにセットする
	void SetMoveDown(MoveObject& obj);	   //下の向きにセットする
	void SetMoveLeft(MoveObject& obj);	   //左の向きにセットする
	void SetMoveRight(MoveObject& obj);   //右の向きにセットする
	bool GoHouse(MoveObject& obj,RoadInfo& info);
	bool Gopiano(MoveObject& obj, RoadInfo& info);
	bool Gopark(MoveObject& obj, RoadInfo& info);

	void SetPosFromMap(MoveObject& obj, int mapX, int mapY);
	bool HitBox(float ax, float ay, float aw, float ah,
		float bx, float by, float bw, float bh);
	void Playertocollide();
	void Animation(MoveObject& obj,Sprite* spr);
	float DegToRad(float degree)
	{
		const float PI = 3.1415926535f;
		return degree * PI / 180.0f;
	}
	static Map& Instance()
	{
		static Map map;
		return map;
	}

	// Infoを更新する

	void UpdateInfo(MoveObject& obj, RoadInfo& info);
	void UpdateInfo(int mapX, int mapY, RoadInfo& info);
};
