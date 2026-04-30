#include "SceneTutorial.h"
#include "SceneTitle.h"
#include "SceneManager.h"


Sprite* sprTutorial;

int tutorial_state;
int tutorial_timer;

void SceneTutorial::Initialize()
{
    tutorial_state = 0;
    tutorial_timer = 0;
}

void SceneTutorial::Finalize()
{
    safe_delete(sprTutorial);
    music::stop(0);
}

void SceneTutorial::Update(float delta_time)
{
    switch (tutorial_state)
    {
    case 0:
        //////// ‰ŠúÝ’è ////////

        sprTutorial = sprite_load(L"./Data/Images/tutorial.png");


        tutorial_state++;


        break;

    case 1:
        //////// ƒpƒ‰ƒ[ƒ^‚ÌÝ’è ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        tutorial_state++;
        /*fallthrough*/
        break;
    case 2:

        if (TRG(0) & PAD_START)
        {
            manager->ChangeScene(new SceneTitle(manager, nullptr));
        }
        ++tutorial_timer;
        break;

    }
}

void SceneTutorial::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    sprite_render(sprTutorial, 0, 0, 1, 1);

}

#ifdef _DEBUG
void SceneTutorial::DrawImGui()
{

}
#endif
