#include "../GameLib/game_lib.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneBase.h"
#include "player.h"
#include "StageSelect.h"

int title_state;
int title_timer;

Sprite* sprTitle;

Button startButton = { 300,200,200,50,0 };
Button howtoButton = { 300,280,200,50,1 };




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


        

        bool click = player.MenuUpdate();
        CursorPos pos = player.getCursorpos();

        if (click)
        {
            if (player.IsHovered(startButton, pos.x, pos.y))
            {
                manager->ChangeScene(new SceneGame(manager, nullptr));
            }
            else if (player.IsHovered(howtoButton, pos.x, pos.y))
            {
                manager->ChangeScene(new StageSelect(manager));
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

    sprite_render(sprTitle, 0, 0);

    Drawbutton(startButton);

    Drawbutton(howtoButton);


#ifdef _DEBUG
    DrawImGui();
#endif
}

#ifdef _DEBUG
void SceneTitle::DrawImGui()
{
   
}
#endif

void  SceneTitle::Drawbutton(Button button)
{
    GameLib::primitive::rect(
        button.x,
        button.y,
        button.width,
        button.height,
        0, 0, 0,          // 中心・角度（そのままでOK）
        1, 0, 0, 0.3f,    // 色（赤＋半透明）
        false
    );
}




