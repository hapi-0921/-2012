#include "SceneManager.h"
#include "SceneResult.h"
#include "Scene_GameArea1.h"
#include "StageSelect.h"
#include "Number.h"
#include "Character.h"
#include "Mapchip.h"





Sprite* sprStage1;
Sprite* sprKeyCurPos;
Sprite* sprFrame;
Sprite* sprClock;
Sprite* sprTutolialBook;

Sprite* sprMemo1;
Sprite* sprMemo2;
Sprite* sprMemo3;
Sprite* sprNext;

Sprite* sprRuru;
Sprite* spr3;
Sprite* spr2;
Sprite* spr1;

Sprite* Town;



//(X座標、Y座標、横幅（W）、立幅（H）、番号)
Button tutolialButton = { 1704,424,120,138,0 };
Button nextButton = { 1300,920,120,120,1 };

int stage1_state;
int stage1_timer;
int stage1_frame_timer;
//0ページ目
int tutorialPage = 0;
//本を開いたときに時を止める
bool tutorialOpen = false;


//カウントダウン
int countdownState = 0;
float countdownTimer = 0.0f;


void Scene_GameArea1::Initialize()
{
    stage1_state = 0;

    stage1_timer = 100;

    countdownState = 0;
    countdownTimer = 0;

    NumberInitialize();
   

}

void Scene_GameArea1::Finalize()
{
    safe_delete(sprStage1);
    
    safe_delete(sprKeyCurPos);

    safe_delete(sprFrame);

    safe_delete(sprClock);

    safe_delete(sprTutolialBook);

    safe_delete(sprMemo1);

    safe_delete(sprMemo2);

    safe_delete(sprMemo3);

    safe_delete(sprNext);

    safe_delete(sprRuru);

    safe_delete(spr3);

    safe_delete(spr2);

    safe_delete(spr1);

    safe_delete(Town);


    music::stop(6);

}

void Scene_GameArea1::Update(float delta_time)
{
    switch (stage1_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprStage1 = sprite_load(L"./Data/Images/stage1.png");
        sprKeyCurPos = sprite_load(L"./Data/Images/cursor.png");
        sprFrame = sprite_load(L"./Data/Images/frame.png");
        sprClock = sprite_load(L"./Data/Images/Clock.png");
        sprTutolialBook = sprite_load(L"./Data/Images/Memo.png");
        sprMemo1 = sprite_load(L"./Data/Images/MemoManual1.png");
        sprMemo2 = sprite_load(L"./Data/Images/MemoManual2.png");
        sprMemo3 = sprite_load(L"./Data/Images/MemoManual3.png");
        sprNext = sprite_load(L"./Data/Images/Next.png");

        sprRuru = sprite_load(L"./Data/Images/ruru.png");

        spr3 = sprite_load(L"./Data/Images/3.png");
        spr2 = sprite_load(L"./Data/Images/2.png");
        spr1 = sprite_load(L"./Data/Images/1.png");

        Town = sprite_load(L"./Data/Images/Town.png");

        stage1_state++;

        //音楽再生（ループ）
        music::play(6, true);
        break;

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        stage1_state++;
        /*fallthrough*/
        break;
    case 2:

        // チュートリアル用クリック判定
        static bool prevTutorialMouse = false;

        bool mouseLeft = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
        bool click = (!prevTutorialMouse && mouseLeft);

        prevTutorialMouse = mouseLeft;

        //カウントダウン
        
        countdownTimer += delta_time;


         // ruru表示
        if (countdownState == 0)
        {
            if (click)
            {
                countdownState = 1;
                countdownTimer = 0;
            }
            music::play(12);
        }
        else if (countdownState == 1)
        {
            if (countdownTimer >= 1.0f)
            {
                music::play(12);
                countdownState = 2;
                countdownTimer = 0;
                music::play(12);
            }
        }
        else if (countdownState == 2)
        {
            if (countdownTimer >= 1.0f)
            {
               
                countdownState = 3;
                countdownTimer = 0;
                music::play(12);
            }
        }
        else if (countdownState == 3)
        {
            if (countdownTimer >= 1.0f)
            {
               
                countdownState = 4;
                countdownTimer = 0;
                music::play(12);
            }
        }

        //ゲーム開始
        CursorPos pos = player.getCursorpos();

        

        if (click)
        {
            // 本を開く
            if (!tutorialOpen &&
                player.IsHovered(tutolialButton, pos.x, pos.y))
            {
                tutorialOpen = true;
                tutorialPage = 1;

                music::play(5);
            }

            // 次ページ
            else if (tutorialOpen &&
                player.IsHovered(nextButton, pos.x, pos.y))
            {
                tutorialPage++;

                music::play(5);

                if (tutorialPage > 3)
                {
                    tutorialOpen = false;
                    tutorialPage = 0;
                }
            }
        }

        // 本を開いてない時だけプレイヤー操作,ルール、カウントが動いてるときにストップ
        if (!tutorialOpen && countdownState == 4)
        {
            player.GameUpdate(mapchip);
        }

        // カーソル位置更新
        row = (player.GetCursorRow() + 1) * 128;
        col = (player.GetCursorCol() + 1) * 128;

        // 本を開いてない時だけゲーム進行、カウントが終わり次第スタート
        if (!tutorialOpen && countdownState == 4)
        {
            mapchip.Update();

            //ゴールした
            if (mapchip.goal)
            {
                manager->ChangeScene(new SceneResult(manager, stage1_timer));
            }

            // タイマー
            static int frame = 0;
            frame++;

            if (frame >= 60)
            {
                stage1_timer--;
                frame = 0;
            }

            // 時間切れ
            if (stage1_timer <= 0)
            {
                manager->ChangeScene(new SceneResult(manager, stage1_timer));
            }

            stage1_frame_timer++;
        }

        break;

        
    }
    
}


