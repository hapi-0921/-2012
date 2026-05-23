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
Sprite* TitleRogo;

Sprite* sprCloud;

Sprite* Green;

Sprite* SkyBlue;




//(X座標、Y座標、横幅（W）、立幅（H）、番号)
Button startButton = { 100,520 + 64,384,256,0 };//250,430
Button howtoButton = { 1436,520 + 64,384,256,1 };//1286,430




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
    safe_delete(TitleRogo);
    safe_delete(sprCloud);
    safe_delete(Green);
   
    safe_delete(SkyBlue);
   
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

        TitleRogo = sprite_load(L"./Data/Images/TitleRogo.png");

        sprCloud = sprite_load(L"./Data/Images/cloud.png");

        Green = sprite_load(L"./Data/Images/Green.png");

       

        SkyBlue = sprite_load(L"./Data/Images/skyblue.png");

       

        fade_A = 0.0;
        fade_start = false;
        fade_out = false;

        //雲配置
        clouds[0] = { -100, 30, 1.0f };
        clouds[1] = { 900, 120, 0.6f };
        clouds[2] = { 800, 290, 1.3f };
        clouds[3] = { -500, 250, 0.8f };
        clouds[4] = { -200, 350, 0.8f };
        clouds[5] = { 100, 550, 0.8f };



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

        for (int i = 0; i < 4; i++)
        {
            clouds[i].x += clouds[i].speed;

            //画面外に行ったら左へ戻す
            if (clouds[i].x > 1920)
            {
                clouds[i].x = -200;
            }
        }


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
   
    


    //背景
    clear(0.50f, 0.66f, 0.83f);

    //青背景
    sprite_render(
        SkyBlue,
        0, 0, 2, 1
    );

    //緑背景
    sprite_render(
        Green,
        0, 660,2,1
    );

   



    //雲描画
    for (int i = 0; i < 4; i++)
    {
        sprite_render(
            sprCloud,
            clouds[i].x,
            clouds[i].y,
            2.0f, 2.0f,
            0, 0,
            183, 92, // 雲画像サイズ
            0, 0,
            0,
            1, 1, 1
        );
    }

    //アニメーション描画
    int frameWidth = 128;
    int frameHeight = 128;

    int srcX = Roadframe * frameWidth;


    sprite_render(
        sprRoad,
        960,
        640,
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
        sprite_render(sprTutorialbutton, 294, 712,5.95f,5.95f, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    else
    {
        sprite_render(sprTutorialbutton, 294, 712,6, 6, 0, 0, texW, texH, texW / 2, texH / 2);
    }

    //選択画面へのボタン
    if (player.IsHovered(howtoButton, position.x, position.y))
    {
        sprite_render(sprSelectbutton, 1630, 712, 5.95f, 5.95f,0,0,texW,texH,texW/2,texH/2);
    }
    else
    {
        sprite_render(sprSelectbutton, 1630, 712,6,6,0, 0, texW, texH, texW / 2, texH / 2);
    }


    //タイトルロゴ
    sprite_render(TitleRogo, 960 - 448,540 - 512,7,6);


    sprite_render(fade, 0, 0, 1, 1, 0, 0, 1920, 1080, 0, 0, 0, 1, 1, 1, (fade_A));


    

   

    if (player.GetCursorIndex() == 0)
    {
        sprite_render(sprTitleSelecting, 294, 712, 2, 2);
    }
    if (player.GetCursorIndex() == 1)
    {
        sprite_render(sprTitleSelecting, 1630, 712, 2, 2);
    }

    


    //デバッグ表示
   /* Drawbutton(startButton);

 
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




