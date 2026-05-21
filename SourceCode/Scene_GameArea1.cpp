#include "SceneManager.h"
#include "SceneResult.h"
#include "Scene_GameArea1.h"
#include "StageSelect.h"
#include "Number.h"
#include "Character.h"
#include "Mapchip.h"





Sprite* sprStage1;
Sprite* sprKeyCurPos;
Sprite* sprFrame;
Sprite* sprClock;


int stage1_state;
int stage1_timer;
int stage1_frame_timer;


void Scene_GameArea1::Initialize()
{
    stage1_state = 0;
    stage1_timer = 5;



    NumberInitialize();
   

}

void Scene_GameArea1::Finalize()
{
    safe_delete(sprStage1);
    
    safe_delete(sprKeyCurPos);

}

void Scene_GameArea1::Update(float delta_time)
{
    switch (stage1_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprStage1 = sprite_load(L"./Data/Images/stage1.png");
        sprKeyCurPos = sprite_load(L"./Data/Images/cursor.png");
        sprFrame= sprite_load(L"./Data/Images/frame.png");
        sprClock = sprite_load(L"./Data/Images/Clock.png");
        stage1_state++;


        break;

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        stage1_state++;
        /*fallthrough*/
        break;
    case 2:
        player.GameUpdate(mapchip);
        
       
        mapchip.Update();
       



        //if (TRG(0) & PAD_START)
        //{
        //    manager->ChangeScene(new SceneResult(manager, nullptr));
        //}

        mapchip.Update();

        row = (player.GetCursorRow() + 1) * 128;
        col = (player.GetCursorCol() + 1) * 128;
            

        //1秒で1減るように
        static int frame = 0;
        frame++;
        if (frame >= 60)
        {
            stage1_timer--;
            frame = 0;
        }

        // 時間切れ
        if (stage1_timer <= 0)
        {
            manager->ChangeScene(new SceneResult(manager, stage1_timer));
        }


        stage1_frame_timer++;
        break;

    }
}

void Scene_GameArea1::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    sprite_render(sprStage1, 0, 0, 1, 1);

    sprite_render(sprClock, 1624, 5, 2, 2);


    DrawNumber(1756,15, stage1_timer);



    mapchip.Render();
    if ((stage1_frame_timer / 32) % 2 == 0 && player.GetSelecting())
    {
        sprite_render(sprFrame, (player.GetSelectingCol() + 1) * 128 - 20, (player.GetSelectingRow() + 1) * 128 - 30);
    }
    if (player.isKeyboardMode()) sprite_render(sprKeyCurPos, col, row+15, 2, 2);
}








#ifdef _DEBUG
void Scene_GameArea1::DrawImGui()
{

}
#endif
