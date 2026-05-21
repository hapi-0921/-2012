#include "SceneGame.h"
#include "SceneManager.h"
#include"SceneResult.h"
#include "SceneTitle.h"
#include"Mapchip.h"
#include "player.h"

Map* mapchip;
Sprite* sprGame;

int game_state;
int game_timer;

//int cursorRow = 0;
//int cursorCol = 0;
//bool isSelecting = false;
//int selectRow = 0;
//int selectCol = 0;


//テスト用コメント
void SceneGame::Initialize()
{

    game_state = 0;
    game_timer = 0;

    player.reset();

    mapchip = new Map;
}

void SceneGame::Finalize()
{
    safe_delete(sprGame);
}



void SceneGame::Update(float delta_time)
{
    switch (game_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprGame = sprite_load(L"./Data/Images/game.png");


        game_state++;
       

            break;

        case 1:
            //////// パラメータの設定 ////////

            GameLib::setBlendMode(Blender::BS_ALPHA);

            game_state++;
            /*fallthrough*/
            break;
        case 2:

            mapchip->Update();
          
           
            ++game_timer;
            break;

        }
    
}

void SceneGame::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    //背景
    sprite_render(sprGame, 0, 0, 1, 1);
    mapchip->Render();

}

#ifdef _DEBUG
void SceneGame::DrawImGui()
{

   
}
#endif

