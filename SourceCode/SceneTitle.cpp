#include "../GameLib/game_lib.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "Scene_GameArea1.h"
#include "SceneResult.h"
#include "SceneBase.h"
#include "player.h"
#include "StageSelect.h"
#include "SceneTutorial.h"
#include "audio.h"
#include "Number.h"




int title_state;
int title_timer;
float fade_A;
bool fade_start;
bool fade_out;
int Roadframe;
Sprite* fade;
Sprite* sprTitle;

Sprite* sprTutorialbutton;
Sprite* sprTitleSelecting;
Sprite* sprSelectbutton;

Sprite* sprRoad;


//(X座標、Y座標、横幅（W）、立幅（H）、番号)
Button startButton = { 250,430 + 64,384,256,0 };//850/200
Button howtoButton = { 1286,430 + 64,384,256,1 };//850/200




void SceneTitle::Initialize()
{
    title_state = 0;
    title_timer = 0;
    Roadframe = 0;
   
   

    player.reset();

}


void SceneTitle::Finalize()
{

    music::stop(0);

    safe_delete(sprTitle);

    safe_delete(sprTitleSelecting);
    safe_delete(sprTutorialbutton);
    safe_delete(sprSelectbutton);
    safe_delete(sprRoad);
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
        sprTitleSelecting = sprite_load(L"./Data/Images/cursor.png");
        sprSelectbutton = sprite_load(L"./Data/Images/selectbuttun.png");
       
        sprRoad = sprite_load(L"./Data/Images/TitleRoad.png");

        fade = sprite_load(L"./Data/Images/fade.png");

        fade_A = 0.0;
        fade_start = false;
        fade_out = false;

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

        character.Move();

        title_timer++;


        //アニメーション
        if (title_timer > 10)
        {
            Roadframe++;

            title_timer = 0;

            if (Roadframe >= 4)
            {
                Roadframe = 0;
            }
        }


        if (TRG(0) & PAD_START)
        {
            switch (player.GetCursorIndex())
            {
            case 0:
                manager->ChangeScene(new SceneTutorial(manager, nullptr));//チュートリアル画面へ
                break;
            case 1:
                manager->ChangeScene(new Scene_GameArea1(manager));//ステージ選択画面へ
                break;
            }
        }

        bool click = player.MenuUpdate(2);
        CursorPos pos = player.getCursorpos();

        if (click)
        {
            if (player.IsHovered(startButton, pos.x, pos.y))
            {
               
                music::play(1);
                manager->ChangeScene(new SceneTutorial(manager, nullptr));//チュートリアル画面へ
            }
            else if (player.IsHovered(howtoButton, pos.x, pos.y))
            {
                fade_start = true;
                music::play(1);

            }
            
        }
        if (fade_start == true)
        {
            fade_A += 0.01f;
            if (fade_A >= 1.0f)
            {
                fade_A = 1.0f;
                fade_out = true;
            }

            if (fade_out)
            {
                manager->ChangeScene(new Scene_GameArea1(manager));//ステージ選択画面へ
                break;
            }
        }

           




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

    //アニメーション描画
    int frameWidth = 128;
    int frameHeight = 128;

    int srcX = Roadframe * frameWidth;


    sprite_render(
        sprRoad,
        960,
        540,
        5,
        5,
        srcX,
        0,
        frameWidth,
        frameHeight,
        frameWidth / 2,
        frameHeight / 2
    );

    character.Draw();

    //ボタンの描画
    //ボタンにカーソルを合わしたときに押し込まれてるように
    float texW = 64;
    float texH = 64;

    CursorPos position = player.getCursorpos();

    //チュートリアルへのボタン
    if (player.IsHovered(startButton, position.x, position.y))
    {
        sprite_render(sprTutorialbutton, 444, 622,5.95f,5.95f, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    else
    {
        sprite_render(sprTutorialbutton, 444, 622,6, 6, 0, 0, texW, texH, texW / 2, texH / 2);
    }

    //選択画面へのボタン
    if (player.IsHovered(howtoButton, position.x, position.y))
    {
        sprite_render(sprSelectbutton, 1480, 622, 5.95f, 5.95f,0,0,texW,texH,texW/2,texH/2);
    }
    else
    {
        sprite_render(sprSelectbutton, 1480, 622,6,6,0, 0, texW, texH, texW / 2, texH / 2);
    }

    sprite_render(fade, 0, 0, 1, 1, 0, 0, 1920, 1080, 0, 0, 0, 1, 1, 1, (fade_A));

    

   

    if (player.GetCursorIndex() == 0)
    {
        sprite_render(sprTitleSelecting, 444, 622, 2, 2);
    }
    if (player.GetCursorIndex() == 1)
    {
        sprite_render(sprTitleSelecting, 1480, 622, 2, 2);
    }

    


    //デバッグ表示
    /*Drawbutton(startButton);

 
    Drawbutton(howtoButton);*/

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




