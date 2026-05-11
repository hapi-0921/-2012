#include "StageSelect.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "Scene_GameArea1.h"
#include "Scene_GameArea2.h"
#include "Scene_GameArea3.h"

Sprite* sprSelect;

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
    music::stop(0);
}

void StageSelect::Update(float delta_time)
{
    switch (select_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprSelect = sprite_load(L"./Data/Images/select.png");


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
            }
            else if (player.IsHovered(stage2Button, pos.x, pos.y))
            {
                manager->ChangeScene(new Scene_GameArea2(manager));//ステージ2へ
            }
            else if (player.IsHovered(stage3Button, pos.x, pos.y))
            {
                manager->ChangeScene(new Scene_GameArea3(manager));//ステージ3へ
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
    sprite_render(sprSelect, 0, 0, 1, 1);

    //デバッグ表示
    Drawbutton(stage1Button);
    Drawbutton(stage2Button);
    Drawbutton(stage3Button);

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
