#include "StageSelect.h"

#include "SceneManager.h"


Sprite* sprSelect;

int select_state;
int select_timer;

void StageSelect::Initialize()
{
    select_state = 0;
    select_timer = 0;
}

void StageSelect::Finalize()
{
    safe_delete(sprSelect);
    music::stop(0);
}

void StageSelect::Update(float delta_time)
{
    switch (select_state)
    {
    case 0:
        //////// ‰ŠúÝ’è ////////

        sprSelect = sprite_load(L"./Data/Images/select.png");


        select_state++;


        break;

    case 1:
        //////// ƒpƒ‰ƒ[ƒ^‚ÌÝ’è ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        select_state++;
        /*fallthrough*/
        break;
    case 2:

        if (TRG(0) & PAD_START)
        {
            manager->ChangeScene(new SceneGame(manager, nullptr));
        }
        ++select_timer;
        break;

    }
}

void StageSelect::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    sprite_render(sprSelect, 0, 0, 1, 1);

}

#ifdef _DEBUG
void StageSelect::DrawImGui()
{

}
#endif
