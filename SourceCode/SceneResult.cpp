#include "SceneResult.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "StageSelect.h"

Sprite* sprResult;

Sprite* sprSelect1button;
Sprite* sprTitlebutton;

//(X座標、Y座標、横幅（W）、立幅（H）、番号)
Button titleButton = { 600,200,560,150,0};



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
   
    safe_delete(sprTitlebutton);
}

void SceneResult::Update(float delta_time)
{
    switch (result_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprResult = sprite_load(L"./Data/Images/result.png");
       
        sprTitlebutton = sprite_load(L"./Data/Images/titlego.png");

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
          
                if (player.IsHovered(titleButton, pos.x, pos.y))
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
    

    //ボタンの描画
    //ボタンにカーソルを合わしたときに押し込まれてるように
    float texW = 560;
    float texH = 150;

    CursorPos position = player.getCursorpos();

    //タイトルに戻るボタン
    if (player.IsHovered(titleButton, position.x, position.y))
    {
        sprite_render(sprTitlebutton, 880, 275, 1.45f, 1.45f, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    else
    {
        sprite_render(sprTitlebutton, 880, 275, 1.5, 1.5, 0, 0, texW, texH, texW / 2, texH / 2);
    }


    //デバッグ表示
   /* Drawbutton(selectButton);
    Drawbutton(titleButton);*/

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

