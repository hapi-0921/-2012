#include "SceneTutorial.h"
#include "SceneTitle.h"
#include "SceneManager.h"


Sprite* sprTutorial;

int tutorial_state;
int tutorial_timer;

void SceneTutorial::Initialize()
{
    sprruru1 =sprite_load(L"./Data/Images/ruru1.png");
    sprruru2 =sprite_load(L"./Data/Images/ruru2.png");
    sprruru3 =sprite_load(L"./Data/Images/ruru3.png");
    sprruru4 =sprite_load(L"./Data/Images/ruru4.png");
    sprruru5 =sprite_load(L"./Data/Images/ruru5.png");
    sprruru6= sprite_load(L"./Data/Images/ruru6.png");
    sprmemo= sprite_load(L"./Data/Images/MemoBackground.png");
    sprKeyCurPosTu = sprite_load(L"./Data/Images/cursor.png");
    sprclick = sprite_load(L"./Data/Images/click.png");
    sprGray= sprite_load(L"./Data/Images/Gray.png");
    sprskip= sprite_load(L"./Data/Images/skip.png");

    Tutorialmap.map.resize(4);

    for (int y = 0; y < 4; y++)
    {
        Tutorialmap. map[y].resize(4);
    }

    Tutorialmap. map =
    {
        {7,2,3,1},
        {1,2,3,3},
        {2,2,2,2},
        {2,1,3,5},
    };
    Tutorialmap.tutorial = true;
    tutorial_state = 0;
    tutorial_timer = 0;
    Tutorialmap.m.move.pos.x = 300;

    Tutorialmap.scale = 3;
    Tutorialmap.chipSize = 192;
    Tutorialmap.block[1][3].angle = 180;
    Tutorialmap.m.move.speed = 2;
    Tutorialmap.c.move.speed = 4;
    Tutorialmap.n.pos.x = 725;
    Tutorialmap.n.pos.y = 670;
    player.Tutorial = true;
    step = -1;
}

void SceneTutorial::Finalize()
{
    safe_delete(sprTutorial);

    music::stop(6);

}

void SceneTutorial::Update(float delta_time)
{
    switch (tutorial_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprTutorial = sprite_load(L"./Data/Images/tutorial.png");

        //音楽再生（ループ）
        music::play(6, true);


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



        row = (player.GetTutorialRow() + 1) * 198;
        col = (player.GetTutorialCol() + 1) * 198;


        switch (step)
        {
        case -1:
            stop = true;
            if (player.MenuUpdate(1))
            {
                step = 0;
            }
            break;
        case 0:
            stop = false;
            Tutorialmap.TutorialUpdate();
            if (Tutorialmap.block[0][2].pass == 1)
            {
                step = 1;
            }
            break;

        case 1://ブロックが端についたら説明
            stop = true;

            if (player.MenuUpdate(1))
            {
                step = 2;


            }
            break;
        case 2:
            stop = false;
            Tutorialmap.TutorialUpdate();
            if (Tutorialmap.m.move.pos.y >= 226)
            {
                step = 3;
            }
            break;
        case 3://playerにマス動かさせる
            stop = true;
            player.TutorialUpdate(Tutorialmap);
            if (Tutorialmap.map[1][2] == 2)
            {
                step = 4;
            }
            break;
        case 4:
            stop = false;
            Tutorialmap.TutorialUpdate();
            if (Tutorialmap.m.move.pos.y >= 418)
            {
                step = 5;
                
            }
            break;

        case 5://車出す
            stop = true;
            Tutorialmap.TutorialCar();
            Tutorialmap.c.move.speed = 4;
            if (Tutorialmap.c.move.pos.x == 2000)
            {
                step = 7;
            }
            break;
        case 7://
            stop = false;
            Tutorialmap.m.move.speed = 4;
            Tutorialmap.TutorialUpdate();
            if (Tutorialmap.block[1][2].pass==2)
            {
                step = 8;
            }
            break;
        case 8://道が回る説明
            Tutorialmap.TutorialUpdate();
            if (Tutorialmap.block[1][2].pass == 3)
            {
                step = 9;
            }
            break;
        case 9:
            stop = true;

            if (player.MenuUpdate(1))
            {
                step = 10;
            }
            break;
        case 10://ゴールに付いたら
            stop = false;
            Tutorialmap.TutorialUpdate();
            if (Tutorialmap.m.move.pos.y >= 600)
            {
                Tutorialmap.m.housepoint = true;
                step = 11;
            }
            break;
        case 11://チュートリアル終わり
            stop = true;

            if (player.MenuUpdate(1))
            {

             manager->ChangeScene(new SceneTitle(manager, nullptr));
         }
            break;
       
    }
        ++tutorial_timer;
        Tutorialmap.gametimer++;
        break;
    }
}

