#include "../GameLib/game_lib.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneBase.h"
#include "player.h"
#include "StageSelect.h"
#include "SceneTutorial.h"
#include "audio.h"
#include "Number.h"




int title_state;
int title_timer;

Sprite* sprTitle;

Sprite* sprTutorialbutton;
Sprite* sprTitleSelecting;
Sprite* sprSelectbutton;


//(X座標、Y座標、横幅（W）、立幅（H）、番号)
Button startButton = { 400,200,400,400,0 };
Button howtoButton = { 900,200,400,400,1 };




void SceneTitle::Initialize()
{
    title_state = 0;
    title_timer = 0;

    player.reset();

}


void SceneTitle::Finalize()
{

    music::stop(0);

    safe_delete(sprTitle);

    safe_delete(sprTitleSelecting);
    safe_delete(sprTutorialbutton);
}

//更新
void SceneTitle::Update(float delta_time)
{
  

    switch (title_state)
    {
    case 0:
        //////// 初期設定 ////////

        //画像の読み込み

        sprTitle = sprite_load(L"./Data/Images/title.png");

        sprTutorialbutton = sprite_load(L"./Data/Images/tutorialbuttun.png");
        sprTitleSelecting = sprite_load(L"./Data/Images/playerpos_kari.png");


        title_state++;

        //音楽再生（ループ）
        music::play(0, true);


        break;


        

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        title_state++;

       
        break;

    case 2:
        if (TRG(0) & PAD_START)
        {
            switch (player.GetCursorIndex())
            {
            case 0:
                manager->ChangeScene(new SceneTutorial(manager, nullptr));//チュートリアル画面へ
                break;
            case 1:
                manager->ChangeScene(new StageSelect(manager));//ステージ選択画面へ
                break;
            }
        }

        bool click = player.MenuUpdate(2);
        CursorPos pos = player.getCursorpos();

        if (click)
        {
            if (player.IsHovered(startButton, pos.x, pos.y))
            {
                manager->ChangeScene(new SceneTutorial(manager, nullptr));//チュートリアル画面へ
                music::play(1);

            }
            else if (player.IsHovered(howtoButton, pos.x, pos.y))
            {
                manager->ChangeScene(new StageSelect(manager));//ステージ選択画面へ
                music::play(2);

            }
        }

    
            title_timer++;
            break;
        

    }
}

//描画
void SceneTitle::Draw()
{
    setBlendMode(Blender::BS_ALPHA);
    clear(1, 1, 1);
    //背景
    sprite_render(sprTitle, 0, 0);

    //ボタンの描画
    //ボタンにカーソルを合わしたときに押し込まれてるように
    float texW = 400;
    float texH = 400;


    sprite_render(sprTutorialbutton, 400, 200);

    sprite_render(sprSelectbutton, 900, 200);

    CursorPos position = player.getCursorpos();

    //チュートリアルへのボタン
    if (player.IsHovered(startButton, position.x, position.y))
    {
        sprite_render(sprTutorialbutton, 600, 400,0.95f,0.95f, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    else
    {
        sprite_render(sprTutorialbutton, 600, 400, 1, 1, 0, 0, texW, texH, texW / 2, texH / 2);
    }

    //選択画面へのボタン
    if (player.IsHovered(howtoButton, position.x, position.y))
    {
        sprite_render(sprSelectbutton, 1100, 400, 0.95f, 0.95f,0,0,texW,texH,texW/2,texH/2);
    }
    else
    {
        sprite_render(sprSelectbutton, 1100, 400,1,1,0, 0, texW, texH, texW / 2, texH / 2);
    }


    sprite_render(sprTutorialbutton, 400, 200);

    if (player.GetCursorIndex() == 0)
    {
        sprite_render(sprTitleSelecting, 600, 400, 1, 1);
    }
    if (player.GetCursorIndex() == 1)
    {
        sprite_render(sprTitleSelecting, 1100, 400, 1, 1);
    }

    //デバッグ表示
  /*  Drawbutton(startButton);*/

 
    /*Drawbutton(howtoButton);*/

#ifdef _DEBUG
    DrawImGui();
#endif
}

#ifdef _DEBUG
void SceneTitle::DrawImGui()
{
   
}
#endif

//デバッグの表示
void  SceneTitle::Drawbutton(Button button)
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




