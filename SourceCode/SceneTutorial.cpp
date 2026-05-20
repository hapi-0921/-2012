#include "SceneTutorial.h"
#include "SceneTitle.h"
#include "SceneManager.h"


Sprite* sprTutorial;

int tutorial_state;
int tutorial_timer;

void SceneTutorial::Initialize()
{
    Tutorialmap.map.resize(4);

    for (int y = 0; y < 4; y++)
    {
        Tutorialmap. map[y].resize(4);
    }

    Tutorialmap. map =
    {
        {7,2,3,1},
        {1,2,3,1},
        {1,3,2,1},
        {2,1,3,5},
    };
    Tutorialmap.tutorial = true;
    tutorial_state = 0;
    tutorial_timer = 0;
    Tutorialmap.m.move.pos.x = 300;
}

void SceneTutorial::Finalize()
{
    safe_delete(sprTutorial);

}

void SceneTutorial::Update(float delta_time)
{
    switch (tutorial_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprTutorial = sprite_load(L"./Data/Images/tutorial.png");


        tutorial_state++;


        break;

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        tutorial_state++;
        /*fallthrough*/
        break;
    case 2:

        debug::setString("moby%f", Tutorialmap.m.move.pos.y);



        /* if (TRG(0) & PAD_START)
         {
             manager->ChangeScene(new SceneTitle(manager, nullptr));
         }*/


        switch (step)
        {
        case 0:
            Tutorialmap.TutorialUpdate();
            if (Tutorialmap.block[0][2].pass == 1)
            {
                step = 1;
            }
            break;

        case 1://ブロックが端についたら説明
            stop = true;
            if (TRG(0) & PAD_START)
            {
                step = 2;


            }
            break;
        case 2:
            Tutorialmap.TutorialUpdate();
            if (Tutorialmap.m.move.pos.y >= 227)
            {
                step = 3;
                //
            }
            break;
        case 3:
            player.GameUpdate(Tutorialmap);
            if (Tutorialmap.map[1][2] == 2)
            {
                step = 4;
            }
            break;
        
    case 4:
        Tutorialmap.TutorialUpdate();
        break;
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
    Tutorialmap.Render();
    if (!stop)
    {
        Tutorialmap.m.move.animTimer += 1.0f / 60.0f;
    }
    text_out(1,"端につくと反転する", 800, 200, 1, 1, 0, 1, 1);
    debug::display(1, 0, 1, 2, 2); // ← 最後に描く

}

#ifdef _DEBUG
void SceneTutorial::DrawImGui()
{

}
#endif
