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



    GameLib::setBlendMode(Blender::BS_ALPHA);
    GameLib::clear(1, 1, 1);

    sprite_render(sprTitle, 0, 0);


#ifdef _DEBUG
    DrawImGui();
#endif
}

#ifdef _DEBUG
void SceneTitle::DrawImGui()
{

}
#endif


