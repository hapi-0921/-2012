#include "SceneResult.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "StageSelect.h"
#include "Scene_GameArea1.h"
#include "Number.h"



Sprite* sprResult;

Sprite* sprSelect1button;
Sprite* sprTitlebutton;

Sprite* GameclearRogo;
Sprite* GameoverRogo;

Sprite* Gameclear;
Sprite* Gameover;


Sprite* GameoverPlayer;

Sprite* ClearPlayer;


//(X座標、Y座標、横幅（W）、立幅（H）、番号)
Button titleButton = { 1470,945,224,60,0};



int result_state;
int result_timer;
int resultframe;




void SceneResult::Initialize()
{
    result_state = 0;
    result_timer = 0;

    NumberInitialize();

}

void SceneResult::Finalize()
{
    safe_delete(sprResult);
    music::stop(9);
   
    safe_delete(sprTitlebutton);
    safe_delete(Gameclear);
    safe_delete(Gameover);
    safe_delete(GameoverPlayer);
    safe_delete(GameclearRogo);
    safe_delete(GameoverRogo);
    safe_delete(ClearPlayer);


}

void SceneResult::Update(float delta_time)
{
    switch (result_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprResult = sprite_load(L"./Data/Images/result.png");
       
        sprTitlebutton = sprite_load(L"./Data/Images/titlego.png");

        Gameclear = sprite_load(L"./Data/Images/Clear.png");

        Gameover = sprite_load(L"./Data/Images/Gameover.png");

        GameoverPlayer = sprite_load(L"./Data/Images/GameoverPlayer.png");

        ClearPlayer = sprite_load(L"./Data/Images/ClearPlayer.png");

        GameclearRogo = sprite_load(L"./Data/Images/ClearRogo.png");
        GameoverRogo = sprite_load(L"./Data/Images/GameoverRogo.png");

        if (clearTime > 0)
        {
            music::play(11);
        }
        else//０以下ならゲームオーバー画面へ
        {
            music::play(10);
            music::setVolume(10, 1.8f);

        }

        result_state++;
        
        //音楽再生（ループ）
       /* music::play(9, true);*/

       
            break;

        case 1:
            //////// パラメータの設定 ////////

            GameLib::setBlendMode(Blender::BS_ALPHA);

            result_state++;
            /*fallthrough*/
            break;
        case 2:
            bool click = player.MenuUpdate(2);

            //アニメーション
            if (result_timer > 10)
            {
                resultframe++;

                result_timer = 0;

                if (resultframe >= 4)
                {
                    resultframe = 0;
                }
            }

            if (TRG(0) & PAD_START)
            {
                manager->ChangeScene(new SceneTitle(manager));;
                music::play(1);
            }


            CursorPos pos = player.getCursorpos();

            if (click)
            {
                if (player.IsHovered(titleButton, pos.x, pos.y))
                {
                    manager->ChangeScene(new SceneTitle(manager,nullptr));//タイトル画面へ
                    music::play(1);
                }
            }
            ++result_timer;
            break;

        }
    }

void SceneResult::Draw()
{
    setBlendMode(Blender::BS_ALPHA);
    
   
    //背景
    clear(0.5f, 0.8f, 1.0f);//空色
    
    int frameWidth = 64;
    int frameHeight = 64;

    int srcX = resultframe * frameWidth;

    //ボタンの描画
    //ボタンにカーソルを合わしたときに押し込まれてるように
    float texW = 560;
    float texH = 150;

    CursorPos position = player.getCursorpos();

    //タイトルに戻るボタン
    if (player.IsHovered(titleButton, position.x, position.y))
    {
        sprite_render(sprTitlebutton, 1580, 975, 0.3f, 0.3f, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    else
    {
        sprite_render(sprTitlebutton, 1580, 975, 0.4f, 0.4f, 0, 0, texW, texH, texW / 2, texH / 2);
    }

    //時間
    DrawNumber(850, 700, clearTime);

    //時間が０以上ならクリア画面
    if (clearTime > 0)
    {
        sprite_render(Gameclear, 1500, 750, 5, 5, 0, 0, 64, 64, 32, 32, 170);

        sprite_render(GameclearRogo, 900, 300, 8, 8, 0, 0, 128, 64, 64, 32);

        //アニメーション描画
       
        sprite_render(
            ClearPlayer,
            360,
            740,
            4,
            4,
            srcX,
            0,
            frameWidth,
            frameHeight,
            frameWidth / 2,
            frameHeight / 2
        );

    }
    else//０以下ならゲームオーバー画面へ
    {
        sprite_render(Gameover, 1500, 750, 5, 5, 0, 0, 64, 64, 32, 32,170);

        sprite_render(GameoverRogo, 900, 300, 8, 8, 0, 0, 128, 64, 64, 32);

        //アニメーション描画
        sprite_render(
            GameoverPlayer,
            360,
            740,
            4,
            4,
            srcX,
            0,
            frameWidth,
            frameHeight,
            frameWidth / 2,
            frameHeight / 2
        );

    }

    //デバッグ表示
    
    /*Drawbutton(titleButton);*/

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

