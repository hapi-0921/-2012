#include "SceneManager.h"
#include "SceneResult.h"
#include "Scene_GameArea1.h"
#include "StageSelect.h"
<<<<<<< HEAD
#include "Number.h"
=======
#include "Character.h"
#include "mapchip.h"

>>>>>>> 16205dd1aa60dca66d02d12023c622066b49eea1


Sprite* sprStage1;


int stage1_state;
int stage1_timer;

void Scene_GameArea1::Initialize()
{
    stage1_state = 0;
    stage1_timer = 90;



    NumberInitialize();
   

}

void Scene_GameArea1::Finalize()
{
    safe_delete(sprStage1);
    
   

}

void Scene_GameArea1::Update(float delta_time)
{
    switch (stage1_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprStage1 = sprite_load(L"./Data/Images/stage1.png");


        stage1_state++;


        break;

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        stage1_state++;
        /*fallthrough*/
        break;
    case 2:

        character.Move();
        player.GameUpdate(mapchip);

        if (TRG(0) & PAD_START)
        {
            manager->ChangeScene(new SceneResult(manager, nullptr));
        }

            

        //1秒で1減るように
        static int frame = 0;
        frame++;
        if (frame >= 60)
        {
            stage1_timer--;
            frame = 0;
        }


       
        break;

    }
}

void Scene_GameArea1::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    sprite_render(sprStage1, 0, 0, 1, 1);

<<<<<<< HEAD
    player.Draw();

   
    DrawNumber(64,10, stage1_timer);
=======
    character.Draw();

    mapchip.Render();
>>>>>>> 16205dd1aa60dca66d02d12023c622066b49eea1
}








#ifdef _DEBUG
void Scene_GameArea1::DrawImGui()
{

}
#endif
