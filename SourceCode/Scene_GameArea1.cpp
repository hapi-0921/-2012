#include "SceneManager.h"
#include "SceneResult.h"
#include "Scene_GameArea1.h"
#include "StageSelect.h"



Sprite* sprStage1;

int stage1_state;
int stage1_timer;

void Scene_GameArea1::Initialize()
{
    stage1_state = 0;
    stage1_timer = 0;
}

void Scene_GameArea1::Finalize()
{
    safe_delete(sprStage1);
    music::stop(0);
}

void Scene_GameArea1::Update(float delta_time)
{
    switch (stage1_state)
    {
    case 0:
        //////// ‰ŠúÝ’è ////////

        sprStage1 = sprite_load(L"./Data/Images/stage1.png");


        stage1_state++;


        break;

    case 1:
        //////// ƒpƒ‰ƒ[ƒ^‚ÌÝ’è ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        stage1_state++;
        /*fallthrough*/
        break;
    case 2:

        player.MenuUpdate();


        if (TRG(0) & PAD_START)
        {
            manager->ChangeScene(new SceneResult(manager, nullptr));
        }
        ++stage1_timer;
        break;

    }
}

void Scene_GameArea1::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    sprite_render(sprStage1, 0, 0, 1, 1);

    player.Draw();


}

#ifdef _DEBUG
void Scene_GameArea1::DrawImGui()
{

}
#endif
