#pragma once
#include"SceneBase.h"
#include"SceneTitle.h"
#include"SceneGame.h"
#include "player.h"
#include "Character.h"
#include "Mapchip.h"


class Scene_GameArea1 :public SceneBase
{
public:
    Scene_GameArea1(SceneManager* mgr, SceneBase* next = nullptr)
        :SceneBase(mgr), nextScenePtr(next) {
    }

    void Initialize() override;
    void Finalize() override;
    void Update(float delta_time) override;
    void Draw() override;
  

private:
    SceneBase* nextScenePtr;

    Player player;
    Character character;
    Map mapchip;
    
    int row;
    int col;


#ifdef _DEBUG
    void DrawImGui();
#endif
};