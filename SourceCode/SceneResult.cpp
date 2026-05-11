#include "SceneResult.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "StageSelect.h"

Sprite* sprResult;

Sprite* sprSelect1button;
Sprite* sprTitlebutton;

//(X座標、Y座標、横幅（W）、立幅（H）、番号)
Button selectButton = { 400,200,400,400,0 };
Button titleButton = { 900,200,400,400,1 };


int result_state;
int result_timer;




void SceneResult::Initialize()
{
    result_state = 0;
    result_timer = 0;
}

void SceneResult::Finalize()
{
    safe_delete(sprResult);
    music::stop(0);
    safe_delete(sprSelect1button);
    safe_delete(sprTitlebutton);
}

void SceneResult::Update(float delta_time)
{
    switch (result_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprResult = sprite_load(L"./Data/Images/result.png");
        sprSelect1button = sprite_load(L"./Data/Images/selectbuttun.png");
        sprTitlebutton = sprite_load(L"./Data/Images/titlebuttun.png");

        result_state++;
        

            break;

        case 1:
            //////// パラメータの設定 ////////

            GameLib::setBlendMode(Blender::BS_ALPHA);

            result_state++;
            /*fallthrough*/
            break;
        case 2:
            bool click = player.MenuUpdate(2);

            if (TRG(0) & PAD_START)
            {
                switch (player.GetCursorIndex())
                {
                case 0:
                    manager->ChangeScene(new StageSelect(manager, nullptr));//ステージ選択画面へ
                    break;
                case 1:
                    manager->ChangeScene(new SceneTitle(manager));//タイトル画面へ
                    break;
                }
            }

            CursorPos pos = player.getCursorpos();

            if (click)
            {
                if (player.IsHovered(selectButton, pos.x, pos.y))
                {
                    manager->ChangeScene(new StageSelect(manager, nullptr));//選択画面へ
                    music::play(1);
                }
                else if (player.IsHovered(titleButton, pos.x, pos.y))
                {
                    manager->ChangeScene(new SceneTitle(manager,nullptr));//タイトル画面へ
                    music::play(2);
                }
            }
            ++result_timer;
            break;

        }
    }

void SceneResult::Draw()
{
    setBlendMode(Blender::BS_ALPHA);
    
    clear(0, 0, 0);
    //背景
    sprite_render(sprResult, 0, 0, 1, 1);
    sprite_render(sprSelect1button, 400, 200);
    sprite_render(sprTitlebutton, 900, 200);


    //デバッグ表示
    Drawbutton(selectButton);
    Drawbutton(titleButton);

}

#ifdef _DEBUG
void SceneResult::DrawImGui()
{
    
}
#endif

//デバッグの表示
void  SceneResult::Drawbutton(Button button)
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