void Scene_GameArea1::Draw()
{
    setBlendMode(Blender::BS_ALPHA);

    clear(0, 0, 0);
    sprite_render(sprStage1, 0, 0, 1, 1);

    //ルール表示
    if (countdownState == 0)
    {
        sprite_render(Town, 0, 0, 2.0f, 1.6875f);

        sprite_render(sprRuru, 150, 50, 0.6f, 0.6f);
        return;
    }
    //3
    if (countdownState == 1)
    {
        sprite_render(Town, 0, 0, 2.0f, 1.6875f);



        sprite_render(spr3,
            860, 400,
            1, 1);

        return;
    }
    //2
    if (countdownState == 2)
    {
        sprite_render(Town, 0,0, 2.0f, 1.6875f);

        sprite_render(spr2,
            860, 400,
            1, 1);

        return;
    }
    //1
    if (countdownState == 3)
    {
        sprite_render(Town, 0, 0, 2.0f, 1.6875f);

        sprite_render(spr1,
            860, 400,
            1, 1);

        return;
    }






    sprite_render(sprClock, 1624, 5, 2, 2);


    DrawNumber(1826,15, stage1_timer);

    // 本
    float texW = 64;
    float texH = 64;

    CursorPos position = player.getCursorpos();

    mapchip.Render();

    //チュートリアルへのボタン
    if (player.IsHovered(tutolialButton, position.x, position.y))
    {
        sprite_render(sprTutolialBook, 1762, 492, 2.95f, 2.95f, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    else
    {
        sprite_render(sprTutolialBook, 1762, 492, 3, 3, 0, 0, texW, texH, texW / 2, texH / 2);
    }
    //メモの中身
    if (tutorialOpen)
    {
        switch (tutorialPage)
        {
        case 1:
            sprite_render(sprMemo1, 960, 540, 8, 8);
            break;

        case 2:
            sprite_render(sprMemo2, 960, 540, 8, 8);
            break;

        case 3:
            sprite_render(sprMemo3, 960, 540, 8, 8);
            break;
        }


        //矢印表示
        if (player.IsHovered(nextButton, position.x, position.y))
        {
            sprite_render(
                sprNext,
                1360, 990,   // 表示位置
                0.5f, 0.5f,  // scaleX, scaleY
                0, 0,
                360, 360,    // 元画像サイズ
                180, 180     // 中心座標
            );
        }
        else
        {
            sprite_render(
                sprNext,
                1360, 990,
                0.5f, 0.6f,
                0, 0,
                360, 360,
                180, 180
            );
        }
        


    }

    
    if ((stage1_frame_timer / 32) % 2 == 0 && player.GetSelecting())
    {
        sprite_render(sprFrame, (player.GetSelectingCol() + 1) * 128 - 28, (player.GetSelectingRow() + 1) * 128 - 28);
    }
    if (player.isKeyboardMode()) sprite_render(sprKeyCurPos, col, row+15, 2, 2);



    //デバッグ
   /* DrawbuttonGame(tutolialButton);*/

   /* DrawbuttonGame(nextButton);*/


}


void Scene_GameArea1::DrawbuttonGame(Button button)
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





#ifdef _DEBUG
void Scene_GameArea1::DrawImGui()
{

}
#endif