void SceneTutorial::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    Tutorialmap.Render();
    sprite_render(sprmemo, 1020, 100, 13, 13, 0, 0, 64, 64);


    if (!stop)
    {
        Tutorialmap.m.move.animTimer += 1.0f / 60.0f;
    }
    debug::display(1, 0, 1, 2, 2); // ← 最後に描く
    switch (step)
    {
    case -1:
        sprite_render(sprruru1, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        if (Tutorialmap.gametimer >> 5 & 0x01)
        {
            sprite_render(sprclick, 1560, 760, 0.5, 0.5, 1, 1, 454, 340);
        }
       
        
            break;
    case 0:
        sprite_render(sprruru1, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        
        break;

    case 1://ブロックが端についたら説明
        sprite_render(sprruru2, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        if (Tutorialmap.gametimer >> 5 & 0x01)
        {
            sprite_render(sprclick, 1560, 760, 0.5, 0.5, 1, 1, 454, 340);
        }
        break;
    case 2:
        sprite_render(sprruru2, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);

        break;
    case 3://playerにマス動かさせる
        sprite_render(sprruru3, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        sprite_render(sprGray, 0, 0, 1, 1, 1, 1, 1920, 1080);
        break;
    case 4:
        sprite_render(sprruru3, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);

        break;

    case 5://車出す
        sprite_render(sprruru4, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);

        break;
    case 6://車の説明
        sprite_render(sprruru4, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        break;
    case 7://
        sprite_render(sprruru4, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        if (Tutorialmap.gametimer >> 5 & 0x01)
        {
            sprite_render(sprskip, 1560, 200, 0.5, 0.5, 1, 1, 300, 300);
        }
        break;
    case 8://道が回る説明
        sprite_render(sprruru5, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        if (Tutorialmap.gametimer >> 5 & 0x01)
        {
            sprite_render(sprskip, 1560, 200, 0.5, 0.5, 1, 1, 300, 300);
        }
        break;
    case 9:
        sprite_render(sprruru5, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        if (Tutorialmap.gametimer >> 5 & 0x01)
        {
            sprite_render(sprclick, 1560, 760, 0.5, 0.5, 1, 1, 454, 340);
        }
        break;
    case 10://ゴールに付いたら
        sprite_render(sprruru6, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        if (Tutorialmap.gametimer >> 5 & 0x01)
        {
            sprite_render(sprskip, 1560, 200, 0.5, 0.5, 1, 1, 300, 300);
        }
        break;
    case 11://チュートリアル終わり
        sprite_render(sprruru6, 1100, 200, 0.8, 0.8, 1, 1, 900, 800);
        if (Tutorialmap.gametimer >> 5 & 0x01)
        {
            sprite_render(sprclick, 1560, 760, 0.5, 0.5, 1, 1, 454, 340);
        }
        break;


    }

    if (player.isKeyboardMode()) sprite_render(sprKeyCurPosTu, col, row + 15, 2, 2);
}

#ifdef _DEBUG
void SceneTutorial::DrawImGui()
{

}
#endif
