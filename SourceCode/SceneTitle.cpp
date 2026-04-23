#include "../GameLib/game_lib.h"
#include "SceneTitle.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneResult.h"
void SceneTitle::Initialize()
{
   
}


void SceneTitle::Finalize()
{
    
}

//更新
void SceneTitle::Update(float delta_time)
{
   
}

//描画
void SceneTitle::Draw()
{
    GameLib::setBlendMode(Blender::BS_ALPHA);
    GameLib::clear(1, 1, 1);

    
#ifdef _DEBUG
    DrawImGui();
#endif
}

#ifdef _DEBUG
void SceneTitle::DrawImGui()
{
   
}
#endif


