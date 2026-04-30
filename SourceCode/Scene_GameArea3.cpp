#include "SceneManager.h"

#include "Scene_GameArea3.h"

Sprite* sprStage3;

int stage3_state;
int stage3_timer;

void Scene_GameArea3::Initialize()
{
    stage3_state = 0;
    stage3_timer = 0;
}

void Scene_GameArea3::Finalize()
{
    safe_delete(sprStage3);
    music::stop(0);
}

void Scene_GameArea3::Update(float delta_time)
{
    switch (stage3_state)
    {
    case 0:
        //////// ‰ŠúÝ’è ////////

        sprStage3 = sprite_load(L"./Data/Images/stage3.png");


        stage3_state++;


        break;

    case 1:
        //////// ƒpƒ‰ƒ[ƒ^‚ÌÝ’è ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        stage3_state++;
        /*fallthrough*/
        break;
    case 2:

        if (TRG(0) & PAD_START)
        {
            manager->ChangeScene(new SceneGame(manager, nullptr));
        }
        ++stage3_timer;
        break;

    }
}

void Scene_GameArea3::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    sprite_render(sprStage3, 0, 0, 1, 1);

}

#ifdef _DEBUG
void Scene_GameArea3::DrawImGui()
{

}
#endif
