#include "../GameLib/game_lib.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneBase.h"


int title_state;
int title_timer;

Sprite* sprTitle;



void SceneTitle::Initialize()
{
    title_state = 0;
    title_timer = 0;
}


void SceneTitle::Finalize()
{
    music::stop(0);

    safe_delete(sprTitle);
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


        title_state++;


        //音楽再生（ループ）
        music::play(0, true);

        /*fallthrough*/
        break;

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);




        title_state++;

        break;

    case 2:

        int mx = input::getCursorPosX();
        int my = input::getCursorPosY();

        float button_x = 400;
        float button_y = 300;
        float button_w = 200;
        float button_h = 80;

        bool isHover =
            mx >= button_x &&
            mx <= button_x + button_w &&
            my >= button_y &&
            my <= button_y + button_h;

        // 仮：左クリック
        if (isHover && (input::TRG(0) & LEFT_CLICK))
        {
            manager->ChangeScene(new SceneGame(manager, nullptr));
        }

        //enter押したら次
        if (TRG(0) & PAD_START)
        {
            manager->ChangeScene(new SceneGame(manager, nullptr));
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

    sprite_render(sprTitle, 0, 0);

   
    float button_x = 400;
    float button_y = 300;
    float button_w = 200;
    float button_h = 80;

    debug::setString("x:%f", button_x);

    debug::setString("y:%f", button_y);

    debug::setString("w:%f", button_w);

    debug::setString("h:%f", button_h);

    debug::display(0, 0, 0, 1, 1);

    

#ifdef _DEBUG
    DrawImGui();
#endif
}

#ifdef _DEBUG
void SceneTitle::DrawImGui()
{
  
}
#endif


