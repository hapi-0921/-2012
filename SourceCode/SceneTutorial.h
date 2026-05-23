#pragma once
#include"vector"
#include"SceneBase.h"
#include"SceneTitle.h"
#include"SceneGame.h"
#include"player.h"
#include"Mapchip.h"
class SceneTutorial :public SceneBase
{
public:
    SceneTutorial(SceneManager* mgr, SceneBase* next = nullptr)
        :SceneBase(mgr), nextScenePtr(next) {
    }

    void Initialize() override;
    void Finalize() override;
    void Update(float delta_time) override;
    void Draw() override;
private:
    bool stop = false;
    int step = -1;
    Sprite* sprruru1;
    Sprite* sprruru2;
    Sprite* sprruru3;
    Sprite* sprruru4;
    Sprite* sprruru5;
    Sprite* sprruru6;
    Sprite* sprmemo;
    Sprite* sprclick;
    Sprite* sprGray;
    Sprite* sprskip;
    SceneBase* nextScenePtr;
    Map Tutorialmap;
    Player player;

    Sprite* sprKeyCurPosTu;
    int row;
    int col;

#ifdef _DEBUG
    void DrawImGui();
#endif
};
