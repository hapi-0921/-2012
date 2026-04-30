#include "SceneManager.h"

#include "Scene_GameArea2.h"

Sprite* sprStage2;

int stage2_state;
int stage2_timer;

void Scene_GameArea2::Initialize()
{
    stage2_state = 0;
    stage2_timer = 0;
}

void Scene_GameArea2::Finalize()
{
    safe_delete(sprStage2);
    music::stop(0);
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

        if (TRG(0) & PAD_START)
        {
            manager->ChangeScene(new SceneGame(manager, nullptr));
        }
        ++stage2_timer;
        break;

    }
}

void Scene_GameArea2::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    sprite_render(sprStage2, 0, 0, 1, 1);

}

#ifdef _DEBUG
void Scene_GameArea2::DrawImGui()
{

}
#endif
