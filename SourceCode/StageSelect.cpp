#include "StageSelect.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "Scene_GameArea1.h"
#include "Scene_GameArea2.h"
#include "Scene_GameArea3.h"

Sprite* sprSelect;
Sprite* sprstage1button;
Sprite* sprstage2button;
Sprite* sprstage3button;
Sprite* sprStageSelectpos;

//(X座標、Y座標、横幅（W）、立幅（H）、番号)
Button stage1Button = { 200,200,400,400,0 };
Button stage2Button = { 700,200,400,400,1 };
Button stage3Button = { 1200,200,400,400,2 };

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
    safe_delete(sprstage1button);
    safe_delete(sprstage2button);
    safe_delete(sprstage3button);

    safe_delete(sprStageSelectpos);

    music::stop(0);
}

void StageSelect::Update(float delta_time)
{
    switch (select_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprSelect = sprite_load(L"./Data/Images/select.png");
        sprstage1button = sprite_load(L"./Data/Images/stage1buttun.png");
        sprstage2button = sprite_load(L"./Data/Images/stage2buttun.png");
        sprstage3button = sprite_load(L"./Data/Images/stage3buttun.png");

        sprStageSelectpos = sprite_load(L"./Data/Images/playerpos_kari.png");

        select_state++;


        break;

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        select_state++;
        /*fallthrough*/
        break;
    case 2:

        bool click = player.MenuUpdate(3);


        if (TRG(0) & PAD_START)
        {
            switch (player.GetCursorIndex())
            {
            case 0:
                manager->ChangeScene(new Scene_GameArea1(manager, nullptr));//ステージ１
                break;
            case 1:
                manager->ChangeScene(new  Scene_GameArea2(manager));//ステージ2
                break;
            case 2:
                manager->ChangeScene(new  Scene_GameArea3(manager));//ステージ3
                break;
            }
        }


        CursorPos pos = player.getCursorpos();

        if (click)
        {
            if (player.IsHovered(stage1Button, pos.x, pos.y))
            {
                manager->ChangeScene(new Scene_GameArea1(manager, nullptr));//ステージ1へ
                music::play(1);

            }
            else if (player.IsHovered(stage2Button, pos.x, pos.y))
            {
                manager->ChangeScene(new Scene_GameArea2(manager, nullptr));//ステージ2へ
                music::play(2);

            }
            else if (player.IsHovered(stage3Button, pos.x, pos.y))
            {
                manager->ChangeScene(new Scene_GameArea3(manager, nullptr));//ステージ3へ
                music::play(3);

            }

        }
        ++select_timer;
        break;

    }
}

void StageSelect::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    //背景
    sprite_render(sprSelect, 0, 0, 1, 1);

    

    //ボタンの描画
    //ボタンにカーソルを合わしたときに押し込まれてるように
    float texW = 400;
    float texH = 400;

    CursorPos position = player.getCursorpos();

    //ステージ1ボタン
    if (player.IsHovered(stage1Button, position.x, position.y))
    {
        sprite_render(sprstage1button, 400, 400, 0.95f, 0.95f, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    else
    {
        sprite_render(sprstage1button, 400, 400, 1, 1, 0, 0, texW, texH, texW / 2, texH / 2);
    }

    //ステージ2ボタン
    if (player.IsHovered(stage2Button, position.x, position.y))
    {
        sprite_render(sprstage2button, 900, 400, 0.95f, 0.95f, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    else
    {
        sprite_render(sprstage2button, 900, 400, 1, 1, 0, 0, texW, texH, texW / 2, texH / 2);
    }

    //ステージ3ボタン
    if (player.IsHovered(stage3Button, position.x, position.y))
    {
        sprite_render(sprstage3button, 1400, 400, 0.95f, 0.95f, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    else
    {
        sprite_render(sprstage3button, 1400, 400, 1, 1, 0, 0, texW, texH, texW / 2, texH / 2);

    }

    if (player.GetCursorIndex() == 0)
    {
        sprite_render(sprStageSelectpos, 400, 400, 1, 1);
    }
    if (player.GetCursorIndex() == 1)
    {
        sprite_render(sprStageSelectpos, 900, 400, 1, 1);
    }
    if (player.GetCursorIndex() == 2)
    {
        sprite_render(sprStageSelectpos, 1400, 400, 1, 1);
    }


    //デバッグ表示
   /* Drawbutton(stage1Button);
    Drawbutton(stage2Button);
    Drawbutton(stage3Button);*/

}

#ifdef _DEBUG
void StageSelect::DrawImGui()
{

}
#endif

//デバッグ
void StageSelect::Drawbutton(Button button)
{
    GameLib::primitive::rect(
        button.x,
        button.y,
        button.width,
        button.height,
        0, 0, 0,
        1, 0, 0, 0.3f,    // 色
        false
    );
}
