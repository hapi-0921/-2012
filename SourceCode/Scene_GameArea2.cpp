#include "SceneManager.h"
#include "SceneResult.h"
#include "Scene_GameArea2.h"
#include "Number.h"

Sprite* sprStage2;

int stage2_state;
int stage2_timer;

void Scene_GameArea2::Initialize()
{
    stage2_state = 0;
    stage2_timer = 90;

    NumberInitialize();

}

void Scene_GameArea2::Finalize()
{
    safe_delete(sprStage2);
  
}

void Scene_GameArea2::Update(float delta_time)
{
    switch (stage2_state)
    {
    case 0:
        //////// ‰ŠúÝ’è ////////

        sprStage2 = sprite_load(L"./Data/Images/stage2.png");


        stage2_state++;


        break;

    case 1:
        //////// ƒpƒ‰ƒ[ƒ^‚ÌÝ’è ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        stage2_state++;
        /*fallthrough*/
        break;
    case 2:

       



        //1•b‚Å1Œ¸‚é‚æ‚¤‚É
        static int frame = 0;
        frame++;
        if (frame >= 60)
        {
            stage2_timer--;
            frame = 0;
        }


        break;

    }
}

void Scene_GameArea2::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    sprite_render(sprStage2, 0, 0, 1, 1);

    DrawNumber(64, 10, stage2_timer);
}

#ifdef _DEBUG
void Scene_GameArea2::DrawImGui()
{

}
#endif
