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
    SceneBase* nextScenePtr;
    Map Tutorialmap;
    Player player;
#ifdef _DEBUG
    void DrawImGui();
#endif
};
