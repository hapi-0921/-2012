#pragma once
#include"SceneBase.h"
#include"SceneTitle.h"
#include"SceneGame.h"
class SceneResult :public SceneBase
{
public:
    SceneResult(SceneManager* mgr, SceneBase* next = nullptr)
        :SceneBase(mgr), nextScenePtr(next) {
    }

    void Initialize() override;
    void Finalize() override;
    void Update(float delta_time) override;
    void Draw() override;
    void Drawbutton(Button button);


private:
    SceneBase* nextScenePtr;

    Player player;

   
#ifdef _DEBUG
    void DrawImGui();
#endif
};
