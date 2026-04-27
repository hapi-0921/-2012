#include "SceneResult.h"
#include "SceneManager.h"


Sprite* sprResult;

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
}

void SceneResult::Update(float delta_time)
{
    switch (result_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprResult = sprite_load(L"./Data/Images/result.png");


        result_state++;
        
            //////// 初期設定 ////////

            sprResult = sprite_load(L"./Data/Images/result.png");


            result_state++;
            /*fallthrough*/

            break;

        case 1:
            //////// パラメータの設定 ////////

            GameLib::setBlendMode(Blender::BS_ALPHA);

            result_state++;
            /*fallthrough*/
            break;
        case 2:

            if (TRG(0) & PAD_START)
            {
                manager->ChangeScene(new SceneTitle(manager));
            }
            ++result_timer;
            break;

        }
    }

void SceneResult::Draw()
{
    GameLib::setBlendMode(Blender::BS_ALPHA);
    
    clear(0, 0, 0);
    sprite_render(sprResult, 0, 0, 1, 1);

}

#ifdef _DEBUG
void SceneResult::DrawImGui()
{
    
}
#endif
